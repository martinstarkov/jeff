#pragma once

// General

#define READ_REFRESH_DELAY 100 // milliseconds

// Bluetooth

#define BLUETOOTH_BAUD 9600 // data mode: 9600, command mode: 38400#define NEUTRAL String("NEUTRAL: ")
#define FAILURE String("FAILURE: ") // String conversion required because Arduino interprets "" as char*
#define SUCCESS String("SUCCESS: ")
#define WARNING String("WARNING: ")
#define NEUTRAL String("NEUTRAL: ")

// Sensors

#define BMP_AMOUNT 4 // amount of BMPs attached to teensy
#define BNO_AMOUNT 1 // amount of BNOs attached to teensy

#define STANDARD_PRESSURE 1005 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)

// Parachute

  // Drogue
  
  #define DROGUE_LOOP_LENGTH 50
  #define DROGUE_CONFIDENCE 10
  #define DROGUE_SAFETY_FACTOR 0.2 // meters, altitude decrease more than this value for the decrease to count
  
  // Main
  
  #define MAIN_LOOP_LENGTH 10
  #define MAIN_DEPLOY_ALTITUDE 179 // 457.2 according to competition rules
  #define MAIN_SAFETY_FACTOR 0 // meters, distance above MAIN_DEPLOY_ALTITUDE for main chutes to activate
