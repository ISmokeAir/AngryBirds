#include "TrajectoryOptimizer.h"
#include "Utils.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

SimulationResult TrajectoryOptimizer::findOptimalShot(const Bird* bird, const Target& target, double wind) {
    std::vector<SimulationResult> simulationData;
    
    double startX = bird->getPozitie().getX();
    double startY = bird->getPozitie().getY();
    double targetX = target.getPozitie().getX();
    double targetY = target.getPozitie().getY();
    double birdMass = bird->getMasa();
    double baseSpeed = bird->getViteza();

    std::cout << "Initializare procesare Monte Carlo...\n";
    std::cout << "Parametri: Vant=" << wind << " Masa=" << birdMass << " Distanta=" << std::abs(targetX - startX) << "\n";

    SimulationResult bestResult;
    bestResult.score = -1.0;
    bestResult.hit = false;

    for (int angleDeg = 10; angleDeg <= 85; angleDeg += 2) {
        for (int power = 30; power <= 100; power += 5) {
            
            double rads = angleDeg * 3.14159265359 / 180.0;
            double actualSpeed = baseSpeed * (power / 100.0);
            
            double velX = actualSpeed * std::cos(rads);
            double velY = actualSpeed * std::sin(rads);
            
            double currX = startX;
            double currY = startY;
            
            bool collision = false;
            double minDistanceToTarget = 10000.0;
            
            double timeStep = 0.1;
            int maxSteps = 500;
            
            for (int step = 0; step < maxSteps; ++step) {
                double dragForceX = -0.05 * velX;
                double dragForceY = -0.05 * velY;
                
                double windForceX = (wind * 0.5) / birdMass;
                
                double accX = (dragForceX + windForceX) / birdMass;
                double accY = (-9.8 * birdMass + dragForceY) / birdMass;
                
                velX += accX * timeStep;
                velY += accY * timeStep;
                
                currX += velX * timeStep;
                currY += velY * timeStep;
                
                if (currY < 0) {
                    currY = 0;
                    break; 
                }

                double dist = std::sqrt(std::pow(currX - targetX, 2) + std::pow(currY - targetY, 2));
                if (dist < minDistanceToTarget) {
                    minDistanceToTarget = dist;
                }
                
                if (dist < 2.0) {
                    collision = true;
                    break;
                }
            }

            double impactScore = 0.0;
            
            if (collision) {
                double impactVelocity = std::sqrt(velX*velX + velY*velY);
                double kineticEnergy = 0.5 * birdMass * impactVelocity * impactVelocity;
                
                impactScore = kineticEnergy;
                
                if (angleDeg > 45) impactScore *= 1.2;
                
                if (power < 100) impactScore *= 1.1;
            } else {
                if (minDistanceToTarget < 5.0) {
                    impactScore = 10.0 / minDistanceToTarget;
                }
            }

            SimulationResult res;
            res.angle = (double)angleDeg;
            res.power = (double)power;
            res.score = impactScore;
            res.hit = collision;
            res.impactPoint = Vector2D(currX, currY);
            
            simulationData.push_back(res);

            if (res.score > bestResult.score) {
                bestResult = res;
            }
        }
    }

    std::cout << "Simulari completate: " << simulationData.size() << "\n";
    printAnalysisReport(simulationData);
    
    return bestResult;
}

void TrajectoryOptimizer::printAnalysisReport(const std::vector<SimulationResult>& results) {
    if (results.empty()) return;

    std::cout << "\n=== RAPORT ANALIZA TRAIECTORIE ===\n";
    std::cout << "Unghi | Putere | Rezultat | Scor\n";
    std::cout << "--------------------------------\n";

    int countHigh = 0;
    int countMed = 0;
    int countLow = 0;
    int countMiss = 0;

    for (size_t i = 0; i < results.size(); i += 25) {
        const auto& r = results[i];
        
        std::string status = "RATARE";
        if (r.hit) {
            status = "LOVITURA";
            if (r.score > 500) status += " CRITICA";
        }

        if (r.score > 500) countHigh++;
        else if (r.score > 100) countMed++;
        else if (r.score > 0) countLow++;
        else countMiss++;

        if (r.hit || r.score > 50.0) { 
             std::cout << std::fixed << std::setprecision(1) 
                       << r.angle << "deg | " 
                       << r.power << "%   | " 
                       << status << " | " 
                       << r.score << "\n";
        }
    }

    std::cout << "--------------------------------\n";
    std::cout << "STATISTICA POSIBILITATI:\n";
    std::cout << "Solutii Critice: " << countHigh << "\n";
    std::cout << "Solutii Bune:    " << countMed << "\n";
    std::cout << "Solutii Slabe:   " << countLow << "\n";
    std::cout << "Esuate:          " << countMiss << "\n";
    std::cout << "================================\n";
}