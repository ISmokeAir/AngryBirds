#include "Game.h"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

Game::Game() : vantCurrent(0.0), dificultate(Difficulty::Normal) {
    this->updateVant();
    this->logActiune("Joc initializat.");
}

Game::~Game() {
    this->logActiune("Joc inchis.");
    this->salveazaLogPeDisk();
}

void Game::logActiune(const std::string& actiune) {

    this->istoricActiuni.push_back(actiune);
}

void Game::salveazaLogPeDisk() const {

    std::ofstream fisier("gamelog.txt");
    if (fisier.is_open()) {
        fisier << "=== JURNAL DE JOC ===\n";
        for (const auto& linie : this->istoricActiuni) {
            fisier << linie << "\n";
        }
        fisier << "=== FINAL JURNAL ===\n";
        fisier.close();
    }
}

void Game::updateVant() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    this->vantCurrent = dis(gen);


    std::stringstream ss;
    ss << "Vant actualizat la: " << std::fixed << std::setprecision(2) << this->vantCurrent;
    this->logActiune(ss.str());
}

void Game::addBird(const Bird& b) {
    this->birds.push_back(b);
    this->logActiune("Pasare adaugata: " + b.getNume());
}

void Game::addTarget(const Target& t) {
    this->targets.push_back(t);
    this->logActiune("Tinta adaugata.");
}

void Game::setDifficulty(Difficulty d) {
    this->dificultate = d;

    double hpMod = 1.0;
    double armuraMod = 1.0;
    std::string diffName;

    switch (this->dificultate) {
        case Difficulty::Easy:
            hpMod = 0.7;
            armuraMod = 0.8;
            diffName = "EASY";
            break;
        case Difficulty::Normal:
            hpMod = 1.0;
            armuraMod = 1.0;
            diffName = "NORMAL";
            break;
        case Difficulty::Hard:
            hpMod = 1.5;
            armuraMod = 1.2;
            diffName = "HARD";
            break;
    }

    for (auto& t : this->targets) {
        t.scaleazaDificultate(hpMod, armuraMod);
    }

    this->logActiune("Dificultate schimbata la: " + diffName);
    std::cout << "Dificultatea a fost setata. Tintele au fost modificate.\n";
}

void Game::predicteazaTraiectorie(int birdIdx, int targetIdx) const {
    if (birdIdx < 0 || birdIdx >= static_cast<int>(this->birds.size())) return;
    if (targetIdx < 0 || targetIdx >= static_cast<int>(this->targets.size())) return;

    const Bird& b = this->birds[birdIdx];
    const Target& t = this->targets[targetIdx];

    std::cout << "\n--- CALCUL PREDICTIV TRAIECTORIE ---\n";
    std::cout << "Pasare: " << b.getNume() << " | Vant: " << this->vantCurrent << "\n";

    Vector2D start = b.getPozitie();
    Vector2D end = t.getPozitie();

    double distTotala = start.distanta(end);
    double pasi = 10.0;
    double stepSize = distTotala / pasi;

    std::cout << "Simulare puncte intermediare:\n";

    for (int i = 0; i <= static_cast<int>(pasi); ++i) {
        double distCurenta = i * stepSize;


        double efectVant = (this->vantCurrent * 0.1) * (distCurenta / 10.0);

        double xEstimat = start.getX() + distCurenta + efectVant;
        double yEstimat = start.getY();

        std::cout << "  [Pas " << i << "] Coord: ("
                  << std::fixed << std::setprecision(2) << xEstimat << ", "
                  << std::fixed << std::setprecision(2) << yEstimat << ")";

        if (i == static_cast<int>(pasi)) {
            std::cout << " -> PUNCT IMPACT ESTIMAT";
        }
        std::cout << "\n";
    }
    std::cout << "------------------------------------\n";
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

    std::stringstream logMsg;
    logMsg << "Lansare: " << b.getNume() << " [Idx:" << birdIdx << "] -> Tinta [Idx:" << targetIdx << "]";
    this->logActiune(logMsg.str());

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
            this->logActiune("Rezultat: Tinta distrusa.");
        } else {
            std::cout << "HP ramas: " << t.getIntegritate() << "\n";
            this->logActiune("Rezultat: Lovitura partiala.");
        }
    } else {
        std::cout << "Impact nesemnificativ.\n";
        this->logActiune("Rezultat: Ratare.");
    }

    this->stats.inregistreazaLansare(hit, momentum);
    this->updateVant();
}

double Game::calculeazaScorStrategic(int birdIdx, int targetIdx) const {
    const Bird& b = this->birds[birdIdx];
    const Target& t = this->targets[targetIdx];

    if (t.esteDistrus()) return -1.0;

    Vector2D directie = t.getPozitie() - b.getPozitie();
    double dist = directie.magnitudine();

    Vector2D vantVector;
    vantVector.setX(this->vantCurrent);
    vantVector.setY(0.0);

    double influentaVant = directie.produsScalar(vantVector);

    double damageEstimat = b.calculeazaMomentum(dist, this->vantCurrent);

    if (influentaVant > 0) {
        damageEstimat *= 1.1;
    }

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
    this->logActiune("Pornire Demo AI Avansat.");
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
            std::cout << "[AI] Solutie Optima: Pasare " << bestBird
                      << " -> Tinta " << bestTarget
                      << " (Scor: " << maxScore << ")\n";


            this->predicteazaTraiectorie(bestBird, bestTarget);

            this->lanseazaPasare(bestBird, bestTarget);
        } else {
            std::cout << "[AI] Nu s-au gasit solutii viabile.\n";
            break;
        }
    }

    std::cout << "=== FINAL SIMULARE AVANSATA ===\n";
    this->logActiune("Demo AI finalizat.");
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
    os << "\n=== ANGRY BIRDS ENGINE v3.0 (LOGGING ENABLED) ===\n";
    os << "Dificultate: " << static_cast<int>(g.dificultate) << "\n";

    os << "Log Entries: " << g.istoricActiuni.size() << "\n";
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