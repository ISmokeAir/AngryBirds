#include "StructuralAnalyzer.h"
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>

bool StructuralAnalyzer::areConnected(const Target& t1, const Target& t2) {
    if (t1.esteDistrus() || t2.esteDistrus()) return false;
    double dist = t1.getPozitie().distanta(t2.getPozitie());
    return dist < 15.0;
}

std::vector<int> StructuralAnalyzer::checkStability(const std::vector<Target>& targets) {
    int n = static_cast<int>(targets.size());
    if (n == 0) return {};

    std::vector<bool> isStable(n, false);
    std::queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (targets[i].esteDistrus()) continue;
        if (targets[i].getPozitie().getY() <= 5.0) {
            isStable[i] = true;
            q.push(i);
        }
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        if (targets[i].esteDistrus()) continue;
        for (int j = i + 1; j < n; ++j) {
            if (targets[j].esteDistrus()) continue;
            if (areConnected(targets[i], targets[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int neighbor : adj[curr]) {
            if (!isStable[neighbor]) {
                isStable[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    std::vector<int> unstableIndices;
    for (int i = 0; i < n; ++i) {
        if (!targets[i].esteDistrus() && !isStable[i]) {
            unstableIndices.push_back(i);
        }
    }
    return unstableIndices;
}

void StructuralAnalyzer::applyCollapseDamage(std::vector<Target>& targets, const std::vector<int>& unstableIndices) {
    if (unstableIndices.empty()) return;

    std::cout << "\n>>> AVERTISMENT STRUCTURAL: " << unstableIndices.size() << " blocuri instabile! <<<\n";

    for (int idx : unstableIndices) {
        Target& t = targets[idx];


        Vector2D currentPos = t.getPozitie();


        Vector2D newPos = currentPos;
        newPos.setY(currentPos.getY() - 10.0);
        newPos.setX(currentPos.getX() + (idx % 2 == 0 ? 1.0 : -1.0));

        std::cout << "COLLAPSE: Tinta " << idx << " cade virtual la " << newPos << "\n";

        double fallDamage = 50.0 + (t.getPozitie().getY() * 2.0);
        t.aplicaImpact(fallDamage);
    }
}