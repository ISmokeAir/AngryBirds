#include "Bird.h"

int Bird::numarPasari = 0;

Bird::Bird(std::string nume, double masa, double viteza, double factorAero, const Vector2D& poz)
    : nume(std::move(nume)), masa(masa), vitezaLansare(viteza), factorAerodinamic(factorAero), pozitie(poz) {
    numarPasari++;
}

Bird::~Bird() {
    numarPasari--;
}

double Bird::calculeazaMomentum(double distantaZbor, double vant) const {
    double v = vitezaLansare + (vant * factorAerodinamic) - (distantaZbor * 0.1);
    if (v < 0) v = 0;
    return masa * v * 10.0;
}

const std::string& Bird::getNume() const { return nume; }
const Vector2D& Bird::getPozitie() const { return pozitie; }
double Bird::getMasa() const { return masa; }
double Bird::getViteza() const { return vitezaLansare; }

int Bird::getNumarTotalPasari() {
    return numarPasari;
}

std::ostream& operator<<(std::ostream& os, const Bird& b) {
    b.afiseaza(os);
    return os;
}

void Bird::afiseaza(std::ostream& os) const {
    os << "Bird (Baza): " << nume;
}