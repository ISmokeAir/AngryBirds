#ifndef OOP_STATS_H
#define OOP_STATS_H

#include <iostream>

class Stats {
private:
    int totalShots;
    int successfulShots;
    double totalDamage;

public:
    Stats();

    void addShot(bool hit, double damage);
    void reset();

    [[nodiscard]] int getShots() const;
    [[nodiscard]] double getDamage() const;

    friend std::ostream& operator<<(std::ostream& os, const Stats& s);
};

#endif