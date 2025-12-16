#include "PhysicsEngine.h"
#include "Utils.h"
#include <cmath>

std::vector<Vector2D> PhysicsEngine::simulateTrajectory(Vector2D start, Vector2D target, double windX, double windY, double mass, double launchSpeed) {
    std::vector<Vector2D> points;
    double distTotal = start.distanta(target);
    int steps = 15;
    double stepSize = distTotal / steps;

    for (int i = 0; i <= steps; ++i) {
        double d = i * stepSize;

        double gravityDrop = 0.5 * 9.8 * Utils::square(d / launchSpeed);


        double windEffectX = (windX / mass) * (d / 10.0);
        double windEffectY = (windY / mass) * (d / 10.0);

        double x = start.getX() + d + windEffectX;
        double y = start.getY() - gravityDrop + windEffectY;

        points.push_back(Vector2D(x, y));
    }
    return points;
}

double PhysicsEngine::calculateImpactForce(double mass, double velocity, double distance) {
    double energy = Utils::kineticEnergy(mass, velocity);
    double drag = distance * 0.05;
    double finalForce = energy - drag;
    return Utils::clamp(finalForce, 0.0, 5000.0);
}


bool PhysicsEngine::checkCollision(Vector2D objPos, Vector2D targetPos, double radius) {
    Vector2D diff = objPos - targetPos;
    return diff.magnitudine() <= radius;
}