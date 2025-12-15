#include <iostream>
#include <string>
#include "Game.h"

static int readInt(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        int x;
        if (std::cin >> x) return x;
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << "Input invalid! Introdu un numar.\n";
    }
}

int main() {
    Game game;

    game.addBird(Bird("Red", 50, Vector2D(0, 0), BirdType::Red));
    game.addBird(Bird("Chuck", 60, Vector2D(0, 0), BirdType::Chuck));
    game.addBird(Bird("Bomb", 80, Vector2D(0, 0), BirdType::Bomb));
    game.addBird(Bird("Terence", 90, Vector2D(0, 0), BirdType::Red));

    game.addTarget(Target(50, Vector2D(30, 0), Material::Ice));
    game.addTarget(Target(100, Vector2D(50, 0), Material::Wood));
    game.addTarget(Target(100, Vector2D(70, 0), Material::Stone));

    bool running = true;
    while (running) {
        std::cout << "\n--- ANGRY BIRDS CPP EDITION ---\n";
        std::cout << "1. Afiseaza Stare Joc\n";
        std::cout << "2. Trage Manual\n";
        std::cout << "3. Auto Simulare (Demo)\n";
        std::cout << "4. Iesire\n";

        int choice = readInt("Alege optiunea: ");

        switch (choice) {
            case 1:
                game.printState();
                break;
            case 2: {
                game.printState();
                std::cout << "\nSelecteaza indexul pasarii si al tintei.\n";
                int bIdx = readInt("Index Pasare: ");
                int tIdx = readInt("Index Tinta: ");

                game.simulateShot(bIdx, tIdx);

                if (game.checkWin()) {
                    std::cout << "\nFELICITARI! AI DISTRUS TOATE TINTELE!\n";
                    running = false;
                }
                break;
            }
            case 3:
                game.demoRun();
                if (game.checkWin()) running = false;
                break;
            case 4:
                running = false;
                break;
            default:
                std::cout << "Optiune necunoscuta.\n";
        }
    }

    std::cout << "Joc terminat. La revedere!\n";
    return 0;
}