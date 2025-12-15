#include <iostream>
#include <string>
#include "Game.h"

static int citesteInt(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        int x;
        if (std::cin >> x) return x;

        if (std::cin.eof()) {
            return -1;
        }

        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << "Te rog introdu un numar valid.\n";
    }
}

int main() {
    Game joc;

    joc.addBird(Bird("Red", BirdType::Red, Vector2D(0, 0)));
    joc.addBird(Bird("Chuck", BirdType::Chuck, Vector2D(0, 0)));
    joc.addBird(Bird("Bomb", BirdType::Bomb, Vector2D(0, 0)));
    joc.addBird(Bird("Matilda", BirdType::Red, Vector2D(0, 0)));

    joc.addTarget(Target(50.0, Vector2D(30, 0), Material::Ice));
    joc.addTarget(Target(100.0, Vector2D(50, 0), Material::Wood));
    joc.addTarget(Target(100.0, Vector2D(80, 0), Material::Stone));

    bool ruleaza = true;
    while (ruleaza) {
        std::cout << "\n--- MENIU PRINCIPAL ---\n";
        std::cout << "1. Afiseaza Harta\n";
        std::cout << "2. Seteaza Dificultate\n";
        std::cout << "3. Lanseaza Pasare (Manual)\n";
        std::cout << "4. Simulare AI Avansat\n";
        std::cout << "5. Calculeaza Traiectorie (Predictie)\n";
        std::cout << "6. Iesire\n";

        int optiune = citesteInt("Selectie: ");

        if (optiune == -1) {
            ruleaza = false;
            break;
        }

        switch (optiune) {
            case 1:
                joc.afiseazaStare();
                break;
            case 2: {
                std::cout << "0 = Easy, 1 = Normal, 2 = Hard\n";
                int dif = citesteInt("Alege: ");
                if (dif == -1) { ruleaza = false; break; }

                if (dif == 0) joc.setDifficulty(Difficulty::Easy);
                else if (dif == 1) joc.setDifficulty(Difficulty::Normal);
                else if (dif == 2) joc.setDifficulty(Difficulty::Hard);
                else std::cout << "Invalid.\n";
                break;
            }
            case 3: {
                joc.afiseazaStare();
                int bIdx = citesteInt("Alege Pasare (index): ");
                if (bIdx == -1) { ruleaza = false; break; }

                int tIdx = citesteInt("Alege Tinta (index): ");
                if (tIdx == -1) { ruleaza = false; break; }

                joc.lanseazaPasare(bIdx, tIdx);

                if (joc.verificaVictorie()) {
                    std::cout << "\nVICTORIE! Toate tintele au fost distruse!\n";
                    ruleaza = false;
                }
                break;
            }
            case 4:
                joc.ruleazaDemoAvansat();
                break;
            case 5: {
                // NOU: Optiune de meniu pentru predictie
                joc.afiseazaStare();
                int bIdx = citesteInt("Pasare pentru predictie: ");
                if (bIdx == -1) { ruleaza = false; break; }
                int tIdx = citesteInt("Tinta pentru predictie: ");
                if (tIdx == -1) { ruleaza = false; break; }

                joc.predicteazaTraiectorie(bIdx, tIdx);
                break;
            }
            case 6:
                ruleaza = false;
                break;
            default:
                std::cout << "Optiune invalida.\n";
        }
    }

    return 0;
}