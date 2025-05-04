#include "weather_fetcher.h"
#include "curl_utils.h"
#include "config.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <iomanip>  // For std::setprecision

using json = nlohmann::json;

WeatherData WeatherFetcher::fetchWeather(const std::string& location) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string readBuffer;
    std::string encodedLocation;

    // URL encode the location string to handle spaces/special characters
    char* encoded = curl_easy_escape(curl, location.c_str(), location.length());
    if (encoded) {
        encodedLocation = encoded;
        curl_free(encoded);
    }
    else {
        encodedLocation = location;  // Fallback if encoding fails
    }

    // Use HTTPS for secure connection
    std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + encodedLocation
        + "&units=metric&appid=" + OPENWEATHER_API_KEY;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "WeatherCLI/1.0");

    // Enable verbose mode for debugging (optional)
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::string error = curl_easy_strerror(res);
        curl_easy_cleanup(curl);
        throw std::runtime_error("Network error: " + error);
    }

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    // Handle different HTTP status codes
    if (http_code == 404) {
        throw std::runtime_error("Location not found. Please check spelling and try format: 'City' or 'City,CountryCode'");
    }
    else if (http_code == 401) {
        throw std::runtime_error("Invalid API key. Please check config.h");
    }
    else if (http_code != 200) {
        throw std::runtime_error("API error: HTTP " + std::to_string(http_code));
    }

    try {
        auto j = json::parse(readBuffer);
        WeatherData data;

        // Extract location name from API response for better accuracy
        data.location = j.value("name", location);
        std::string country = j["sys"].value("country", "");
        if (!country.empty()) {
            data.location += ", " + country;
        }

        // Round temperature to 1 decimal place
        data.temperature = std::round(j["main"]["temp"].get<double>() * 10) / 10;
        data.conditions = j["weather"][0]["main"].get<std::string>();
        data.humidity = j["main"]["humidity"].get<int>();
        data.windSpeed = j["wind"].value("speed", 0.0);

        return data;
    }
    catch (const json::exception& e) {
        throw std::runtime_error("Data parsing failed: " + std::string(e.what()) +
            "\nRaw response: " + readBuffer.substr(0, 200) + "...");
    }
}