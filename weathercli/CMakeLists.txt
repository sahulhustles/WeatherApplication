cmake_minimum_required(VERSION 3.10)
project(WeatherCLI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find CURL package
find_package(CURL REQUIRED)
if(NOT CURL_FOUND)
    message(FATAL_ERROR "CURL library not found")
endif()

# Warning configuration (FIXED LINE 11)
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Add executable with all source files
add_executable(WeatherCLI
    src/main.cpp
    src/weather_fetcher.cpp
    src/location_service.cpp
    src/curl_utils.cpp
)

# Link libraries (FIXED - must come after add_executable)
target_link_libraries(WeatherCLI PRIVATE 
    CURL::libcurl
)

# Include directories
target_include_directories(WeatherCLI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
)