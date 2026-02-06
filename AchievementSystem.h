#ifndef OOP_ACHIEVEMENTSYSTEM_H
#define OOP_ACHIEVEMENTSYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Observer.h"

class AchievementSystem : public IObserver {
private:
    std::vector<std::string> unlockedAchievements;
    int totalDamageDealt;
    int targetsDestroyed;
    int shotsFired;

    void unlock(const std::string& achName);

public:
    AchievementSystem();

    void onNotify(const std::string& event, double value) override;

    void showAchievements() const;
    int getScore() const;
};

#endif