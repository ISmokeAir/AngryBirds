#include "Game.h"

void Game::adaugaBird(const Bird& b) { birds.push_back(b); }
void Game::adaugaTarget(const Target& t) { targets.push_back(t); }

void Game::simuleazaLovitura(size_t idxBird, size_t idxTarget) {
    if (idxBird >= birds.size() || idxTarget >= targets.size()) return;

    /// Added the case for already destroyed targets

    if (targets[idxTarget].getViata()==0)
    {
        std::cout<< "Tinta a fost distrusa deja! Incearca sa nimeresti alta tinta.\n";
        return;
    }

    const Bird& b = birds[idxBird];
    Target& t = targets[idxTarget];

    double rezultat = b.lanseaza(t.getPozitie());
    std::cout << b.getNume() << " loveste tinta cu forta efectiv: " << rezultat << "\n";
    t.esteLovit(rezultat);

    if (t.esteDistrus())
        std::cout << "Tinta a fost distrusa!\n";
    else
        std::cout << "Tinta a ramas cu viata.\n";
}
size_t Game::getNumarPasari() const { return birds.size(); }
size_t Game::getNumarTinte() const { return targets.size(); }

bool Game::toateDistruse() const {
    for (const auto& t : targets)
        if (!t.esteDistrus()) return false;
    return true;
}


std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "---- Joc Angry Birds ----\n";
    os << "Pasari:\n";
    for (const auto& b : g.birds) os << "  " << b << "\n";
    os << "Tinte:\n";
    for (const auto& t : g.targets) os << "  " << t << "\n";
    return os;
}
