#include <iostream>
#include <string>
#include "Game.h"
#include "Exceptions.h"
#include "MapGenerator.h"
#include "TextUI.h"

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
        Game joc;
        joc.addBird(new RedBird(Vector2D(0,0)));
        joc.addBird(new ChuckBird(Vector2D(0,0)));
        joc.addBird(new BombBird(Vector2D(0,0)));

        joc.loadMap(MapGenerator::generateClassicLevel());

        bool ruleaza = true;
        while(ruleaza) {
            TextUI::drawHeader("ANGRY BIRDS PRO (v0.3)");
            std::vector<std::string> meniu = {
                "Afiseaza Harta",
                "Seteaza Dificultate",
                "Lanseaza Pasare",
                "DEMO AI",
                "Predictie",
                "Achievement-uri",
                "Genereaza Harta (Zid)",
                "Genereaza Harta (Piramida)",
                "Genereaza Harta (Chaos)",
                "Iesire"
            };
            TextUI::drawMenu(meniu);

            int opt = citesteInt("");
            if (opt == -1) break;

            try {
                switch(opt) {
                    case 1: std::cout << joc; break;
                    case 2: {
                        int d = citesteInt("0=Easy, 1=Normal, 2=Hard: ");
                        if(d>=0 && d<=2) joc.setDifficulty((Difficulty)d);
                        break;
                    }
                    case 3: {
                        int b = citesteInt("Idx Bird: ");
                        int t = citesteInt("Idx Tinta: ");
                        joc.lanseazaPasare(b, t);
                        break;
                    }
                    case 4: joc.ruleazaDemoAvansat(); break;
                    case 5: {
                        int b = citesteInt("Idx Bird: ");
                        int t = citesteInt("Idx Tinta: ");
                        joc.predicteazaTraiectorie(b, t);
                        break;
                    }
                    case 6: joc.afiseazaAchievements(); break;
                    case 7: joc.loadMap(MapGenerator::generateWallLevel()); break;
                    case 8: joc.loadMap(MapGenerator::generatePyramidLevel()); break;
                    case 9: joc.loadMap(MapGenerator::generateRandomChaos()); break;
                    case 10: ruleaza = false; break;
                    default: if(opt != -999) std::cout << "Invalid.\n";
                }
            } catch (const GameException& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << "\n";
    }
    return 0;
}