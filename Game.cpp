#include "Game.h"
#include "Exceptions.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

Game::Game() : vantCurrent(0.0), dificultate(Difficulty::Normal) {
    this->updateVant();
    this->logActiune("Joc initializat (Tema 2).");
}

Game::~Game() {
    this->logActiune("Joc inchis.");
    try {
        this->salveazaLogPeDisk();
    } catch (const std::exception& e) {
        std::cerr << "Eroare la salvare log: " << e.what() << "\n";
    }
    curataMemorie();
}

void Game::curataMemorie() {
    for (auto* b : birds) {
        delete b;
    }
    birds.clear();
}

Game::Game(const Game& other)
    : targets(other.targets), stats(other.stats),
      vantCurrent(other.vantCurrent), dificultate(other.dificultate),
      istoricActiuni(other.istoricActiuni) {

    for (const auto* b : other.birds) {
        birds.push_back(b->clone());
    }
}

void swap(Game& first, Game& second) noexcept {
    using std::swap;
    swap(first.birds, second.birds);
    swap(first.targets, second.targets);
    swap(first.stats, second.stats);
    swap(first.vantCurrent, second.vantCurrent);
    swap(first.dificultate, second.dificultate);
    swap(first.istoricActiuni, second.istoricActiuni);
}

Game& Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

void Game::logActiune(const std::string& actiune) {
    this->istoricActiuni.push_back(actiune);
}

void Game::salveazaLogPeDisk() const {
    std::ofstream fisier("gamelog.txt");
    if (!fisier.is_open()) {
        throw FileException("gamelog.txt");
    }
    fisier << "=== JURNAL JOC TEMA 2 ===\n";
    for (const auto& linie : this->istoricActiuni) {
        fisier << linie << "\n";
    }
    fisier << "=== FINAL ===\n";
    fisier.close();
}

void Game::updateVant() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    this->vantCurrent = dis(gen);

    std::stringstream ss;
    ss << "Vant: " << std::fixed << std::setprecision(2) << this->vantCurrent;
    this->logActiune(ss.str());
}

void Game::addBird(Bird* b) {
    if (!b) throw LogicException("Pointer nul la addBird");
    this->birds.push_back(b);
    this->logActiune("Adaugat pasare: " + b->getNume());
}

void Game::addTarget(const Target& t) {
    this->targets.push_back(t);
    this->logActiune("Adaugat tinta.");
}

void Game::setDifficulty(Difficulty d) {
    this->dificultate = d;
    double hp = 1.0, arm = 1.0;
    if (d == Difficulty::Easy) { hp=0.7; arm=0.8; }
    if (d == Difficulty::Hard) { hp=1.5; arm=1.2; }

    for (auto& t : this->targets) t.scaleazaDificultate(hp, arm);
    this->logActiune("Dificultate schimbata.");
    std::cout << "Dificultate actualizata!\n";
}

void Game::predicteazaTraiectorie(int birdIdx, int targetIdx) const {
    if (birdIdx < 0 || birdIdx >= (int)birds.size()) throw LogicException("Idx Pasare Invalid");
    if (targetIdx < 0 || targetIdx >= (int)targets.size()) throw LogicException("Idx Tinta Invalid");

    const Bird* b = birds[birdIdx];
    const Target& t = targets[targetIdx];

    std::cout << "\n--- PREDICTIE TRAIECTORIE ---\n";
    std::cout << "Pasare: " << b->getNume() << " -> Tinta la " << t.getPozitie() << "\n";

    Vector2D start = b->getPozitie();
    Vector2D end = t.getPozitie();
    double dist = start.distanta(end);
    double step = dist / 5.0;

    for(int i=0; i<=5; ++i) {
        double d = i * step;
        double drift = (vantCurrent * 0.1) * (d/10.0);
        std::cout << "  Pas " << i << ": x=" << (start.getX() + d + drift) << "\n";
    }
    std::cout << "-----------------------------\n";
}

void Game::lanseazaPasare(int birdIdx, int targetIdx) {
    if (birdIdx < 0 || birdIdx >= (int)birds.size()) throw LogicException("Idx Pasare Invalid");
    if (targetIdx < 0 || targetIdx >= (int)targets.size()) throw LogicException("Idx Tinta Invalid");

    if (targets[targetIdx].esteDistrus()) {
        std::cout << "Tinta deja distrusa!\n";
        return;
    }

    Bird* b = birds[birdIdx];
    Target& t = targets[targetIdx];

    this->logActiune("Lansare: " + b->getNume());
    std::cout << "\n>>> LANSARE: " << *b << " >>>\n";


    if (auto* bomb = dynamic_cast<BombBird*>(b)) {
        bomb->activeazaExplozie();
    }

    double dist = b->getPozitie().distanta(t.getPozitie());
    double mom = b->calculeazaMomentum(dist, vantCurrent);

    std::cout << "Impact: " << mom << "\n";
    bool hit = t.aplicaImpact(mom);
    stats.inregistreazaLansare(hit, mom);
    updateVant();

    if (hit) std::cout << "LOVITURA! HP ramas: " << t.getIntegritate() << "\n";
    else std::cout << "RATARE!\n";
}

double Game::calculeazaScorStrategic(int birdIdx, int targetIdx) const {
    const Bird* b = birds[birdIdx];
    const Target& t = targets[targetIdx];

    if (t.esteDistrus()) return -1.0;

    double dist = b->getPozitie().distanta(t.getPozitie());
    double estDmg = b->calculeazaMomentum(dist, vantCurrent);


    return (estDmg / t.getIntegritate()) * 100.0;
}


void Game::ruleazaDemoAvansat() {
    std::cout << "\n=== PORNIRE DEMO AI (TEMA 2) ===\n";
    this->logActiune("Start Demo AI");

    int pasi = 0;
    while (!verificaVictorie() && pasi < 10) {
        pasi++;
        std::cout << "\n--- AI Runda " << pasi << " ---\n";

        int bestB = -1, bestT = -1;
        double maxS = -1.0;


        for(int i=0; i<(int)birds.size(); ++i) {
            for(int j=0; j<(int)targets.size(); ++j) {
                if (targets[j].esteDistrus()) continue;

                double s = calculeazaScorStrategic(i, j);
                if (s > maxS) { maxS = s; bestB = i; bestT = j; }
            }
        }

        if (bestB != -1) {
            std::cout << "[AI] Alege Pasarea " << bestB << " -> Tinta " << bestT << "\n";
            predicteazaTraiectorie(bestB, bestT);
            lanseazaPasare(bestB, bestT);
        } else {
            std::cout << "[AI] Nu am gasit tinte valide.\n";
            break;
        }
    }
    std::cout << "=== DEMO FINALIZAT ===\n";
}

bool Game::verificaVictorie() const {
    for(const auto& t : targets) if(!t.esteDistrus()) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "\n=== STARE JOC (TEMA 2) ===\n";
    os << "Dificultate: " << (int)g.dificultate << "\n";

    os << "PASARI:\n";
    for(size_t i=0; i<g.birds.size(); ++i) {
        os << i << ": " << *g.birds[i] << "\n";
    }

    os << "TINTE:\n";
    for(size_t i=0; i<g.targets.size(); ++i) {
        os << i << ": " << g.targets[i] << (g.targets[i].esteDistrus() ? " [DISTRUSA]" : "") << "\n";
    }

    os << g.stats << "\n";
    return os;
}