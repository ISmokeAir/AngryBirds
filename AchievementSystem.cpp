#include "AchievementSystem.h"
#include <algorithm>

AchievementSystem::AchievementSystem() 
    : totalDamageDealt(0), targetsDestroyed(0), shotsFired(0) {}

void AchievementSystem::checkAchievements(double damage, bool targetDestroyed, const std::string& birdName) {
    this->shotsFired++;
    this->totalDamageDealt += static_cast<int>(damage);
    
    if (targetDestroyed) {
        this->targetsDestroyed++;
    }

    if (targetsDestroyed == 1) {
        std::string ach = "FIRST BLOOD: Prima tinta distrusa!";
        if (std::find(unlockedAchievements.begin(), unlockedAchievements.end(), ach) == unlockedAchievements.end()) {
            unlockedAchievements.push_back(ach);
            std::cout << ">>> ACHIEVEMENT UNLOCKED: " << ach << " <<<\n";
        }
    }

    if (damage > 500.0) {
        std::string ach = "SNIPER: Lovitura de peste 500 damage!";
        if (std::find(unlockedAchievements.begin(), unlockedAchievements.end(), ach) == unlockedAchievements.end()) {
            unlockedAchievements.push_back(ach);
            std::cout << ">>> ACHIEVEMENT UNLOCKED: " << ach << " <<<\n";
        }
    }

    if (shotsFired >= 5) {
        std::string ach = "VETERAN: Ai tras 5 focuri.";
        if (std::find(unlockedAchievements.begin(), unlockedAchievements.end(), ach) == unlockedAchievements.end()) {
            unlockedAchievements.push_back(ach);
            std::cout << ">>> ACHIEVEMENT UNLOCKED: " << ach << " <<<\n";
        }
    }

    if (totalDamageDealt > 2000) {
        std::string ach = "DEMOLITION MAN: 2000 Damage Total.";
        if (std::find(unlockedAchievements.begin(), unlockedAchievements.end(), ach) == unlockedAchievements.end()) {
            unlockedAchievements.push_back(ach);
            std::cout << ">>> ACHIEVEMENT UNLOCKED: " << ach << " <<<\n";
        }
    }
}

void AchievementSystem::showAchievements() const {
    std::cout << "\n=== REALIZARI DEBLOCATE ===\n";
    if (unlockedAchievements.empty()) {
        std::cout << "Nicio realizare inca.\n";
    } else {
        for (const auto& ach : unlockedAchievements) {
            std::cout << "[*] " << ach << "\n";
        }
    }
    std::cout << "Scor intern: " << getScore() << "\n";
    std::cout << "===========================\n";
}

int AchievementSystem::getScore() const {
    return (targetsDestroyed * 100) + (totalDamageDealt / 10) + (unlockedAchievements.size() * 50);
}