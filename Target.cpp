#include "Target.h"
#include "Utils.h"
#include <string>
#include <cmath>

Target::Target(double integritate, const Vector2D& p, Material m)
    : integritateStructura(integritate), integritateMaxima(integritate), pozitie(p), material(m), factorArmura(1.0) {

    switch (this->material) {
        case Material::Stone: factorArmura = 2.5; break;
        case Material::Wood: factorArmura = 1.0; break;
        case Material::Ice: factorArmura = 0.5; break;
    }
    if (this->integritateStructura < 0) this->integritateStructura = 0;
}

Target::Target(const Target& other)
    : integritateStructura(other.integritateStructura),
      integritateMaxima(other.integritateMaxima),
      pozitie(other.pozitie),
      material(other.material),
      factorArmura(other.factorArmura) {
}

Target& Target::operator=(const Target& other) {
    if (this != &other) {
        this->integritateStructura = other.integritateStructura;
        this->integritateMaxima = other.integritateMaxima;
        this->pozitie = other.pozitie;
        this->material = other.material;
        this->factorArmura = other.factorArmura;
    }
    return *this;
}

Target::~Target() {
}

void Target::scaleazaDificultate(double multiplicatorHp, double multiplicatorArmura) {
    this->integritateMaxima *= multiplicatorHp;
    this->integritateStructura = this->integritateMaxima;
    this->factorArmura *= multiplicatorArmura;
}

bool Target::aplicaImpact(double fortaImpact) {
    if (this->integritateStructura <= 0 || fortaImpact <= 0.0) return false;

    double fortaEfectiva = Utils::clamp(fortaImpact, 0.0, 10000.0);

    double damageReceptat = (fortaEfectiva / this->factorArmura);

    if (fortaEfectiva > 10.0) {
        damageReceptat *= std::log10(fortaEfectiva);
    }

    if (this->material == Material::Ice) {
        damageReceptat = std::pow(damageReceptat, 1.1);
    } else if (this->material == Material::Stone) {
        if (damageReceptat < 20.0) damageReceptat *= 0.1;
    }

    this->integritateStructura -= damageReceptat;
    if (this->integritateStructura < 0) this->integritateStructura = 0;

    return true;
}

bool Target::esteDistrus() const { return this->integritateStructura <= 0.001; }
double Target::getIntegritate() const { return this->integritateStructura; }
double Target::getIntegritateMaxima() const { return this->integritateMaxima; }
const Vector2D& Target::getPozitie() const { return this->pozitie; }
Material Target::getMaterial() const { return this->material; }
double Target::getArmura() const { return this->factorArmura; }

std::ostream& operator<<(std::ostream& os, const Target& t) {
    std::string matStr;
    switch(t.material) {
        case Material::Wood: matStr = "Lemn"; break;
        case Material::Stone: matStr = "Piatra"; break;
        case Material::Ice: matStr = "Gheata"; break;
    }
    os << "Target [" << matStr << "] (Arm:" << t.factorArmura << ") HP:" << (int)t.integritateStructura << "/" << (int)t.integritateMaxima << " @ " << t.pozitie;
    return os;
}