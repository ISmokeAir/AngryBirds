#ifndef OOP_MYBIRDS_H
#define OOP_MYBIRDS_H

#include "Bird.h"

class RedBird : public Bird {
public:
    explicit RedBird(const Vector2D& poz = Vector2D());
    double calculeazaMomentum(double distantaZbor, double vant) const override;
    Bird* clone() const override;
protected:
    void afiseaza(std::ostream& os) const override;
};

class ChuckBird : public Bird {
public:
    explicit ChuckBird(const Vector2D& poz = Vector2D());
    double calculeazaMomentum(double distantaZbor, double vant) const override;
    Bird* clone() const override;
protected:
    void afiseaza(std::ostream& os) const override;
};

class BombBird : public Bird {
public:
    explicit BombBird(const Vector2D& poz = Vector2D());
    double calculeazaMomentum(double distantaZbor, double vant) const override;
    Bird* clone() const override;
    void activeazaExplozie() const;
protected:
    void afiseaza(std::ostream& os) const override;
};

// --- CLASA NOUA PENTRU COMMIT SEPARAT ---
class MatildaBird : public Bird {
public:
    explicit MatildaBird(const Vector2D& poz = Vector2D());

    double calculeazaMomentum(double distantaZbor, double vant) const override;
    Bird* clone() const override;

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif