#include "MapGenerator.h"
#include "Utils.h"
#include <cmath>
#include <random>

std::vector<Target> MapGenerator::generateClassicLevel() {
    std::vector<Target> t;
    t.push_back(Target(50.0, Vector2D(30, 0), Material::Ice));
    t.push_back(Target(100.0, Vector2D(50, 0), Material::Wood));
    t.push_back(Target(200.0, Vector2D(70, 0), Material::Stone));
    return t;
}

std::vector<Target> MapGenerator::generateWallLevel() {
    std::vector<Target> t;
    double startX = 40.0;
    
    for (int i = 0; i < 5; ++i) {
        Material m = Material::Wood;
        if (i % 2 == 0) m = Material::Stone;
        
        t.push_back(Target(150.0, Vector2D(startX + (i * 5), 0), m));
    }
    
    for (int i = 0; i < 3; ++i) {
        t.push_back(Target(80.0, Vector2D(startX + 5 + (i * 5), 10), Material::Ice));
    }

    return t;
}

std::vector<Target> MapGenerator::generatePyramidLevel() {
    std::vector<Target> t;
    double startX = 50.0;
    double startY = 0.0;
    int rows = 4;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= r; ++c) {
            double x = startX + (c * 8.0) - (r * 4.0);
            double y = startY + (r * 5.0);
            
            Material m = Material::Wood;
            if (r == rows - 1) m = Material::Stone;
            if (r == 0) m = Material::Ice;

            t.push_back(Target(100.0 + (r * 20.0), Vector2D(x, y), m));
        }
    }
    return t;
}

std::vector<Target> MapGenerator::generateRandomChaos() {
    std::vector<Target> t;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> posX(20.0, 90.0);
    std::uniform_real_distribution<> hp(20.0, 300.0);
    std::uniform_int_distribution<> mat(0, 2);

    for (int i = 0; i < 6; ++i) {
        double x = posX(gen);
        double h = hp(gen);
        Material m = Material::Wood;
        int matType = mat(gen);
        
        if (matType == 0) m = Material::Ice;
        else if (matType == 2) m = Material::Stone;

        t.push_back(Target(h, Vector2D(x, 0), m));
    }
    return t;
}