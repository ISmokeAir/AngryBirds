#ifndef OOP_BIRD_H
#define OOP_BIRD_H

#pragma once
#include <string>
#include <iostream>
#include "Vector2D.h"

class Bird {
protected:
    std::string nume;
    double masa;
    double vitezaLansare;
    double factorAerodinamic;
    Vector2D pozitie;

    static int numarPasari;

public:
    Bird(std::string nume, double masa, double viteza, double factorAero, const Vector2D& poz);

    virtual ~Bird();

    [[nodiscard]] virtual double calculeazaMomentum(double distantaZbor, double vant) const;

    [[nodiscard]] virtual Bird* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Bird& b);

    const std::string& getNume() const;
    const Vector2D& getPozitie() const;
    double getMasa() const;
    double getViteza() const;

    static int getNumarTotalPasari();

protected:
    virtual void afiseaza(std::ostream& os) const;
};

#endif