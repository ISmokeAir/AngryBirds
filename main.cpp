#include <iostream>
#include <string>
#include <limits>
#include "Game.h"
#include "Exceptions.h"


static int citesteInt(const std::string& mesaj) {
    std::cout << mesaj;
    int x;
    if (!(std::cin >> x)) {
        if (std::cin.eof()) return -1;
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);

        std::cout << "Input invalid!\n";
        return -999;
    }
    return x;
}

int main() {
    try {
        Game joc;


        joc.addBird(new RedBird(Vector2D(0, 0)));
        joc.addBird(new ChuckBird(Vector2D(0, 0)));
        joc.addBird(new BombBird(Vector2D(0, 0)));


        joc.addTarget(Target(50.0, Vector2D(30, 0), Material::Ice));
        joc.addTarget(Target(100.0, Vector2D(50, 0), Material::Wood));
        joc.addTarget(Target(100.0, Vector2D(80, 0), Material::Stone));

        bool ruleaza = true;
        while (ruleaza) {
            std::cout << "\n--- ANGRY BIRDS (TEMA 2) ---\n";
            std::cout << "1. Afiseaza Harta\n";
            std::cout << "2. Seteaza Dificultate\n";
            std::cout << "3. Lanseaza Pasare (Manual)\n";
            std::cout << "4. DEMO AI (Simulare)\n";
            std::cout << "5. Predictie Traiectorie\n";
            std::cout << "6. Iesire\n";

            int opt = citesteInt("Selectie: ");
            if (opt == -1) break;

            try {
                switch (opt) {
                    case 1:
                        std::cout << joc;
                        break;
                    case 2: {
                        int d = citesteInt("0=Easy, 1=Normal, 2=Hard: ");
                        if (d >= 0 && d <= 2) joc.setDifficulty((Difficulty)d);
                        break;
                    }
                    case 3: {
                        int b = citesteInt("Idx Pasare: ");
                        int t = citesteInt("Idx Tinta: ");
                        joc.lanseazaPasare(b, t);
                        break;
                    }
                    case 4:
                        joc.ruleazaDemoAvansat();
                        break;
                    case 5: {
                        int b = citesteInt("Idx Pasare: ");
                        int t = citesteInt("Idx Tinta: ");
                        joc.predicteazaTraiectorie(b, t);
                        break;
                    }
                    case 6:
                        ruleaza = false;
                        break;
                    default:
                        if (opt != -999) std::cout << "Optiune necunoscuta.\n";
                }
            }
            catch (const GameException& e) {
                std::cerr << "[!] Eroare Joc: " << e.what() << "\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << "\n";
    }

    return 0;
}