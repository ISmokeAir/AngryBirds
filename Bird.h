#ifndef OOP_BIRD_H
#define OOP_BIRD_H

#pragma once
#include <string>
#include <iostream>
#include "Vector2D.h"

enum class BirdType {
    Red,
    Chuck,
    Bomb
};

class Bird {
private:
    std::string nume;
    int putere;
    Vector2D pozitie;
    BirdType tip;

public:
    explicit Bird(std::string nume = "Anonim", int putere = 0, const Vector2D& poz = Vector2D(), BirdType tip = BirdType::Red);

    Bird(const Bird& other);
    Bird& operator=(const Bird& other);
    ~Bird();

    [[nodiscard]] double calculeazaImpact(const Vector2D& tinta, double vant) const;

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] int getPutere() const;
    [[nodiscard]] const Vector2D& getPozitie() const;
    [[nodiscard]] BirdType getTip() const;

    friend std::ostream& operator<<(std::ostream& os, const Bird& b);
};

#endif