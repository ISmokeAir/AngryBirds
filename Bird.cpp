#include "Bird.h"

Bird::Bird(std::string n, BirdType t, const Vector2D& poz)
    : nume(std::move(n)), masa(1.0), vitezaLansare(10.0), pozitie(poz), tip(t) {

    switch (this->tip) {
        case BirdType::Chuck:
            this->masa = 0.8;
            this->vitezaLansare = 25.0;
            break;
        case BirdType::Bomb:
            this->masa = 3.0;
            this->vitezaLansare = 12.0;
            break;
        case BirdType::Red:
        default:
            this->masa = 1.5;
            this->vitezaLansare = 15.0;
            break;
    }
}

Bird::Bird(const Bird& other)
    : nume(other.nume), masa(other.masa), vitezaLansare(other.vitezaLansare), pozitie(other.pozitie), tip(other.tip) {
}

Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        this->nume = other.nume;
        this->masa = other.masa;
        this->vitezaLansare = other.vitezaLansare;
        this->pozitie = other.pozitie;
        this->tip = other.tip;
    }
    return *this;
}

Bird::~Bird() {
}

double Bird::calculeazaMomentum(double distantaZbor, double vant) const {
    double vitezaReala = this->vitezaLansare;

    vitezaReala += (vant * 0.5);

    double coeficientFrecare = 0.1;
    if (this->tip == BirdType::Chuck) {
        coeficientFrecare = 0.05;
    }

    double pierdereViteza = distantaZbor * coeficientFrecare;
    vitezaReala -= pierdereViteza;

    if (vitezaReala < 0) {
        vitezaReala = 0;
    }

    double momentum = this->masa * vitezaReala * 10.0;

    return momentum;
}

const std::string& Bird::getNume() const { return this->nume; }
double Bird::getMasa() const { return this->masa; }
double Bird::getViteza() const { return this->vitezaLansare; }
const Vector2D& Bird::getPozitie() const { return this->pozitie; }

std::ostream& operator<<(std::ostream& os, const Bird& b) {
    std::string tipStr;
    switch(b.tip) {
        case BirdType::Red: tipStr = "Red"; break;
        case BirdType::Chuck: tipStr = "Chuck"; break;
        case BirdType::Bomb: tipStr = "Bomb"; break;
    }
    os << "Bird " << b.nume << " [" << tipStr << "] (Masa:" << b.masa << "kg, V:" << b.vitezaLansare << "m/s) la " << b.pozitie;
    return os;
}