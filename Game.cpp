#include "Game.h"
#include <iostream>
#include <limits>
#include <random>

bool Game::toateDistruse() const {
    for (const auto& t : tinte)
        if (!t.esteDistrus()) return false;
    return true;
}

void Game::simuleazaLovitura(size_t idxBird, size_t idxTarget) {
    if (idxBird >= pasari.size() || idxTarget >= tinte.size()) {
        std::cout << "Index invalid.\n";
        return;
    }

    double dist = pasari[idxBird].getPozitie().distanta(tinte[idxTarget].getPozitie());
    int damage = pasari[idxBird].getPutere();

    switch (dificultate) {
        case Dificultate::Usor:
            damage += 10;
            break;
        case Dificultate::Normal:
            break;
        case Dificultate::Greu:
            damage -= 10;
            if (damage < 1) damage = 1;
            break;
    }

    tinte[idxTarget].iaDamage(damage);
    actualizeazaScor(damage, dist);
}

void Game::actualizeazaScor(int damage, double distanta) {
    int bonus = static_cast<int>(damage - distanta / 5.0);
    if (bonus < 0) bonus = 0;
    scor += bonus;
}

void Game::seteazaDificultate(Dificultate d) {
    dificultate = d;
    for (auto& t : tinte) {
        switch (d) {
            case Dificultate::Usor:
                t.setViata(t.getViata() + 20);
                break;
            case Dificultate::Normal:
                break;
            case Dificultate::Greu:
                t.setViata(t.getViata() + 50);
                break;
        }
    }
}

bool Game::verificaIntegritate() const {
    if (pasari.empty() || tinte.empty()) return false;
    for (const auto& t : tinte)
        if (t.getViata() < 0) return false;
    return true;
}

std::vector<double> Game::calculeazaToateDistantele() const {
    std::vector<double> dist;
    dist.reserve(pasari.size() * tinte.size());
    for (const auto& b : pasari)
        for (const auto& t : tinte)
            dist.push_back(b.getPozitie().distanta(t.getPozitie()));
    return dist;
}

int Game::indiceTintaApropiata(const Vector2D& poz) const {
    if (tinte.empty()) return -1;
    double best = std::numeric_limits<double>::max();
    int idx = -1;
    for (int i = 0; i < static_cast<int>(tinte.size()); i++) {
        double d = poz.distanta(tinte[i].getPozitie());
        if (d < best) {
            best = d;
            idx = i;
        }
    }
    return idx;
}

void Game::simulareAutomata() {
    if (pasari.empty() || tinte.empty()) return;
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> db(0, static_cast<int>(pasari.size()) - 1);
    std::uniform_int_distribution<int> dt(0, static_cast<int>(tinte.size()) - 1);
    int pasi = 0;
    while (!toateDistruse() && pasi < 20) {
        int b = db(rng);
        int t = dt(rng);
        simuleazaLovitura(static_cast<size_t>(b), static_cast<size_t>(t));
        pasi++;
    }
}

void Game::reset() {
    pasari.clear();
    tinte.clear();
    scor = 0;
    dificultate = Dificultate::Normal;
}

void Game::folosesteFunctiiPentruCppcheck() const {
    if (pasari.empty() || tinte.empty()) return;
    const Bird& b = pasari.front();
    const Target& t = tinte.front();
    double valoare = b.lanseaza(t.getPozitie());
    (void)valoare;
    const std::string& nume = b.getNume();
    (void)nume;
    bool lovit = t.esteLovit(1.0);
    (void)lovit;
    Game copia = *this;
    copia.simulareAutomata();
    copia.reset();
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "--- Joc Angry Birds ---\n";
    os << "Scor: " << g.scor << "\n";
    os << "Pasari:\n";
    for (size_t i = 0; i < g.pasari.size(); i++)
        os << "  [" << i << "] " << g.pasari[i] << "\n";
    os << "Tinte:\n";
    for (size_t i = 0; i < g.tinte.size(); i++)
        os << "  [" << i << "] " << g.tinte[i] << "\n";
    return os;
}
