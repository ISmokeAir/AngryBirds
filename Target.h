#ifndef OOP_TARGET_H
#define OOP_TARGET_H

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
    double integritateStructura;
    double integritateMaxima;
    Vector2D pozitie;
    Material material;
    double factorArmura;

public:
    explicit Target(double integritate = 100.0, const Vector2D& poz = Vector2D(), Material mat = Material::Wood);
    Target(const Target& other);
    Target& operator=(const Target& other);
    ~Target();

    bool aplicaImpact(double fortaImpact);
    void scaleazaDificultate(double multiplicatorHp, double multiplicatorArmura);

    bool esteDistrus() const;
    double getIntegritate() const;
    double getIntegritateMaxima() const;
    const Vector2D& getPozitie() const;
    Material getMaterial() const;
    double getArmura() const;

    friend std::ostream& operator<<(std::ostream& os, const Target& t);
};

#endif