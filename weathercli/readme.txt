Weather CLI App
=================
A command-line application written in C++ that fetches current weather information using the OpenWeatherMap API.

Features:
- Fetches weather data like temperature, humidity, wind speed, etc.
- Allows users to check weather by entering the city name.
- Displays the information in a user-friendly format.

Requirements:
-------------
- C++ Compiler (e.g., GCC, Clang)
- cURL library for making HTTP requests (Ensure it is installed and configured properly)
- JSON parsing library (e.g., nlohmann/json)

Setup Instructions:
-------------------
1. Install the required dependencies:
   - Install cURL: 
     - On Ubuntu: `sudo apt-get install libcurl4-openssl-dev`
     - On Windows: Download the cURL library from https://curl.se/windows/
   
   - Install nlohmann/json:
     - You can download the single-header version of nlohmann/json from https://github.com/nlohmann/json

2. Obtain an API key from OpenWeatherMap:
   - Sign up for an API key from https://openweathermap.org/api
   
3. Clone the repository or download the source code.

4. Configure your API key:
   - Open the source code file and replace `YOUR_API_KEY_HERE` with your actual OpenWeatherMap API key.

5. Compile the program:
   - Use your C++ compiler to compile the application. If using g++, you can do it with the following command:
     ```bash
     g++ -o weather_app weather_app.cpp -lcurl
     ```

6. Run the program:
   - Execute the compiled application:
     ```bash
     ./weather_app
     ```
   - Enter a city name when prompted to get the current weather.

Example usage:
--------------
$ ./weather_app
Enter city name: London
Fetching weather data...
City: London
Temperature: 15°C
Humidity: 70%
Wind Speed: 5 m/s

Important Notes:
----------------
- Make sure your system has access to the internet, as the program needs to make HTTP requests to OpenWeatherMap.
- You can change the units in the OpenWeatherMap API request by modifying the API URL (`metric` for Celsius or `imperial` for Fahrenheit).
- If you encounter errors regarding cURL or JSON, make sure the respective libraries are installed correctly.

License:
--------
This project is open-source and licensed under the MIT License.

Credits:
--------
- OpenWeatherMap API: https://openweathermap.org/api
- cURL: https://curl.se/
- nlohmann/json: https://github.com/nlohmann/json

For any issues or contributions, feel free to open an issue or submit a pull request.

Enjoy the app and have fun exploring the weather data!
