#include "ReplaySystem.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>

void ReplaySystem::recordAction(int birdIdx, int targetIdx, double dmg, bool dest) {
    ReplayStep step;
    step.birdIdx = birdIdx;
    step.targetIdx = targetIdx;
    step.damage = dmg;
    step.destroyed = dest;
    step.timestamp = getCurrentTimestamp();
    steps.push_back(step);
}

void ReplaySystem::saveReplayToFile(const std::string& filename) const {
    if (steps.empty()) {
        return;
    }

    std::ofstream out(filename);
    if (!out.is_open()) return;

    out << "REPLAY_VERSION_1.0\n";
    for (const auto& step : steps) {
        out << step.timestamp << "|"
            << step.birdIdx << "|"
            << step.targetIdx << "|"
            << step.damage << "|"
            << (step.destroyed ? "1" : "0") << "\n";
    }
    out.close();
    std::cout << "Replay salvat in " << filename << "\n";
}

void ReplaySystem::loadAndPlayReplay(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Nu exista fisier replay valid.\n";
        return;
    }

    std::string line;
    std::getline(in, line);
    if (line != "REPLAY_VERSION_1.0") {
        std::cout << "Format replay invalid sau fisier corupt.\n";
        return;
    }

    std::cout << "\n>>> RULARE REPLAY >>>\n";
    int stepCount = 1;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while(std::getline(ss, segment, '|')) {
            parts.push_back(segment);
        }

        if (parts.size() >= 5) {
            std::cout << "Pas " << stepCount++ << " [" << parts[0] << "]: ";
            std::cout << "Pasare " << parts[1] << " a lovit Tinta " << parts[2];
            std::cout << " cu " << parts[3] << " damage.";
            if (parts[4] == "1") std::cout << " (DISTRUSA)";
            std::cout << "\n";
        }
    }
    std::cout << "<<< FINAL REPLAY <<<\n";
}

std::string ReplaySystem::getCurrentTimestamp() const {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
    return std::string(buf);
}