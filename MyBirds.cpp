#include "MyBirds.h"
#include <iostream>

RedBird::RedBird(const Vector2D& poz) 
    : Bird("Red", 1.5, 15.0, poz) {}

double RedBird::calculeazaMomentum(double distantaZbor, double vant) const {
    double v = vitezaLansare + (vant * 0.5) - (distantaZbor * 0.1);
    if (v < 0) v = 0;
    return masa * v * 10.0;
}

Bird* RedBird::clone() const { return new RedBird(*this); }
void RedBird::afiseaza(std::ostream& os) const { os << "Pasare Rosie [" << nume << "]"; }


ChuckBird::ChuckBird(const Vector2D& poz)
    : Bird("Chuck", 0.8, 25.0, poz) {}

double ChuckBird::calculeazaMomentum(double distantaZbor, double vant) const {
    double v = vitezaLansare + (vant * 0.8) - (distantaZbor * 0.05);
    if (v < 0) v = 0;
    return masa * v * 10.0;
}

Bird* ChuckBird::clone() const { return new ChuckBird(*this); }
void ChuckBird::afiseaza(std::ostream& os) const { os << "Pasare Galbena [" << nume << "] (Viteza)"; }


BombBird::BombBird(const Vector2D& poz)
    : Bird("Bomb", 3.0, 12.0, poz) {}

double BombBird::calculeazaMomentum(double distantaZbor, double vant) const {
    double v = vitezaLansare + (vant * 0.2) - (distantaZbor * 0.2);
    if (v < 0) v = 0;
    return masa * v * 12.0;
}

Bird* BombBird::clone() const { return new BombBird(*this); }
void BombBird::activeazaExplozie() const { std::cout << ">>> BOMB BIRD: KABOOM! Explozie activata! <<<\n"; }
void BombBird::afiseaza(std::ostream& os) const { os << "Pasare Neagra [" << nume << "] (Exploziv)"; }


// --- IMPLEMENTARE MATILDA BIRD ---
MatildaBird::MatildaBird(const Vector2D& poz)
    : Bird("Matilda", 1.8, 22.0, poz) {}

double MatildaBird::calculeazaMomentum(double distantaZbor, double vant) const {
    double v = vitezaLansare;

    if (distantaZbor > 40.0 && distantaZbor < 80.0) {
        v *= 1.6;
    }

    v = v + (vant * 0.3) - (distantaZbor * 0.02);

    if (v < 0) v = 0;

    return masa * v * 12.0;
}

Bird* MatildaBird::clone() const {
    return new MatildaBird(*this);
}

void MatildaBird::afiseaza(std::ostream& os) const {
    os << "Pasare Alba [" << nume << "] (Egg Drop Bomber)";
}