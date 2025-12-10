#include <iostream>
#include <string>
//#include <limits>
#include "Game.h"
#include "Vector2D.h"

static int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int x;
        if (std::cin >> x) return x;
        if (std::cin.eof()) return -1;
        std::cin.clear();
        std::string dummy;
        std::getline(std::cin, dummy);
        std::cout << "Invalid input\n";
    }
}

static std::string difficultyName(Game::Difficulty d) {
    switch (d) {
        case Game::Difficulty::Easy: return "Easy";
        case Game::Difficulty::Normal: return "Normal";
        case Game::Difficulty::Hard: return "Hard";
    }
    return "Unknown";
}

int main() {
    Game game;

    game.addBird(Bird("Red", 50, Vector2D(0,0)));
    game.addBird(Bird("Chuck", 70, Vector2D(0,0)));
    game.addBird(Bird("Bomb", 90, Vector2D(0,0)));

    game.addTarget(Target(80, Vector2D(20,0)));
    game.addTarget(Target(100, Vector2D(35,0)));
    game.addTarget(Target(120, Vector2D(50,0)));

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1 Play (manual)\n";
        std::cout << "2 Demo\n";
        std::cout << "3 Save\n";
        std::cout << "4 Load\n";
        std::cout << "5 Reset\n";
        std::cout << "6 Stats (full)\n";
        std::cout << "7 Show Game\n";
        std::cout << "8 Set Difficulty\n";
        std::cout << "9 Show Distances\n";
        std::cout << "10 Closest target for bird 0\n";
        std::cout << "11 Quit\n";

        int choice = readInt("Choice: ");
        if (choice == -1 || choice == 11) break;

        switch (choice) {
            case 1: {
                std::cout << game << "\n";
                int bi = readInt("Bird idx: ");
                int ti = readInt("Target idx: ");
                if (bi >= 0 && ti >= 0)
                    game.simulateShot(static_cast<size_t>(bi), static_cast<size_t>(ti));
                break;
            }
            case 2:
                game.demoRun();
                std::cout << "Demo finished\n";
                break;
            case 3: {
                std::string fn;
                std::cout << "Save filename: ";
                std::cin >> fn;
                try { game.save(fn); std::cout << "Saved\n"; } catch (...) { std::cout << "Save failed\n"; }
                break;
            }
            case 4: {
                std::string fn;
                std::cout << "Load filename: ";
                std::cin >> fn;
                try { game.load(fn); std::cout << "Loaded\n"; } catch (...) { std::cout << "Load failed\n"; }
                break;
            }
            case 5:
                game.resetToInitial();
                std::cout << "Reset to initial\n";
                break;
            case 6: {
                std::cout << game.getStats();
                std::cout << "Detailed stats (accessors):\n";
                std::cout << "Total shots: " << game.getStats().getTotalShots() << "\n";
                std::cout << "Successful shots: " << game.getStats().getSuccessfulShots() << "\n";
                std::cout << "Total damage: " << game.getStats().getTotalDamage() << "\n";
                std::cout << "Total distance: " << game.getStats().getTotalDistance() << "\n";
                break;
            }
            case 7:
                std::cout << game << "\n";
                std::cout << "Num birds: " << game.getNumBirds() << ", Num targets: " << game.getNumTargets() << "\n";
                std::cout << "Difficulty: " << difficultyName(game.getDifficulty()) << "\n";
                break;
            case 8: {
                std::cout << "Set difficulty: 0 Easy, 1 Normal, 2 Hard\n";
                int d = readInt("Choice: ");
                if (d == 0) game.setDifficulty(Game::Difficulty::Easy);
                else if (d == 1) game.setDifficulty(Game::Difficulty::Normal);
                else if (d == 2) game.setDifficulty(Game::Difficulty::Hard);
                std::cout << "Difficulty now: " << difficultyName(game.getDifficulty()) << "\n";
                break;
            }
            case 9: {
                auto all = game.computeAllDistances();
                std::cout << "Distances count: " << all.size() << "\n";
                for (size_t i = 0; i < all.size() && i < 10; ++i)
                    std::cout << "d[" << i << "]=" << all[i] << "\n";
                break;
            }
            case 10: {
                if (game.getNumBirds() > 0) {
                    int idx = game.closestTargetIndex(Bird("tmp", 0, Vector2D(0,0)).getPozitie());
                    std::cout << "Closest target index to (0,0): " << idx << "\n";
                } else {
                    std::cout << "No birds available\n";
                }
                break;
            }
            default:
                std::cout << "Unknown\n";
        }
    }

    return 0;
}
