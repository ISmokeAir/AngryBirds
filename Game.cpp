#include "Game.h"
#include <iostream>
#include <random>

Game::Game() : vantCurent(0.0) {
    genereazaVant();
}

void Game::genereazaVant() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-5.0, 5.0);
    vantCurent = dis(gen);
}

void Game::addBird(const Bird& b) {
    birds.push_back(b);
}

void Game::addTarget(const Target& t) {
    targets.push_back(t);
}

void Game::simulateShot(int birdIdx, int targetIdx) {
    if (birdIdx < 0 || birdIdx >= static_cast<int>(birds.size())) {
        std::cout << "Eroare: Index pasare invalid!\n";
        return;
    }
    if (targetIdx < 0 || targetIdx >= static_cast<int>(targets.size())) {
        std::cout << "Eroare: Index tinta invalid!\n";
        return;
    }

    if (targets[targetIdx].esteDistrus()) {
        std::cout << "Acea tinta este deja distrusa! Alege alta.\n";
        return;
    }

    const Bird& b = birds[birdIdx];
    Target& t = targets[targetIdx];

    std::cout << "\n>>> LANSARE >>>\n";
    std::cout << "Vantul bate cu puterea: " << vantCurent << "\n";

    double impact = b.calculeazaImpact(t.getPozitie(), vantCurent);
    bool hit = t.incaseazaDamage(impact);

    if (hit) {
        std::cout << "LOVITURA REUSITA!\n";
        std::cout << "Damage aplicat: " << impact << "\n";
        std::cout << "Viata ramasa tinta: " << t.getViata() << "\n";

        if (t.esteDistrus()) {
            std::cout << "*** TINTA DISTRUSA! ***\n";
        }
    } else {
        std::cout << "RATARE! (Pasarea nu a ajuns sau lovitura prea slaba)\n";
    }
    std::cout << "------------------------\n";

    stats.addShot(hit, impact);
    genereazaVant();
}

void Game::demoRun() {
    std::cout << "\n=== PORNIRE MOD AUTO-SIMULARE ===\n";

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distBird(0, static_cast<int>(birds.size()) - 1);

    int incercari = 0;
    const int MAX_INCERCARI = 15;

    while (!checkWin() && incercari < MAX_INCERCARI) {
        int birdIdx = distBird(gen);


        int targetIdx = -1;
        std::vector<int> tinteValide;
        for(size_t i=0; i<targets.size(); ++i) {
            if(!targets[i].esteDistrus()) {
                tinteValide.push_back(static_cast<int>(i));
            }
        }

        if (!tinteValide.empty()) {
            std::uniform_int_distribution<> distTarget(0, static_cast<int>(tinteValide.size()) - 1);
            targetIdx = tinteValide[distTarget(gen)];

            std::cout << "[AUTO] Calculatorul a ales Pasarea " << birdIdx
                      << " si Tinta " << targetIdx << "\n";
            simulateShot(birdIdx, targetIdx);
        } else {
            break;
        }

        incercari++;
    }

    std::cout << "=== FINAL AUTO-SIMULARE ===\n";
    if (checkWin()) {
        std::cout << "Calculatorul a castigat!\n";
    } else {
        std::cout << "Calculatorul nu a reusit sa distruga tot in " << MAX_INCERCARI << " incercari.\n";
    }
}

bool Game::checkWin() const {
    for (const auto& t : targets) {
        if (!t.esteDistrus()) return false;
    }
    return true;
}

void Game::printState() const {
    std::cout << *this;
    std::cout << "Vant momentan: " << vantCurent << " (Negativ=Apropie, Pozitiv=Indeparteaza)\n";
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "\n=== STARE JOC ===\n";
    os << "PASARI DISPONIBILE:\n";
    for (size_t i = 0; i < g.birds.size(); ++i) {
        os << " [" << i << "] " << g.birds[i] << "\n";
    }
    os << "\nTINTE (INAMICI):\n";
    for (size_t i = 0; i < g.targets.size(); ++i) {
        if (!g.targets[i].esteDistrus()) {
            os << " [" << i << "] " << g.targets[i] << "\n";
        } else {
            os << " [" << i << "] (DISTRUSA)\n";
        }
    }
    os << "\n" << g.stats << "\n";
    os << "=================\n";
    return os;
}