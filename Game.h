#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include <vector>
#include "Bird.h"
#include "Target.h"
#include "Stats.h"

enum class Difficulty {
    Easy,
    Normal,
    Hard
};

class Game {
private:
    std::vector<Bird> birds;
    std::vector<Target> targets;
    Stats stats;
    double vantCurrent;
    Difficulty dificultate;

    void updateVant();
    double calculeazaScorStrategic(int birdIdx, int targetIdx) const;

public:
    Game();

    void addBird(const Bird& b);
    void addTarget(const Target& t);

    void setDifficulty(Difficulty d);

    void lanseazaPasare(int birdIdx, int targetIdx);

    void ruleazaDemoAvansat();

    bool verificaVictorie() const;
    void afiseazaStare() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif