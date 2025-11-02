#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ranges>
#include <cctype>
#include "Game.h"

// Verifica daca string-ul e format doar din cifre (numar natural)
static bool isUnsignedInt(const std::string& s) {
    return !s.empty() &&
        std::ranges::all_of(s, [](unsigned char c){ return std::isdigit(c); });
}

// Citire sigura pentru indecsi din UN stream (nu doar cin)
static bool readIndex(std::istream& in, const std::string& prompt, int maxIdx, int& out) {
    std::string token;
    while (true) {
        std::cout << prompt;
        if (!(in >> token)) {
            return false; // EOF
        }

        if (!isUnsignedInt(token)) {
            std::cout << "Input invalid! Introdu un numar intre 0 si " << maxIdx << ".\n";
            continue;
        }

        int val = std::stoi(token);
        if (val < 0 || val > maxIdx) {
            std::cout << "Index inexistent! Valoarea trebuie sa fie intre 0 si " << maxIdx << ".\n";
            continue;
        }

        out = val;
        return true;
    }
}

// Citire sigura pentru y/n din UN stream
static bool readYesNo(std::istream& in, bool& yes) {
    char r;
    while (true) {
        std::cout << "Mai tragi? (y/n): ";
        if (!(in >> r)) {
            return false; // EOF
        }

        if (r == 'y' || r == 'Y') { yes = true;  return true; }
        if (r == 'n' || r == 'N') { yes = false; return true; }

        std::cout << "Introdu doar 'y' sau 'n'.\n";
    }
}

int main() {
    std::ifstream fin("astatura.txt");

    bool folosescFisier = false;
    if (fin.good()) {
        // verificam rapid daca are continut
        if (fin.peek() != std::ifstream::traits_type::eof()) {
            folosescFisier = true;
            std::cout << "[INFO] Input preluat din tastatura.txt\n";
        } else {
            std::cout << "[INFO] tastatura.txt este gol. Input de la tastatura.\n";
        }
    } else {
        std::cout << "[INFO] tastatura.txt nu exista. Input de la tastatura.\n";
    }

    // alegem stream-ul
    std::istream& in = folosescFisier ? static_cast<std::istream&>(fin) : std::cin;

    Game joc;

    joc.adaugaBird(Bird("Red",   50, Vector2D(0, 0)));
    joc.adaugaBird(Bird("Chuck", 70, Vector2D(0, 0)));
    joc.adaugaBird(Bird("Bomb",  90, Vector2D(0, 0)));

    joc.adaugaTarget(Target(80,  Vector2D(20, 0)));
    joc.adaugaTarget(Target(100, Vector2D(35, 0)));
    joc.adaugaTarget(Target(120, Vector2D(50, 0)));

    std::cout << "Bine ai venit la Mini Angry Birds (terminal)!\n";
    std::cout << "Scop: distruge toate tintele!\n\n";

    while (true) {
        std::cout << joc << "\n";

        int idxBird = -1;
        if (!readIndex(in,
                "Alege pasarea (0-" +
                std::to_string(static_cast<int>(joc.getNumarPasari()) - 1) + "): ",
                static_cast<int>(joc.getNumarPasari()) - 1,
                idxBird
        )) {
            std::cout << "Input terminat. Iesire.\n";
            break;
        }

        int idxTarget = -1;
        if (!readIndex(in,
                "Alege tinta (0-" +
                std::to_string(static_cast<int>(joc.getNumarTinte()) - 1) + "): ",
                static_cast<int>(joc.getNumarTinte()) - 1,
                idxTarget
        )) {
            std::cout << "Input terminat. Iesire.\n";
            break;
        }

        joc.simuleazaLovitura(
            static_cast<size_t>(idxBird),
            static_cast<size_t>(idxTarget)
        );

        if (joc.toateDistruse()) {
            std::cout << "\nFelicitari! Ai distrus toate tintele!\n";
            break;
        }

        bool again = false;
        if (!readYesNo(in, again)) {
            std::cout << "Input terminat. Iesire.\n";
            break;
        }
        if (!again) break;
    }

    std::cout << "\nStare finala:\n" << joc;
    return 0;
}
