#ifndef OOP_STATS_H
#define OOP_STATS_H

//#include <string>
#include <iostream>

class Stats {
private:
    int totalShots = 0;
    int successfulShots = 0;
    double totalDamage = 0.0;
    double totalDistance = 0.0;

public:
    Stats() = default;

    void registerShot(bool hit, double damage, double distance) {
        ++totalShots;
        totalDamage += damage;
        totalDistance += distance;
        if (hit) ++successfulShots;
    }

    void reset() {
        totalShots = 0;
        successfulShots = 0;
        totalDamage = 0.0;
        totalDistance = 0.0;
    }

    [[nodiscard]] int getTotalShots() const { return totalShots; }
    [[nodiscard]] int getSuccessfulShots() const { return successfulShots; }
    [[nodiscard]] double getTotalDamage() const { return totalDamage; }
    [[nodiscard]] double getTotalDistance() const { return totalDistance; }
    [[nodiscard]] double getHitRate() const { return totalShots == 0 ? 0.0 : 100.0 * successfulShots / totalShots; }
    [[nodiscard]] double getAverageDamage() const { return successfulShots == 0 ? 0.0 : totalDamage / successfulShots; }

    friend std::ostream& operator<<(std::ostream& os, const Stats& s) {
        os << "Stats:\n";
        os << "  Shots: " << s.totalShots << "\n";
        os << "  Successful: " << s.successfulShots << "\n";
        os << "  Hit rate: " << s.getHitRate() << "%\n";
        os << "  Total damage: " << s.totalDamage << "\n";
        os << "  Total distance: " << s.totalDistance << "\n";
        os << "  Avg damage (per success): " << s.getAverageDamage() << "\n";
        return os;
    }
};

#endif // OOP_STATS_H
