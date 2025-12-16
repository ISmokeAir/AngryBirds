#ifndef OOP_TRAJECTORYOPTIMIZER_H
#define OOP_TRAJECTORYOPTIMIZER_H

#include "Vector2D.h"
#include "Bird.h"
#include "Target.h"
#include <vector>
#include <string>

struct SimulationResult {
    double angle;
    double power;
    double score;
    Vector2D impactPoint;
    bool hit;
};

class TrajectoryOptimizer {
public:
    static SimulationResult findOptimalShot(const Bird* bird, const Target& target, double wind);
    
    static void printAnalysisReport(const std::vector<SimulationResult>& results);
};

#endif