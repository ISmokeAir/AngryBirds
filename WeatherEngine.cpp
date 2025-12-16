#include "WeatherEngine.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <cmath>

WeatherEngine::WeatherEngine() 
    : windSpeedX(0), windSpeedY(0), rainIntensity(0), visibility(100.0), currentType(WeatherType::Sunny) {
    updateWeather();
}

void WeatherEngine::updateWeather() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDist(0, 3);
    std::uniform_real_distribution<> windDist(-15.0, 15.0);
    std::uniform_real_distribution<> rainDist(0.0, 10.0);

    int t = typeDist(gen);
    currentType = static_cast<WeatherType>(t);
    
    windSpeedX = windDist(gen);
    windSpeedY = windDist(gen) * 0.2; 
    
    switch (currentType) {
        case WeatherType::Sunny:
            rainIntensity = 0.0;
            visibility = 100.0;
            if (std::abs(windSpeedX) > 5.0) windSpeedX *= 0.5;
            break;
        case WeatherType::Rainy:
            rainIntensity = rainDist(gen);
            visibility = 70.0;
            break;
        case WeatherType::Stormy:
            rainIntensity = 10.0;
            windSpeedX *= 1.5;
            visibility = 40.0;
            break;
        case WeatherType::Foggy:
            rainIntensity = 0.5;
            windSpeedX *= 0.1;
            visibility = 15.0;
            break;
    }
}

double WeatherEngine::getWindX() const { return windSpeedX; }
double WeatherEngine::getWindY() const { return windSpeedY; }

double WeatherEngine::getFrictionMultiplier() const {
    if (currentType == WeatherType::Rainy) return 1.2;
    if (currentType == WeatherType::Stormy) return 1.5;
    return 1.0;
}

std::string WeatherEngine::getWeatherReport() const {
    std::stringstream ss;
    ss << "METEO: ";
    switch (currentType) {
        case WeatherType::Sunny: ss << "Soare | "; break;
        case WeatherType::Rainy: ss << "Ploaie | "; break;
        case WeatherType::Stormy: ss << "FURTUNA | "; break;
        case WeatherType::Foggy: ss << "Ceata | "; break;
    }
    ss << "Vant: " << std::fixed << std::setprecision(1) << windSpeedX << "m/s | ";
    ss << "Vizibilitate: " << (int)visibility << "%";
    return ss.str();
}

bool WeatherEngine::isStormy() const {
    return currentType == WeatherType::Stormy;
}