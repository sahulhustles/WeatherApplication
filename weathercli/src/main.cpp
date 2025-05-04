#include "weather_fetcher.h"
#include "location_service.h"
#include <iostream>
#include <string>

void displayHelp() {
    std::cout << "\nWeather CLI Application\n";
    std::cout << "-----------------------\n";
    std::cout << "Options:\n";
    std::cout << "  1. Press Enter for auto-detected location\n";
    std::cout << "  2. Enter city name (e.g., London)\n";
    std::cout << "  3. Enter city,country (e.g., Paris,FR)\n";
    std::cout << "  4. Type 'exit' to quit\n\n";
}

int main(int argc, char* argv[]) {
    WeatherFetcher weatherFetcher;
    LocationService locationService;

    while (true) {
        std::cout << "\nEnter location (city or city,country): ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            // Auto-detect location
            try {
                std::string location = locationService.getCurrentLocation();
                std::cout << "Detected location: " << location << "\n";
                input = location;
            }
            catch (...) {
                std::cerr << "Error: Could not detect your location\n";
                continue;
            }
        }
        else if (input == "exit") {
            break;
        }

        try {
            WeatherData weather = weatherFetcher.fetchWeather(input);

            std::cout << "\nWeather for " << input << ":\n";
            std::cout << "---------------------------------\n";
            std::cout << "Temperature: " << weather.temperature << "°C\n";
            std::cout << "Conditions: " << weather.conditions << "\n";
            std::cout << "Humidity: " << weather.humidity << "%\n";
            std::cout << "Wind Speed: " << weather.windSpeed << " km/h\n";
            std::cout << "---------------------------------\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cerr << "Format: 'City' or 'City,CountryCode'\n";
        }
    }

    return 0;
}