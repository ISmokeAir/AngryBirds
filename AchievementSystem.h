#ifndef OOP_ACHIEVEMENTSYSTEM_H
#define OOP_ACHIEVEMENTSYSTEM_H

#include <vector>
#include <string>
#include <iostream>

class AchievementSystem {
private:
    std::vector<std::string> unlockedAchievements;
    int totalDamageDealt;
    int targetsDestroyed;
    int shotsFired;

public:
    AchievementSystem();

    void checkAchievements(double damage, bool targetDestroyed, const std::string& birdName);

    void showAchievements() const;
    int getScore() const;
};

#endif