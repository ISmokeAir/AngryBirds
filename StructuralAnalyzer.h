#ifndef OOP_STRUCTURALANALYZER_H
#define OOP_STRUCTURALANALYZER_H

#include <vector>
#include <set>
#include "Target.h"

class StructuralAnalyzer {
public:
    static std::vector<int> checkStability(const std::vector<Target>& targets);
    
    static bool areConnected(const Target& t1, const Target& t2);
    
    static void applyCollapseDamage(std::vector<Target>& targets, const std::vector<int>& unstableIndices);
};

#endif