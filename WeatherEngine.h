#ifndef OOP_WEATHERENGINE_H
#define OOP_WEATHERENGINE_H

#include <string>
#include <vector>

enum class WeatherType { Sunny, Rainy, Stormy, Foggy };

class WeatherEngine {
private:
    double windSpeedX;
    double windSpeedY;
    double rainIntensity;
    double visibility;
    WeatherType currentType;

public:
    WeatherEngine();
    
    void updateWeather();
    
    double getWindX() const;
    double getWindY() const;
    double getFrictionMultiplier() const;
    std::string getWeatherReport() const;
    
    bool isStormy() const;
};

#endif