#include <iostream>
#include <limits>
#include "Game.h"

int main() {
    Game joc;

    // Inițializare păsări și ținte
    joc.adaugaBird(Bird("Red", 50, Vector2D(0, 0)));
    joc.adaugaBird(Bird("Chuck", 70, Vector2D(0, 0)));
    joc.adaugaBird(Bird("Bomb", 90, Vector2D(0, 0)));

    joc.adaugaTarget(Target(80, Vector2D(20, 0)));
    joc.adaugaTarget(Target(100, Vector2D(35, 0)));
    joc.adaugaTarget(Target(120, Vector2D(50, 0)));

    std::cout << "Bine ai venit la Angry Birds (versiunea terminal)!\n";
    std::cout << "Scop: Distruge toate tintele!\n\n";

    bool jocActiv = true;
    while (jocActiv) {
        std::cout << joc << "\n";

        int idxBird, idxTarget;
        std::cout << "Alege pasarea (0-" << joc.getNumarPasari() - 1 << "): ";
        std::cin >> idxBird;

        std::cout << "Alege tinta (0-" << joc.getNumarTinte() - 1 << "): ";
        std::cin >> idxTarget;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input invalid! Incearca din nou.\n";
            continue;
        }

        joc.simuleazaLovitura(idxBird, idxTarget);

        // Verificare dacă toate țintele sunt distruse
        if (joc.toateDistruse()) {
            std::cout << "\n Felicitari! Ai distrus toate tintele!\n";
            break;
        }

        char cont;
        std::cout << "\nVrei sa tragi din nou? (y/n): ";
        std::cin >> cont;
        if (cont != 'y' && cont != 'Y') {
            jocActiv = false;
        }
    }

    std::cout << "\n Stare finala:\n" << joc;
    std::cout << "\nMultumim că ai jucat Angry Birds!\n";

    return 0;
}
