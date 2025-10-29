//
// Created by matei on 10/28/2025.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include <iostream>
#include <vector>
#include "Bird.h"
#include "Target.h"

class Game {
    std::vector<Bird> birds;
    std::vector<Target> targets;

public:
    void adaugaBird(const Bird& b);
    void adaugaTarget(const Target& t);
    void simuleazaLovitura(size_t idxBird, size_t idxTarget);
    [[nodiscard]] size_t getNumarPasari() const;
    [[nodiscard]] size_t getNumarTinte() const;
    [[nodiscard]] bool toateDistruse() const;



    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};


#endif //OOP_GAME_H