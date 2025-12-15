#include "Stats.h"

Stats::Stats() : totalLansari(0), tinteLovite(0), damageTotal(0.0) {
}

void Stats::inregistreazaLansare(bool lovit, double damage) {
    this->totalLansari++;
    this->damageTotal += damage;
    if (lovit) {
        this->tinteLovite++;
    }
}

int Stats::getLansari() const { return this->totalLansari; }
double Stats::getDamageTotal() const { return this->damageTotal; }

double Stats::getAcuratete() const {
    if (this->totalLansari == 0) return 0.0;
    return (static_cast<double>(this->tinteLovite) / static_cast<double>(this->totalLansari)) * 100.0;
}

std::ostream& operator<<(std::ostream& os, const Stats& s) {
    os << "Statistici Sesiune: " << s.tinteLovite << "/" << s.totalLansari
       << " lovituri reusite. Damage Total: " << s.damageTotal;
    return os;
}