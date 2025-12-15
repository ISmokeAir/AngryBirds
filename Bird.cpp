#include "Bird.h"
#include <algorithm>

Bird::Bird(std::string n, int p, const Vector2D& pos, BirdType t)
    : nume(std::move(n)), putere(p), pozitie(pos), tip(t) {}

Bird::Bird(const Bird& other) 
    : nume(other.nume), putere(other.putere), pozitie(other.pozitie), tip(other.tip) {
}

Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        nume = other.nume;
        putere = other.putere;
        pozitie = other.pozitie;
        tip = other.tip;
    }
    return *this;
}

Bird::~Bird() {
}

double Bird::calculeazaImpact(const Vector2D& tintaPos, double vant) const {
    double dist = pozitie.distanta(tintaPos);
    
    double distantaEfectiva = dist;
    if (vant != 0) {
        distantaEfectiva -= vant;
    }
    if (distantaEfectiva < 0) distantaEfectiva = 0;

    double damage = 0.0;

    switch (tip) {
        case BirdType::Chuck:
            if (distantaEfectiva < putere) {
                damage = putere * 1.5;
            } else {
                damage = putere * 0.8;
            }
            break;
        case BirdType::Bomb:
            if (distantaEfectiva < putere * 0.5) {
                damage = putere * 2.0;
            } else if (distantaEfectiva < putere) {
                damage = putere;
            } else {
                damage = 0.0;
            }
            break;
        case BirdType::Red:
        default:
            double factor = 1.0 - (distantaEfectiva / (putere * 3.0));
            if (factor < 0) factor = 0;
            damage = putere * factor;
            break;
    }

    return damage;
}

const std::string& Bird::getNume() const { return nume; }
int Bird::getPutere() const { return putere; }
const Vector2D& Bird::getPozitie() const { return pozitie; }
BirdType Bird::getTip() const { return tip; }

std::ostream& operator<<(std::ostream& os, const Bird& b) {
    std::string tipStr;
    switch(b.tip) {
        case BirdType::Red: tipStr = "Red"; break;
        case BirdType::Chuck: tipStr = "Chuck"; break;
        case BirdType::Bomb: tipStr = "Bomb"; break;
    }
    os << "Bird " << b.nume << " [" << tipStr << "] (P:" << b.putere << ") la " << b.pozitie;
    return os;
}