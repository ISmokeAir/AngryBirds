#include "MyBirds.h"
#include <iostream>

RedBird::RedBird(const Vector2D& poz) 
    : Bird("Red", 1.5, 15.0, poz) {}

double RedBird::calculeazaMomentum(double distantaZbor, double vant) const {

    double v = vitezaLansare + (vant * 0.5) - (distantaZbor * 0.1);
    if (v < 0) v = 0;
    return masa * v * 10.0;
}

Bird* RedBird::clone() const {
    return new RedBird(*this);
}

void RedBird::afiseaza(std::ostream& os) const {
    os << "[RedBird] " << nume << " (Standard)";
}


ChuckBird::ChuckBird(const Vector2D& poz)
    : Bird("Chuck", 0.8, 25.0, poz) {}

double ChuckBird::calculeazaMomentum(double distantaZbor, double vant) const {

    double v = vitezaLansare + (vant * 0.8) - (distantaZbor * 0.05); 
    if (v < 0) v = 0;
    return masa * v * 10.0;
}

Bird* ChuckBird::clone() const {
    return new ChuckBird(*this);
}

void ChuckBird::afiseaza(std::ostream& os) const {
    os << "[ChuckBird] " << nume << " (Viteza)";
}


BombBird::BombBird(const Vector2D& poz)
    : Bird("Bomb", 3.0, 12.0, poz) {}

double BombBird::calculeazaMomentum(double distantaZbor, double vant) const {

    double v = vitezaLansare + (vant * 0.2) - (distantaZbor * 0.2);
    if (v < 0) v = 0;
    return masa * v * 12.0;
}

Bird* BombBird::clone() const {
    return new BombBird(*this);
}

void BombBird::activeazaExplozie() const {
    std::cout << ">>> BOMB BIRD: KABOOM! Explozie activata! <<<\n";
}

void BombBird::afiseaza(std::ostream& os) const {
    os << "[BombBird] " << nume << " (Exploziv)";
}