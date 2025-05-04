#include "location_service.h"
#include "curl_utils.h"
#include "config.h"
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

std::string LocationService::getLocationByIP() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, IPAPI_URL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error("Failed to fetch location data");
    }

    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_cleanup(curl);

    if (http_code != 200) {
        throw std::runtime_error("Location API returned HTTP " + std::to_string(http_code));
    }

    try {
        auto j = json::parse(readBuffer);
        if (j["status"] == "success") {
            std::string city = j["city"];
            std::string country = j["country"];
            return city + ", " + country;
        }
        throw std::runtime_error("Location API request failed");
    } catch (const json::exception&) {
        throw std::runtime_error("Failed to parse location data");
    }
}

std::string LocationService::getCurrentLocation() {
    try {
        return getLocationByIP();
    } catch (const std::exception&) {
        return "Unknown Location";
    }
}