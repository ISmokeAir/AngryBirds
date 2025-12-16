#ifndef OOP_REPLAYSYSTEM_H
#define OOP_REPLAYSYSTEM_H

#include <vector>
#include <string>

struct ReplayStep {
    int birdIdx;
    int targetIdx;
    double damage;
    bool destroyed;
    std::string timestamp;
};

class ReplaySystem {
private:
    std::vector<ReplayStep> steps;

public:
    void recordAction(int birdIdx, int targetIdx, double dmg, bool dest);
    void saveReplayToFile(const std::string& filename) const;
    void loadAndPlayReplay(const std::string& filename);
    
    std::string getCurrentTimestamp() const;
};

#endif