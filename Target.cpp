#include "Target.h"

Target::Target(int v, const Vector2D& p, Material m) 
    : viata(v), pozitie(p), material(m) {}

Target::Target(const Target& other) = default;
Target& Target::operator=(const Target& other) = default;
Target::~Target() = default;

bool Target::incaseazaDamage(double damageBrut) {
    if (viata <= 0 || damageBrut <= 0) return false;

    double damageFinal = damageBrut;

    switch (material) {
        case Material::Stone:
            damageFinal *= 0.5;
            break;
        case Material::Ice:
            damageFinal *= 1.5;
            break;
        case Material::Wood:
        default:
            break;
    }

    int dmg = static_cast<int>(damageFinal);
    if (dmg < 1) dmg = 1;

    viata -= dmg;
    if (viata < 0) viata = 0;
    
    return true;
}

bool Target::esteDistrus() const {
    return viata <= 0;
}

int Target::getViata() const {
    return viata;
}

const Vector2D& Target::getPozitie() const {
    return pozitie;
}
std::ostream& operator<<(std::ostream& os, const Target& t) {
    std::string protectie;
    switch(t.material) {
        case Material::Wood: protectie = "Lemn"; break;
        case Material::Stone: protectie = "Piatra"; break;
        case Material::Ice: protectie = "Gheata"; break;
    }

    os << "Porcusor [Protectie: " << protectie << "] HP:" << t.viata << " la " << t.pozitie;
    return os;

}