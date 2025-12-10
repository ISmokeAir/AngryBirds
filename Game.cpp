#include "Game.h"
#include <fstream>
#include <stdexcept>
#include <random>
#include <limits>

void Game::addBird(const Bird& b) {
    birds.push_back(b);
    initialBirds.push_back(b);
}

void Game::addTarget(const Target& t) {
    targets.push_back(t);
    initialTargets.push_back(t);
}

bool Game::allDestroyed() const {
    for (const auto& T : targets) if (!T.esteDistrus()) return false;
    return true;
}

void Game::simulateShot(size_t birdIdx, size_t targetIdx) {
    if (birdIdx >= birds.size() || targetIdx >= targets.size()) return;

    const Bird& b = birds[birdIdx];
    Target& t = targets[targetIdx];

    double dist = b.getPozitie().distanta(t.getPozitie());
    double shotValue = b.lanseaza(t.getPozitie());
    bool hit = t.esteLovit(shotValue);
    if (hit) {
        int damage = static_cast<int>(shotValue);
        score += damage;
    } else {
        int damage = static_cast<int>(shotValue);
        t.iaDamage(damage); // if beta logic wants integer damage anyway
    }

    stats.registerShot(hit, shotValue, dist);
}

void Game::demoRun() {
    if (birds.empty() || targets.empty()) return;

    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> birdDist(0, static_cast<int>(birds.size()) - 1);
    std::uniform_int_distribution<int> targetDist(0, static_cast<int>(targets.size()) - 1);

    int steps = 0;
    while (!allDestroyed() && steps < 50) {
        int bi = birdDist(rng);
        int ti = targetDist(rng);
        simulateShot(static_cast<size_t>(bi), static_cast<size_t>(ti));
        ++steps;
    }
}

void Game::resetToInitial() {
    birds = initialBirds;
    targets = initialTargets;
    score = 0;
    stats.reset();
}

void Game::setDifficulty(Difficulty d) {
    difficulty = d;
    for (auto& t : targets) {
        int vi = t.getViata();
        switch (d) {
            case Difficulty::Easy: vi += 20; break;
            case Difficulty::Normal: break;
            case Difficulty::Hard: vi += 50; break;
        }
        t.setViata(vi);
    }
}

void Game::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open file for saving");
    out << score << '\n';
    out << birds.size() << '\n';
    for (const auto& b : birds) {
        out << b.getNume() << ' ' << b.getPutere() << ' '
            << b.getPozitie().getX() << ' ' << b.getPozitie().getY() << '\n';
    }
    out << targets.size() << '\n';
    for (const auto& t : targets) {
        out << t.getViata() << ' ' << t.getPozitie().getX() << ' ' << t.getPozitie().getY() << '\n';
    }
}

void Game::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Cannot open file for loading");
    resetToInitial();
    int savedScore = 0;
    in >> savedScore;
    score = savedScore;
    size_t nb = 0;
    in >> nb;
    birds.clear();
    for (size_t i = 0; i < nb; ++i) {
        std::string name;
        int power;
        double x, y;
        in >> name >> power >> x >> y;
        birds.emplace_back(name, power, Vector2D(x, y));
    }
    size_t nt = 0;
    in >> nt;
    targets.clear();
    for (size_t i = 0; i < nt; ++i) {
        int vi;
        double x, y;
        in >> vi >> x >> y;
        targets.emplace_back(vi, Vector2D(x, y));
    }
}

std::vector<double> Game::computeAllDistances() const {
    std::vector<double> result;
    result.reserve(birds.size() * targets.size());
    for (const auto& b : birds)
        for (const auto& t : targets)
            result.push_back(b.getPozitie().distanta(t.getPozitie()));
    return result;
}

int Game::closestTargetIndex(const Vector2D& pos) const {
    if (targets.empty()) return -1;
    double best = std::numeric_limits<double>::max();
    int idx = -1;
    for (int i = 0; i < static_cast<int>(targets.size()); ++i) {
        double d = pos.distanta(targets[i].getPozitie());
        if (d < best) {
            best = d;
            idx = i;
        }
    }
    return idx;
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << "=== Game state ===\n";
    os << "Score: " << g.score << "\n";
    os << "Birds:\n";
    for (size_t i = 0; i < g.birds.size(); ++i)
        os << " [" << i << "] " << g.birds[i] << "\n";
    os << "Targets:\n";
    for (size_t i = 0; i < g.targets.size(); ++i)
        os << " [" << i << "] " << g.targets[i] << "\n";
    os << g.stats;
    return os;
}
