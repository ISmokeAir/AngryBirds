#ifndef OOP_BIRD_H
#define OOP_BIRD_H

#pragma once
#include <string>
#include "Vector2D.h"

enum class BirdType {
    Red,
    Chuck,
    Bomb
};

class Bird {
private:
    std::string nume;
    double masa;
    double vitezaLansare;
    Vector2D pozitie;
    BirdType tip;

public:
    explicit Bird(std::string nume = "Anonim", BirdType tip = BirdType::Red, const Vector2D& poz = Vector2D());
    Bird(const Bird& other);
    Bird& operator=(const Bird& other);
    ~Bird();

    double calculeazaMomentum(double distantaZbor, double vant) const;

    const std::string& getNume() const;
    double getMasa() const;
    double getViteza() const;
    const Vector2D& getPozitie() const;

    friend std::ostream& operator<<(std::ostream& os, const Bird& b);
};

#endif