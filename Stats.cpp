#include "Stats.h"

Stats::Stats() : totalShots(0), successfulShots(0), totalDamage(0.0) {}

void Stats::addShot(bool hit, double damage) {
    totalShots++;
    totalDamage += damage;
    if (hit) successfulShots++;
}

void Stats::reset() {
    totalShots = 0;
    successfulShots = 0;
    totalDamage = 0.0;
}

int Stats::getShots() const { return totalShots; }
double Stats::getDamage() const { return totalDamage; }

std::ostream& operator<<(std::ostream& os, const Stats& s) {
    os << "Statistici: " << s.successfulShots << "/" << s.totalShots
       << " lovituri, Damage total: " << s.totalDamage;
    return os;
}