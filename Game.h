#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include <vector>
#include <string>
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

    // NOU: Istoric pentru logging
    std::vector<std::string> istoricActiuni;

    void updateVant();
    double calculeazaScorStrategic(int birdIdx, int targetIdx) const;

    // NOU: Functii interne pentru sistemul de logging
    void logActiune(const std::string& actiune);
    void salveazaLogPeDisk() const;

public:
    Game();
    ~Game(); // Destructorul va salva fisierul automat

    void addBird(const Bird& b);
    void addTarget(const Target& t);

    void setDifficulty(Difficulty d);

    void lanseazaPasare(int birdIdx, int targetIdx);

    // NOU: Functie complexa de matematica
    void predicteazaTraiectorie(int birdIdx, int targetIdx) const;

    void ruleazaDemoAvansat();

    bool verificaVictorie() const;
    void afiseazaStare() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif