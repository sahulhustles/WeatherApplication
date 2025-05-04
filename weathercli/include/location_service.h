#pragma once
#include <string>

class LocationService {
public:
    std::string getCurrentLocation();
    
private:
    std::string getLocationByIP();
};