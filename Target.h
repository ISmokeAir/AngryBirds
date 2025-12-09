#pragma once
#include <ostream>
#include "Vector2D.h"

class Target {
private:
    int viata;
    Vector2D pozitie;

public:

    explicit Target(int viata = 100, const Vector2D& poz = Vector2D())
        : viata(viata), pozitie(poz) {}

    Target(const Target&) = default;
    Target& operator=(const Target&) = default;
    ~Target() = default;

    [[nodiscard]] bool esteLovit(double putereLovitura) const {
        if (viata <= 0) return false;
        return putereLovitura >= viata;
    }

    bool esteLovit(double putereLovitura) {
        if (putereLovitura > 0) {
            viata -= static_cast<int>(putereLovitura);
            if (viata < 0) viata = 0;
            return true;
        }
        return false;
    }


    void iaDamage(int damage) {
        if (damage <= 0) return;
        viata -= damage;
        if (viata < 0) viata = 0;
    }

    [[nodiscard]] int getViata() const { return viata; }
    void setViata(int v) { viata = v; if (viata < 0) viata = 0; }

    [[nodiscard]] bool esteDistrus() const { return viata <= 0; }
    [[nodiscard]] const Vector2D& getPozitie() const { return pozitie; }

    friend std::ostream& operator<<(std::ostream& os, const Target& t) {
        os << "Target[viata=" << t.viata << ", poz=" << t.pozitie << "]";
        return os;
    }
};