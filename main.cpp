#include <iostream>
#include <string>
#include "Game.h"
#include "Exceptions.h"
#include "MapGenerator.h"
#include "TextUI.h"
#include "GameContainer.h"

template <typename T>
void debugLog(const T& valoare, const std::string& mesaj) {
    std::cout << "[DEBUG] " << mesaj << ": " << valoare << "\n";
}

static int citesteInt(const std::string& mesaj) {
    std::cout << mesaj;
    int x;
    if (!(std::cin >> x)) {
        if (std::cin.eof()) return -1;
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        return -999;
    }
    return x;
}

int main() {
    try {
        GameContainer<int> scoruriSesiune(5, "Scoruri Recente");
        scoruriSesiune.add(100);
        scoruriSesiune.add(250);

        Game joc;
        joc.addBird(new RedBird(Vector2D(0,0)));
        joc.addBird(new ChuckBird(Vector2D(0,0)));
        joc.addBird(new BombBird(Vector2D(0,0)));
        joc.addBird(new MatildaBird(Vector2D(0,0)));

        joc.loadMap(MapGenerator::generateClassicLevel());
        joc.addTarget(Target(50.0, Vector2D(95, 0), Material::Wood));

        bool ruleaza = true;
        while(ruleaza) {
            TextUI::drawHeader("ANGRY BIRDS FINAL PROJECT");
            std::vector<std::string> meniu = {
                "Afiseaza Harta", "Schimba Dificultate", "Lanseaza", "DEMO AI",
                "Predictie", "Super Computer", "Achievements",
                "Magazin", "Wall Map", "Pyramid Map", "Chaos Map",
                "Replay Last Match", "Iesire"
            };
            TextUI::drawMenu(meniu);

            int opt = citesteInt("");
            if (opt == -1) break;

            try {
                switch(opt) {
                    case 1: joc.afiseazaStare(); break;
                    case 2: {
                        std::cout << "\nALEGE DIFICULTATE:\n";
                        std::cout << "1. Usor\n2. Normal\n3. Greu\nSelectie: ";
                        int d = citesteInt("");
                        if(d >= 1 && d <= 3) {
                            joc.setDifficulty(static_cast<Difficulty>(d - 1));
                        } else {
                            std::cout << "Selectie invalida. Ramane neschimbat.\n";
                        }
                        break;
                    }
                    case 3: {
                        int b = citesteInt("Bird:"); int t = citesteInt("Target:");
                        joc.lanseazaPasare(b, t);
                        break;
                    }
                    case 4: joc.ruleazaDemoAvansat(); break;
                    case 5: {
                        int b = citesteInt("Bird:"); int t = citesteInt("Target:");
                        joc.predicteazaTraiectorie(b, t);
                        break;
                    }
                    case 6: joc.activeazaSuperComputer(); break;
                    case 7: joc.afiseazaAchievements(); break;
                    case 8: joc.acceseazaMagazin(); break;
                    case 9: joc.loadMap(MapGenerator::generateWallLevel()); break;
                    case 10: joc.loadMap(MapGenerator::generatePyramidLevel()); break;
                    case 11: joc.loadMap(MapGenerator::generateRandomChaos()); break;
                    case 12: joc.ruleazaReplay(); break;
                    case 13: ruleaza = false; break;
                    default: if(opt != -999) std::cout << "Invalid.\n";
                }
            } catch (const std::exception& e) {
                std::cerr << e.what() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}