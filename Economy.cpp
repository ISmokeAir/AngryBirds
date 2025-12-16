#include "Economy.h"
#include <iostream>
#include <iomanip>

Economy::Economy() : coins(0) {
    shopItems[1] = {"Upgrade Putere (x1.5)", 100, false};
    shopItems[2] = {"Upgrade Acuratete", 200, false};
    shopItems[3] = {"Extra Viata Tinte", 50, false};
    shopItems[4] = {"Golden Slingshot", 500, false};
}

void Economy::addCoins(int amount) {
    if (amount > 0) {
        coins += amount;
        transactionLog.push_back("Credit: +" + std::to_string(amount));
    }
}

bool Economy::spendCoins(int amount) {
    if (coins >= amount) {
        coins -= amount;
        transactionLog.push_back("Debit: -" + std::to_string(amount));
        return true;
    }
    return false;
}

void Economy::buyItem(int itemId) {
    auto it = shopItems.find(itemId);
    if (it != shopItems.end()) {
        if (it->second.purchased) {
            std::cout << "Deja detinut: " << it->second.name << "\n";
            return;
        }

        if (spendCoins(it->second.cost)) {
            it->second.purchased = true;
            std::cout << "Cumparat cu succes: " << it->second.name << "\n";
        } else {
            std::cout << "Fonduri insuficiente! Ai nevoie de " << it->second.cost << "\n";
        }
    } else {
        std::cout << "Item invalid.\n";
    }
}

void Economy::showShop() const {
    std::cout << "\n--- MAGAZIN ---\n";
    std::cout << "Fonduri: " << coins << " Gold\n";
    for (const auto& pair : shopItems) {
        std::cout << "[" << pair.first << "] " << pair.second.name 
                  << " - Pret: " << pair.second.cost 
                  << (pair.second.purchased ? " [CUMPARAT]" : "") << "\n";
    }
    std::cout << "---------------\n";
}

void Economy::showBalance() const {
    std::cout << "Sold curent: " << coins << "\n";
}

int Economy::getBalance() const {
    return coins;
}