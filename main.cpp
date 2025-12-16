#include <iostream>
#include <string>
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

        joc.addTarget(Target(200.0, Vector2D(30,0), Material::Ice));
        joc.addTarget(Target(500.0, Vector2D(50,0), Material::Wood));
        joc.addTarget(Target(1000.0, Vector2D(80,0), Material::Stone));

        bool ruleaza = true;
        while(ruleaza) {
            std::cout << "\n--- ANGRY BIRDS PRO (v0.2) ---\n";
            std::cout << "1. Afiseaza Harta\n";
            std::cout << "2. Seteaza Dificultate\n";
            std::cout << "3. Lanseaza Pasare\n";
            std::cout << "4. DEMO AI\n";
            std::cout << "5. Predictie\n";
            std::cout << "6. Achievement-uri (NOU)\n";
            std::cout << "7. Iesire\n";

            int opt = citesteInt("Optiune: ");
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
                    case 7: ruleaza = false; break;
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