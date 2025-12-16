#ifndef OOP_ECONOMY_H
#define OOP_ECONOMY_H

#include <string>
#include <map>
#include <vector>

struct ShopItem {
    std::string name;
    int cost;
    bool purchased;
};

class Economy {
private:
    int coins;
    std::map<int, ShopItem> shopItems;
    std::vector<std::string> transactionLog;

public:
    Economy();
    
    void addCoins(int amount);
    bool spendCoins(int amount);
    void buyItem(int itemId);
    
    void showShop() const;
    void showBalance() const;
    int getBalance() const;
};

#endif