#include "Game.h"
#include "Exceptions.h"
#include "Utils.h"
#include "TextUI.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

Game::Game() : vantCurrent(0.0), dificultate(Difficulty::Normal) {
    this->updateVant();
    this->logActiune("Joc initializat.");
}

Game::~Game() {
    this->logActiune("Joc inchis.");
    try {
        this->salveazaLogPeDisk();
    } catch (const std::exception& e) {
        std::cerr << "Eroare salvare log: " << e.what() << "\n";
    }
    curataMemorie();
}

void Game::curataMemorie() {
    for (auto* b : birds) delete b;
    birds.clear();
}

Game::Game(const Game& other)
    : targets(other.targets), stats(other.stats), achievements(other.achievements), economy(other.economy),
      vantCurrent(other.vantCurrent), dificultate(other.dificultate),
      istoricActiuni(other.istoricActiuni) {
    for (const auto* b : other.birds) {
        birds.push_back(b->clone());
    }
}

void swap(Game& first, Game& second) noexcept {
    using std::swap;
    swap(first.birds, second.birds);
    swap(first.targets, second.targets);
    swap(first.stats, second.stats);
    swap(first.achievements, second.achievements);
    swap(first.economy, second.economy);
    swap(first.vantCurrent, second.vantCurrent);
    swap(first.dificultate, second.dificultate);
    swap(first.istoricActiuni, second.istoricActiuni);
}

Game& Game::operator=(Game other) {
    swap(*this, other);
    return *this;
}

void Game::logActiune(const std::string& actiune) {
    this->istoricActiuni.push_back(actiune);
}

void Game::salveazaLogPeDisk() const {
    std::ofstream fisier("gamelog.txt");
    if (!fisier.is_open()) throw FileException("gamelog.txt");
    fisier << "=== LOG JOC ===\n";
    for (const auto& linie : istoricActiuni) fisier << linie << "\n";
    fisier << "Scor Final: " << achievements.getScore() << "\n";
    fisier << "Bani ramasi: " << economy.getBalance() << "\n";
    fisier.close();
}

void Game::updateVant() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    this->vantCurrent = dis(gen);
    std::stringstream ss;
    ss << "Vant: " << std::fixed << std::setprecision(2) << this->vantCurrent;
    this->logActiune(ss.str());
}

void Game::addBird(Bird* b) {
    if (!b) throw LogicException("Pointer nul addBird");
    this->birds.push_back(b);
    this->logActiune("Adaugat bird: " + b->getNume());
}

void Game::addTarget(const Target& t) {
    this->targets.push_back(t);
    this->logActiune("Adaugat tinta");
}

void Game::loadMap(const std::vector<Target>& mapTargets) {
    this->targets = mapTargets;
    this->logActiune("Harta noua incarcata");
    TextUI::drawHeader("HARTA NOUA GENERATA");
}

void Game::setDifficulty(Difficulty d) {
    this->dificultate = d;
    double hp=1.0, arm=1.0;
    if(d==Difficulty::Easy) { hp=0.7; arm=0.8; }
    if(d==Difficulty::Hard) { hp=1.5; arm=1.2; }

    for(auto& t : targets) t.scaleazaDificultate(hp, arm);
    this->logActiune("Dificultate setata");
}

void Game::predicteazaTraiectorie(int birdIdx, int targetIdx) const {
    if (birdIdx < 0 || birdIdx >= (int)birds.size()) throw LogicException("Idx Bird Invalid");
    if (targetIdx < 0 || targetIdx >= (int)targets.size()) throw LogicException("Idx Tinta Invalid");

    const Bird* b = birds[birdIdx];
    const Target& t = targets[targetIdx];

    TextUI::drawHeader("PREDICTIE TRAIECTORIE");
    std::vector<Vector2D> points = PhysicsEngine::simulateTrajectory(b->getPozitie(), t.getPozitie(), vantCurrent, b->getMasa(), b->getViteza());
    for(size_t i = 0; i < points.size(); ++i) std::cout << "Pct " << i << ": " << points[i] << "\n";
}

void Game::activeazaSuperComputer() {
    TextUI::drawHeader("SUPER COMPUTER: OPTIMIZARE TRAIECTORIE");

    int bestBird = -1;
    SimulationResult bestGlobalShot;
    bestGlobalShot.score = -1.0;

    for (int i = 0; i < (int)birds.size(); ++i) {
        for (const auto& t : targets) {
            if (t.esteDistrus()) continue;

            std::cout << "Analizez Pasare [" << i << "] vs Tinta...\n";
            SimulationResult res = TrajectoryOptimizer::findOptimalShot(birds[i], t, vantCurrent);

            if (res.score > bestGlobalShot.score) {
                bestGlobalShot = res;
                bestBird = i;
            }
        }
    }

    if (bestBird != -1) {
        std::cout << "\n>>> SOLUTIE OPTIMA GASITA <<<\n";
        std::cout << "Pasare Recomandata: " << birds[bestBird]->getNume() << "\n";
        std::cout << "Unghi Lansare: " << bestGlobalShot.angle << " grade\n";
        std::cout << "Putere Lansare: " << bestGlobalShot.power << "%\n";
        std::cout << "Scor Estimat: " << bestGlobalShot.score << "\n";
    } else {
        std::cout << "Nu s-a gasit nicio solutie viabila.\n";
    }
}

void Game::lanseazaPasare(int birdIdx, int targetIdx) {
    if (birdIdx < 0 || birdIdx >= (int)birds.size()) throw LogicException("Idx Bird Invalid");
    if (targetIdx < 0 || targetIdx >= (int)targets.size()) throw LogicException("Idx Tinta Invalid");

    if (targets[targetIdx].esteDistrus()) {
        std::cout << "Tinta distrusa deja.\n";
        return;
    }

    Bird* b = birds[birdIdx];
    Target& t = targets[targetIdx];

    this->logActiune("Lansare: " + b->getNume());
    TextUI::drawHeader("LANSARE");
    std::cout << "Pasare: " << *b << "\n";

    if (auto* bomb = dynamic_cast<BombBird*>(b)) {
        bomb->activeazaExplozie();
    }

    double dist = b->getPozitie().distanta(t.getPozitie());
    double mom = PhysicsEngine::calculateImpactForce(b->getMasa(), b->getViteza(), dist);

    std::cout << "Forta Impact: " << mom << "\n";
    bool hit = t.aplicaImpact(mom);
    achievements.checkAchievements(mom, t.esteDistrus(), b->getNume());

    if (hit) {
        int reward = 50;
        if (t.esteDistrus()) reward = 150;
        economy.addCoins(reward);
        std::cout << "Ai castigat " << reward << " Gold!\n";
    }

    stats.inregistreazaLansare(hit, mom);
    updateVant();

    if (hit) {
        std::cout << "LOVITURA! HP Ramas: " << t.getIntegritate() << "\n";
        TextUI::drawProgressBar((t.getIntegritate() / t.getIntegritateMaxima()) * 100.0);
    } else {
        std::cout << "RATARE!\n";
    }
}

void Game::afiseazaAchievements() const {
    achievements.showAchievements();
}

void Game::acceseazaMagazin() {
    bool inShop = true;
    while (inShop) {
        economy.showShop();
        std::cout << "0. Iesire\nID Item: ";
        int opt;
        if (!(std::cin >> opt)) {
            std::cin.clear();
            std::string dummy;
            std::getline(std::cin, dummy);
            continue;
        }
        if (opt == 0) inShop = false;
        else economy.buyItem(opt);
    }
}

double Game::calculeazaScorStrategic(int birdIdx, int targetIdx) const {
    const Bird* b = birds[birdIdx];
    const Target& t = targets[targetIdx];
    if (t.esteDistrus()) return -1.0;
    double dist = b->getPozitie().distanta(t.getPozitie());
    return PhysicsEngine::calculateImpactForce(b->getMasa(), b->getViteza(), dist);
}

void Game::ruleazaDemoAvansat() {
    TextUI::drawHeader("DEMO AI HIBRID: HEURISTIC + MONTE CARLO");
    int steps = 0;
    while(!verificaVictorie() && steps < 8) {
        steps++;
        std::cout << "\n=== RUNDA AI " << steps << " ===\n";

        int bestBird = -1;
        int bestTarget = -1;
        double maxHeuristicScore = -1.0;

        std::cout << "Faza 1: Scanare Heuristica Rapida...\n";
        for(int i=0; i<(int)birds.size(); ++i) {
            for(int j=0; j<(int)targets.size(); ++j) {
                if(targets[j].esteDistrus()) continue;

                double s = calculeazaScorStrategic(i, j);
                if (s > maxHeuristicScore) {
                    maxHeuristicScore = s;
                    bestBird = i;
                    bestTarget = j;
                }
            }
        }

        if(bestBird != -1) {
            std::cout << "Candidat Identificat: Pasare " << bestBird << " -> Tinta " << bestTarget << "\n";
            std::cout << "Scor Heuristic: " << maxHeuristicScore << "\n";

            std::cout << "Faza 2: Validare Monte Carlo (Super Computer)...\n";

            SimulationResult simRes = TrajectoryOptimizer::findOptimalShot(birds[bestBird], targets[bestTarget], vantCurrent);

            if (simRes.hit && simRes.score > 0) {
                std::cout << "[AI] Solutie confirmata! Unghi: " << simRes.angle << ", Putere: " << simRes.power << "\n";

                this->logActiune("AI Lansare Optimizata");

                Target& t = targets[bestTarget];
                Bird* b = birds[bestBird];

                std::cout << ">>> AI EXECUTA LANSAREA >>>\n";
                if (auto* bomb = dynamic_cast<BombBird*>(b)) bomb->activeazaExplozie();

                bool hit = t.aplicaImpact(simRes.score);
                achievements.checkAchievements(simRes.score, t.esteDistrus(), "AI_BOT");

                if (hit) {
                    economy.addCoins(25);
                    std::cout << "AI LOVITURA! HP Ramas: " << t.getIntegritate() << "\n";
                } else {
                    std::cout << "AI RATARE (Eroare simulare)!\n";
                }

                updateVant();
            } else {
                std::cout << "[AI] Validare esuata. Se incearca lansare standard...\n";
                lanseazaPasare(bestBird, bestTarget);
            }

        } else {
            std::cout << "[AI] Nu mai sunt tinte valide.\n";
            break;
        }
    }
    std::cout << "=== DEMO END ===\n";
}

bool Game::verificaVictorie() const {
    for(const auto& t : targets) if(!t.esteDistrus()) return false;
    return true;
}

void Game::afiseazaStare() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    TextUI::drawHeader("STARE JOC");
    os << "Dificultate: " << (int)g.dificultate << "\n";
    os << "Bani: " << g.economy.getBalance() << "\n";
    os << "Pasari:\n";
    for(size_t i=0; i<g.birds.size(); ++i) os << i << ": " << *g.birds[i] << "\n";
    os << "Tinte:\n";
    for(size_t i=0; i<g.targets.size(); ++i)
        os << i << ": " << g.targets[i] << (g.targets[i].esteDistrus() ? " [X]" : "") << "\n";
    os << g.stats << "\n";
    return os;
}