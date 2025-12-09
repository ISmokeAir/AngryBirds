#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <optional>
#include "Bird.h"
#include "Target.h"

enum class Dificultate { Usor, Normal, Greu };

class Game {
private:
    std::vector<Bird> pasari;
    std::vector<Target> tinte;

    int scor = 0;
    Dificultate dificultate = Dificultate::Normal;

public:
    Game() = default;


    void adaugaBird(const Bird& b) { pasari.push_back(b); }
    void adaugaTarget(const Target& t) { tinte.push_back(t); }


    [[nodiscard]] size_t getNumarPasari() const { return pasari.size(); }
    [[nodiscard]] size_t getNumarTinte() const { return tinte.size(); }
    [[nodiscard]] bool toateDistruse() const;


    void simuleazaLovitura(size_t idxBird, size_t idxTarget);

    void actualizeazaScor(int damage, double distanta);

    [[nodiscard]] int getScor() const { return scor; }


    void seteazaDificultate(Dificultate d);
    [[nodiscard]] Dificultate getDificultate() const { return dificultate; }


    [[nodiscard]] bool verificaIntegritate() const;


    [[nodiscard]] std::vector<double> calculeazaToateDistantele() const;


    [[nodiscard]] int indiceTintaApropiata(const Vector2D& poz) const;


    void simulareAutomata();


    void reset();


    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif // OOP_GAME_H
