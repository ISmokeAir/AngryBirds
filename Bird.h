#ifndef OOP_BIRD_H
#define OOP_BIRD_H

#pragma once
#include <iostream>
#include <string>
#include "Vector2D.h"

class Bird {
private:
    std::string nume;
    int putere;
    Vector2D pozitie;

public:
    explicit Bird(std::string nume = "Anonim", int putere = 0, const Vector2D& poz = Vector2D())
        : nume(std::move(nume)), putere(putere), pozitie(poz) {}


    Bird(const Bird&) = default;


    Bird& operator=(const Bird&) = default;


    ~Bird() = default;


    [[nodiscard]] double lanseaza(const Vector2D& tinta) const {
        double dist = pozitie.distanta(tinta);
        return putere - dist;
    }


    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] int getPutere() const { return putere; }
    [[nodiscard]] const Vector2D& getPozitie() const { return pozitie; }


    friend std::ostream& operator<<(std::ostream& os, const Bird& b) {
        os << "Bird[" << b.nume
           << ", putere=" << b.getPutere()
           << ", poz=" << b.pozitie << "]";
        return os;
    }


};


#endif //OOP_BIRD_H