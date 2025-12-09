#include "Game.h"
#include <iostream>
#include <limits>
#include <random>
#include <sstream>


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


    const Vector2D& targetPos = tinte[idxTarget].getPozitie();
    double dist = pasari[idxBird].getPozitie().distanta(targetPos);


    double valoareLovitura = pasari[idxBird].lanseaza(targetPos);

    int damage = static_cast<int>(valoareLovitura);
    if (damage < 0) damage = 0; // Nu aplicam damage negativ

    std::cout << "[INFO] Lovitura Bird " << pasari[idxBird].getNume()
              << " pe Target " << idxTarget
              << " (Distanta: " << dist << ", Damage baza: " << damage << ").\n";



    int initial_damage = damage;
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

    std::cout << "[INFO] Damage aplicat (Dificultate " << getDificultateString() << "): " << damage << ".\n";
    tinte[idxTarget].iaDamage(damage);


    actualizeazaScor(damage, dist);
}


void Game::actualizeazaScor(int damage, double dist) {

    int bonus = static_cast<int>(damage - dist / 5.0);
    if (bonus < 0) bonus = 0;
    scor += bonus;
}


std::string Game::getDificultateString() const {
    switch (dificultate) {
        case Dificultate::Usor: return "Usor";
        case Dificultate::Normal: return "Normal";
        case Dificultate::Greu: return "Greu";
    }
    return "Necunoscut";
}

void Game::seteazaDificultate(Dificultate d) {
    dificultate = d;
}
bool Game::verificaIntegritate() const {
    if (pasari.empty() || tinte.empty()) return false;

    for (const auto& t : tinte)
        if (t.getViata() < 0) return false;

    // Adaugam o verificare utila: Pasarea 0 ar trebui sa aiba putere > 0.
    if (pasari[0].getPutere() <= 0) return false;

    return true;
}


std::vector<double> Game::calculeazaToateDistantele() const {
    std::vector<double> dist;


    std::cout << "[DEBUG] Calculul distantelor intre " << pasari.size() << " pasari si "
              << tinte.size() << " tinte...\n";

    for (const auto& b : pasari)
        for (const auto& t : tinte)
            dist.push_back(b.getPozitie().distanta(t.getPozitie()));

    return dist;
}


int Game::indiceTintaApropiata(const Vector2D& poz) const {
    if (tinte.empty()) return -1;

    double best = std::numeric_limits<double>::max();
    int idx = -1;

    for (int i = 0; i < (int)tinte.size(); i++) {
        double d = poz.distanta(tinte[i].getPozitie());
        if (d < best) {
            best = d;
            idx = i;
        }
    }
    return idx;
}


void Game::simulareAutomata() {
    std::cout << "[AUTO] Incep simularea (Max 20 pasi)...\n";

    std::default_random_engine rng(std::random_device{}());
    // Asiguram ca distributia nu esueaza daca un vector e gol (desi integritatea ar trebui sa previna asta)
    if (pasari.empty() || tinte.empty()) {
        std::cout << "[AUTO] Nu exista pasari sau tinte. Simularea nu poate incepe.\n";
        return;
    }

    std::uniform_int_distribution<int> db(0, (int)pasari.size() - 1);
    std::uniform_int_distribution<int> dt(0, (int)tinte.size() - 1);

    int pasi = 0;

    while (!toateDistruse() && pasi < 20) {
        int b = db(rng);
        int t = dt(rng);

        std::cout << "[AUTO] Pasul " << pasi << ": Bird[" << b << "] ataca Target[" << t << "]\n";

        simuleazaLovitura(b, t);
        pasi++;
    }

    std::cout << "[AUTO] Simulare incheiata in " << pasi << " pasi. Tinte ramase:\n";
    for (size_t i = 0; i < tinte.size(); ++i) {
        if (!tinte[i].esteDistrus()) {
            std::cout << "  [" << i << "] " << tinte[i] << "\n";
        }
    }
}


void Game::reset() {
    std::cout << "[INFO] Resetare joc: Pasari, Tinte, Scor si Dificultate au fost resetate.\n";
    pasari.clear();
    tinte.clear();
    scor = 0;
    dificultate = Dificultate::Normal;
}


std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "--- Joc Angry Birds ---\n";
    os << "Dificultate: " << g.getDificultateString() << "\n";
    os << "Scor: " << g.scor << "\n";
    os << "Pasari:\n";
    for (size_t i = 0; i < g.pasari.size(); i++)
        os << "  [" << i << "] " << g.pasari[i] << "\n";

    os << "Tinte:\n";
    for (size_t i = 0; i < g.tinte.size(); i++)
        os << "  [" << i << "] " << g.tinte[i] << (g.tinte[i].esteDistrus() ? " (DISTRUS)" : "") << "\n";

    return os;
}