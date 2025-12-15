#include "Game.h"
#include <iostream>
#include <random>
#include <vector>


Game::Game() : vantCurrent(0.0), dificultate(Difficulty::Normal) {
    this->updateVant();
}

void Game::updateVant() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    this->vantCurrent = dis(gen);
}

void Game::addBird(const Bird& b) {
    this->birds.push_back(b);
}

void Game::addTarget(const Target& t) {
    this->targets.push_back(t);
}

void Game::setDifficulty(Difficulty d) {
    this->dificultate = d;

    double hpMod = 1.0;
    double armuraMod = 1.0;

    switch (this->dificultate) {
        case Difficulty::Easy:
            hpMod = 0.7;
            armuraMod = 0.8;
            break;
        case Difficulty::Normal:
            hpMod = 1.0;
            armuraMod = 1.0;
            break;
        case Difficulty::Hard:
            hpMod = 1.5;
            armuraMod = 1.2;
            break;
    }

    for (auto& t : this->targets) {
        t.scaleazaDificultate(hpMod, armuraMod);
    }

    std::cout << "Dificultatea a fost setata. Tintele au fost modificate.\n";
}

void Game::lanseazaPasare(int birdIdx, int targetIdx) {
    if (birdIdx < 0 || birdIdx >= static_cast<int>(this->birds.size())) {
        std::cout << "Eroare: Pasare invalida.\n";
        return;
    }
    if (targetIdx < 0 || targetIdx >= static_cast<int>(this->targets.size())) {
        std::cout << "Eroare: Tinta invalida.\n";
        return;
    }

    if (this->targets[targetIdx].esteDistrus()) {
        std::cout << "Tinta este deja distrusa.\n";
        return;
    }

    const Bird& b = this->birds[birdIdx];
    Target& t = this->targets[targetIdx];

    std::cout << "\n>>> FIZICA LANSARE >>>\n";
    std::cout << "Vant: " << this->vantCurrent << " m/s\n";
    std::cout << "Pasare: " << b.getNume() << "\n";

    double dist = b.getPozitie().distanta(t.getPozitie());
    double momentum = b.calculeazaMomentum(dist, this->vantCurrent);

    std::cout << "Impact Momentum: " << momentum << "\n";

    bool hit = t.aplicaImpact(momentum);

    if (hit) {
        std::cout << "LOVITURA!\n";
        if (t.esteDistrus()) {
            std::cout << "*** STRUCTURA DISTRUSA ***\n";
        } else {
            std::cout << "HP ramas: " << t.getIntegritate() << "\n";
        }
    } else {
        std::cout << "Impact nesemnificativ.\n";
    }

    this->stats.inregistreazaLansare(hit, momentum);
    this->updateVant();
}

double Game::calculeazaScorStrategic(int birdIdx, int targetIdx) const {
    const Bird& b = this->birds[birdIdx];
    const Target& t = this->targets[targetIdx];

    if (t.esteDistrus()) return -1.0;

    double dist = b.getPozitie().distanta(t.getPozitie());
    double damageEstimat = b.calculeazaMomentum(dist, this->vantCurrent);

    double eficientaMaterial = 1.0;

    if (t.getMaterial() == Material::Stone && b.getMasa() > 2.0) {
        eficientaMaterial = 2.0;
    } else if (t.getMaterial() == Material::Wood && b.getViteza() > 20.0) {
        eficientaMaterial = 1.5;
    } else if (t.getMaterial() == Material::Ice) {
        eficientaMaterial = 1.2;
    }

    double damageReal = (damageEstimat / t.getArmura()) * eficientaMaterial;

    double hpProcentual = (damageReal / t.getIntegritate()) * 100.0;
    if (hpProcentual > 100.0) hpProcentual = 100.0;

    double scor = hpProcentual * 10.0;

    if (dist < 20.0) scor += 50.0;

    if (damageReal >= t.getIntegritate()) {
        scor += 500.0;
    }

    return scor;
}

void Game::ruleazaDemoAvansat() {
    std::cout << "\n=== INITIALIZARE AI AVANSAT ===\n";
    std::cout << "Analiza vectori vant si integritate structurala...\n";

    int pasiMaxim = 20;
    int pas = 0;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    while (!this->verificaVictorie() && pas < pasiMaxim) {
        pas++;
        std::cout << "\n--- Pas Simulare " << pas << " ---\n";

        int bestBird = -1;
        int bestTarget = -1;
        double maxScore = -1.0;

        std::vector<int> pasariDisponibile;
        for(size_t i=0; i<this->birds.size(); ++i) {
            pasariDisponibile.push_back(static_cast<int>(i));
        }

        if (pasariDisponibile.empty()) break;

        for (int bIdx : pasariDisponibile) {
            for (size_t tIdx = 0; tIdx < this->targets.size(); ++tIdx) {
                if (this->targets[tIdx].esteDistrus()) continue;

                double score = this->calculeazaScorStrategic(bIdx, static_cast<int>(tIdx));

                double variatie = std::uniform_real_distribution<>(0.9, 1.1)(gen);
                score *= variatie;

                if (score > maxScore) {
                    maxScore = score;
                    bestBird = bIdx;
                    bestTarget = static_cast<int>(tIdx);
                }
            }
        }

        if (bestBird != -1 && bestTarget != -1) {
            std::cout << "[AI] Solutie Optima Identificata: Pasare " << bestBird
                      << " -> Tinta " << bestTarget
                      << " (Scor incredere: " << maxScore << ")\n";
            this->lanseazaPasare(bestBird, bestTarget);
        } else {
            std::cout << "[AI] Nu s-au gasit solutii viabile.\n";
            break;
        }
    }

    std::cout << "=== FINAL SIMULARE AVANSATA ===\n";
}

bool Game::verificaVictorie() const {
    for (const auto& t : this->targets) {
        if (!t.esteDistrus()) return false;
    }
    return true;
}

void Game::afiseazaStare() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "\n=== ANGRY BIRDS ENGINE v2.0 ===\n";
    os << "Dificultate: " << static_cast<int>(g.dificultate) << "\n";
    os << "PASARI:\n";
    for (size_t i = 0; i < g.birds.size(); ++i) {
        os << i << ": " << g.birds[i] << "\n";
    }
    os << "TINTE:\n";
    for (size_t i = 0; i < g.targets.size(); ++i) {
        if (!g.targets[i].esteDistrus()) {
            os << i << ": " << g.targets[i] << "\n";
        } else {
            os << i << ": DISTRUSA\n";
        }
    }
    os << g.stats << "\n";
    return os;
}