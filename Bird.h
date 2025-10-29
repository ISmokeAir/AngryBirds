//
// Created by matei on 10/28/2025.
//

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
    // Constructor cu parametri
    explicit Bird(std::string nume = "Anonim", int putere = 0, const Vector2D& poz = Vector2D())
        : nume(std::move(nume)), putere(putere), pozitie(poz) {}

    // Constructor de copiere generat automat
    Bird(const Bird&) = default;

    // Operator= generat automat
    Bird& operator=(const Bird&) = default;

    // Destructor generat automat
    ~Bird() = default;

    // Funcție netrivială: calculează forța efectivă a loviturii
    [[nodiscard]] double lanseaza(const Vector2D& tinta) const {
        double dist = pozitie.distanta(tinta);
        return putere - dist;
    }

    // Getteri
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] int getPutere() const { return putere; }
    [[nodiscard]] const Vector2D& getPozitie() const { return pozitie; }

    // Operator << pentru afișare frumoasă
    friend std::ostream& operator<<(std::ostream& os, const Bird& b) {
        os << "Bird[" << b.nume << ", putere=" << b.putere << ", poz=" << b.pozitie << "]";
        return os;
    }
};


#endif //OOP_BIRD_H

