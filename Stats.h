#ifndef OOP_STATS_H
#define OOP_STATS_H

#pragma once
#include <ostream>

class Stats {
private:
    int totalLansari;
    int tinteLovite;
    double damageTotal;

public:
    Stats();

    void inregistreazaLansare(bool lovit, double damage);

    int getLansari() const;
    double getDamageTotal() const;
    double getAcuratete() const;

    friend std::ostream& operator<<(std::ostream& os, const Stats& s);
};

#endif