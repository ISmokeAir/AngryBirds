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

Game::Game() : dificultate(Difficulty::Normal) {
    this->weather.updateWeather();
    Utils::logDebug("Constructor Game apelat");
    this->logActiune("Joc initializat.");
}

Game::~Game() {
    this->logActiune("Joc inchis.");
    try {
        this->salveazaLogPeDisk();
        this->replay.saveReplayToFile("last_match.rpl");
    } catch (const std::exception& e) {
        std::cerr << "Eroare salvare: " << e.what() << "\n";
    }
    curataMemorie();
}

void Game::curataMemorie() {
    for (auto* b : birds) delete b;
    birds.clear();
}

Game::Game(const Game& other)
    : targets(other.targets), stats(other.stats), achievements(other.achievements),
      economy(other.economy), weather(other.weather), replay(other.replay),
      dificultate(other.dificultate), istoricActiuni(other.istoricActiuni) {
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
    swap(first.weather, second.weather);
    swap(first.replay, second.replay);
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
    fisier.close();
}

void Game::updateVant() {
    weather.updateWeather();
    this->logActiune(weather.getWeatherReport());
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

    TextUI::drawHeader("PREDICTIE METEO-DEPENDENTA");
    std::cout << weather.getWeatherReport() << "\n";


    std::vector<Vector2D> points = PhysicsEngine::simulateTrajectory(
        b->getPozitie(), t.getPozitie(),
        weather.getWindX(), weather.getWindY(),
        b->getMasa(), b->getViteza()
    );

    bool potentialHit = false;
    for(size_t i = 0; i < points.size(); ++i) {
        std::cout << "Pct " << i << ": " << points[i] << "\n";


        if (PhysicsEngine::checkCollision(points[i], t.getPozitie(), 2.0)) {
            potentialHit = true;
        }
    }

    if (potentialHit) {
        std::cout << ">>> PREDICTIE: LOVITURA PROBABILA! <<<\n";
    }
}

void Game::activeazaSuperComputer() {
    TextUI::drawHeader("SUPER COMPUTER & WEATHER ANALYZER");
    int bestBird = -1;
    SimulationResult bestGlobalShot;
    bestGlobalShot.score = -1.0;

    for (int i = 0; i < (int)birds.size(); ++i) {
        for (const auto& t : targets) {
            if (t.esteDistrus()) continue;
            SimulationResult res = TrajectoryOptimizer::findOptimalShot(birds[i], t, weather.getWindX());
            if (res.score > bestGlobalShot.score) {
                bestGlobalShot = res;
                bestBird = i;
            }
        }
    }

    if (bestBird != -1) {
        std::cout << "\n>>> SOLUTIE OPTIMA PE TIMP DE " << weather.getWeatherReport() << " <<<\n";
        std::cout << "Bird: " << birds[bestBird]->getNume() << " | Angle: " << bestGlobalShot.angle << "\n";
    }
}

void Game::verificaStabilitateStructura() {
    std::vector<int> unstable = StructuralAnalyzer::checkStability(targets);
    if (!unstable.empty()) {
        StructuralAnalyzer::applyCollapseDamage(targets, unstable);
        this->logActiune("Colaps structural");
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


    if (weather.isStormy()) {
        std::cout << "!!! ATENTIE: FURTUNA IN DESFASURARE - PRECIZIE SCAZUTA !!!\n";
    }


    std::cout << "Target Info: Mat=" << (int)t.getMaterial()
              << " Arm=" << t.getArmura() << "\n";

    this->logActiune("Lansare: " + b->getNume());
    TextUI::drawHeader("LANSARE");
    std::cout << weather.getWeatherReport() << "\n";

    if (auto* bomb = dynamic_cast<BombBird*>(b)) bomb->activeazaExplozie();

    double dist = b->getPozitie().distanta(t.getPozitie());
    double mom = PhysicsEngine::calculateImpactForce(b->getMasa(), b->getViteza(), dist);

    mom /= weather.getFrictionMultiplier();

    std::cout << "Forta Impact (cu Meteo): " << mom << "\n";
    bool hit = t.aplicaImpact(mom);
    achievements.checkAchievements(mom, t.esteDistrus(), b->getNume());
    replay.recordAction(birdIdx, targetIdx, mom, t.esteDistrus());

    if (hit) {
        int reward = 50;
        if (t.esteDistrus()) reward = 150;
        economy.addCoins(reward);
        std::cout << "Ai castigat " << reward << " Gold!\n";
        TextUI::drawProgressBar((t.getIntegritate() / t.getIntegritateMaxima()) * 100.0);
    } else {
        std::cout << "RATARE!\n";
    }

    stats.inregistreazaLansare(hit, mom);
    updateVant();
    verificaStabilitateStructura();
}

void Game::ruleazaReplay() {
    replay.loadAndPlayReplay("last_match.rpl");
}

void Game::afiseazaAchievements() const { achievements.showAchievements(); }

void Game::acceseazaMagazin() {
    bool inShop = true;
    while (inShop) {
        economy.showShop();
        std::cout << "0. Iesire\nID: ";
        int opt;
        if (!(std::cin >> opt)) {
            std::cin.clear(); std::string d; std::getline(std::cin, d); continue;
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
    return PhysicsEngine::calculateImpactForce(b->getMasa(), b->getViteza(), dist) / weather.getFrictionMultiplier();
}

void Game::ruleazaDemoAvansat() {
    TextUI::drawHeader("DEMO AI");
    int steps = 0;
    while(!verificaVictorie() && steps < 8) {
        steps++;
        int bestB = -1, bestT = -1;
        double maxS = -1.0;

        for(int i=0; i<(int)birds.size(); ++i) {
            for(int j=0; j<(int)targets.size(); ++j) {
                if(targets[j].esteDistrus()) continue;
                double s = calculeazaScorStrategic(i, j);
                if(s > maxS) { maxS = s; bestB = i; bestT = j; }
            }
        }

        if(bestB != -1) {
            std::cout << "AI Trage...\n";
            lanseazaPasare(bestB, bestT);
        } else break;
    }
}

bool Game::verificaVictorie() const {
    for(const auto& t : targets) if(!t.esteDistrus()) return false;
    return true;
}

void Game::afiseazaStare() const {
    std::cout << *this;

    std::cout << "\n[Economie] ";
    economy.showBalance();
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    TextUI::drawHeader("STARE JOC");
    os << g.weather.getWeatherReport() << "\n";
    os << "Bani: " << g.economy.getBalance() << "\n";
    os << "Pasari:\n";
    for(size_t i=0; i<g.birds.size(); ++i) os << i << ": " << *g.birds[i] << "\n";
    os << "Tinte:\n";
    for(size_t i=0; i<g.targets.size(); ++i)
        os << i << ": " << g.targets[i] << (g.targets[i].esteDistrus() ? " [X]" : "") << "\n";
    return os;
}