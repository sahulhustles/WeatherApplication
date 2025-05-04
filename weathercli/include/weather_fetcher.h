#pragma once
#include <string>

struct WeatherData {
    std::string location;
    double temperature;
    std::string conditions;
    double humidity;
    double windSpeed;
};

class WeatherFetcher {
public:
    WeatherData fetchWeather(const std::string& location);
};