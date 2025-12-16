#ifndef OOP_PHYSICSENGINE_H
#define OOP_PHYSICSENGINE_H

#include "Vector2D.h"
#include <vector>

class PhysicsEngine {
public:
    static std::vector<Vector2D> simulateTrajectory(Vector2D start, Vector2D target, double wind, double mass, double launchSpeed);
    static double calculateImpactForce(double mass, double velocity, double distance);
    static bool checkCollision(Vector2D objPos, Vector2D targetPos, double radius);
};

#endif