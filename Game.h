#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <vector>
#include <string>
//#include <iostream>
//#include <optional>
#include "Bird.h"
#include "Target.h"
#include "Vector2D.h"
#include "Stats.h"

class Game {
public:
    enum class Difficulty { Easy, Normal, Hard };

private:
    std::vector<Bird> birds;
    std::vector<Target> targets;

    std::vector<Bird> initialBirds;
    std::vector<Target> initialTargets;

    int score = 0;
    Difficulty difficulty = Difficulty::Normal;
    Stats stats;

public:
    Game() = default;

    void addBird(const Bird& b);
    void addTarget(const Target& t);

    [[nodiscard]] size_t getNumBirds() const { return birds.size(); }
    [[nodiscard]] size_t getNumTargets() const { return targets.size(); }

    [[nodiscard]] bool allDestroyed() const;

    void simulateShot(size_t birdIdx, size_t targetIdx);
    void demoRun();
    void resetToInitial();

    void setDifficulty(Difficulty d);
    [[nodiscard]] Difficulty getDifficulty() const { return difficulty; }

    void save(const std::string& filename) const;
    void load(const std::string& filename);

    const Stats& getStats() const { return stats; }

    [[nodiscard]] std::vector<double> computeAllDistances() const;
    [[nodiscard]] int closestTargetIndex(const Vector2D& pos) const;

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif // OOP_GAME_H
