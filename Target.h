//
// Created by matei on 10/28/2025.
//

#ifndef OOP_TARGET_H
#define OOP_TARGET_H

#pragma once
#include <ostream>
#include "Vector2D.h"

class Target {
private:
    int viata;
    Vector2D pozitie;

public:
    // Constructor cu parametri — explicit pentru a evita conversii implicite
    explicit Target(int viata = 100, const Vector2D& poz = Vector2D())
        : viata(viata), pozitie(poz) {}

    bool esteLovit(double putereLovitura) {
        if (putereLovitura > 0) {
            viata -= static_cast<int>(putereLovitura);
            if (viata < 0) viata = 0;
            return true;
        }
        return false;
    }

    // Aceste funcții returnează informație importantă → [[nodiscard]]
    [[nodiscard]] bool esteDistrus() const { return viata <= 0; }
    [[nodiscard]] const Vector2D& getPozitie() const { return pozitie; }

    friend std::ostream& operator<<(std::ostream& os, const Target& t) {
        os << "Target[viata=" << t.viata << ", poz=" << t.pozitie << "]";
        return os;
    }
};

#endif //OOP_TARGET_H