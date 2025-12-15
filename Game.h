#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <vector>
#include <string>
#include "Bird.h"
#include "Target.h"
#include "Stats.h"

class Game {
private:
    std::vector<Bird> birds;
    std::vector<Target> targets;
    Stats stats;
    double vantCurent;

    void genereazaVant();

public:
    Game();

    void addBird(const Bird& b);
    void addTarget(const Target& t);

    void simulateShot(int birdIdx, int targetIdx);
    void demoRun();
    bool checkWin() const;
    void printState() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif