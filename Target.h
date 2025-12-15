#pragma once
#include <ostream>
#include "Vector2D.h"

enum class Material {
    Wood,
    Stone,
    Ice
};

class Target {
private:
    int viata;
    Vector2D pozitie;
    Material material;

public:
    explicit Target(int viata = 100, const Vector2D& poz = Vector2D(), Material mat = Material::Wood);

    Target(const Target& other);
    Target& operator=(const Target& other);
    ~Target();

    bool incaseazaDamage(double damageBrut);

    [[nodiscard]] bool esteDistrus() const;
    [[nodiscard]] int getViata() const;
    [[nodiscard]] const Vector2D& getPozitie() const;

    friend std::ostream& operator<<(std::ostream& os, const Target& t);
};