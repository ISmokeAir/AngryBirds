#ifndef OOP_GAME_H
#define OOP_GAME_H

#pragma once
#include <vector>
#include <string>
#include "MyBirds.h"
#include "Target.h"
#include "Stats.h"
#include "AchievementSystem.h"
#include "Economy.h"
#include "PhysicsEngine.h"
#include "TrajectoryOptimizer.h"
#include "StructuralAnalyzer.h"
#include "WeatherEngine.h"
#include "ReplaySystem.h"
#include "Observer.h"
#include "GameContainer.h"

enum class Difficulty { Easy, Normal, Hard };

class Game : public ISubject {
private:
    std::vector<Bird*> birds;
    std::vector<Target> targets;
    Stats stats;
    AchievementSystem achievements;
    Economy economy;
    WeatherEngine weather;
    ReplaySystem replay;

    Difficulty dificultate;

    GameContainer<std::string> istoricActiuni;

    std::vector<IObserver*> observers;

    void updateVant();
    double calculeazaScorStrategic(int birdIdx, int targetIdx) const;
    void logActiune(const std::string& actiune);
    void salveazaLogPeDisk() const;
    void curataMemorie();

public:
    Game();
    ~Game();
    Game(const Game& other);
    Game& operator=(Game other);
    friend void swap(Game& first, Game& second) noexcept;

    void addObserver(IObserver* observer) override;
    void removeObserver(IObserver* observer) override;
    void notifyObservers(const std::string& event, double value) override;

    void addBird(Bird* b);
    void addTarget(const Target& t);

    void loadMap(const std::vector<Target>& mapTargets);
    void setDifficulty(Difficulty d);
    void lanseazaPasare(int birdIdx, int targetIdx);
    void predicteazaTraiectorie(int birdIdx, int targetIdx) const;
    void activeazaSuperComputer();
    void ruleazaDemoAvansat();
    void afiseazaAchievements() const;
    void acceseazaMagazin();
    void verificaStabilitateStructura();

    void ruleazaReplay();

    bool verificaVictorie() const;
    void afiseazaStare() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif