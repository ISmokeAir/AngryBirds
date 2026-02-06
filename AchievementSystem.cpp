#include "AchievementSystem.h"

AchievementSystem::AchievementSystem()
    : totalDamageDealt(0), targetsDestroyed(0), shotsFired(0) {}

void AchievementSystem::unlock(const std::string& ach) {
    if (std::find(unlockedAchievements.begin(), unlockedAchievements.end(), ach) == unlockedAchievements.end()) {
        unlockedAchievements.push_back(ach);
        std::cout << "\n>>> [ACHIEVEMENT UNLOCKED]: " << ach << " <<<\n\n";
    }
}

void AchievementSystem::onNotify(const std::string& event, double value) {
    if (event == "SHOT_FIRED") {
        this->shotsFired++;
        if (shotsFired >= 5) unlock("VETERAN: Ai tras 5 focuri.");
    }
    else if (event == "TARGET_DESTROYED") {
        this->targetsDestroyed++;
        if (targetsDestroyed == 1) unlock("FIRST BLOOD: Prima tinta distrusa!");
    }
    else if (event == "DAMAGE_DEALT") {
        int dmg = static_cast<int>(value);
        this->totalDamageDealt += dmg;

        if (value > 500.0) unlock("SNIPER: Lovitura de peste 500 damage!");
        if (totalDamageDealt > 2000) unlock("DEMOLITION MAN: 2000 Damage Total.");

        if (value > 1000.0) unlock("NUKE: Lovitura devastatoare (1000+ dmg)!");
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
    return (targetsDestroyed * 100) + (totalDamageDealt / 10) + (static_cast<int>(unlockedAchievements.size()) * 50);
}