#pragma once

// General

#define READ_REFRESH_DELAY 100 // milliseconds

// Bluetooth

#define BLUETOOTH_BAUD 9600 // data mode: 9600, command mode: 38400
#define FAILURE String("FAILURE: ") // String conversion required because Arduino interprets "" as char*
#define SUCCESS String("SUCCESS: ")
#define WARNING String("WARNING: ")
#define NEUTRAL String("NEUTRAL: ")

// Sensors

#define BMP_AMOUNT 4 // amount of BMPs attached to teensy
#define BNO_AMOUNT 1 // amount of BNOs attached to teensy

#define STANDARD_PRESSURE 1005 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)

// Airbrakes

#define AIRBRAKE_SERVO_PIN 23

  // PID
  
  #define PID_PROPORTIONAL_GAIN -5.0
  #define PID_INTEGRAL_GAIN 0.0
  #define PID_DERIVATIVE_GAIN -5.0
  #define PID_REFERENCE_ALTITUDE 3048.0 // target altitude for rocket
  #define PID_CONTROLLER_DIRECTION 0
  #define PID_MODE 1
  #define PID_SAMPLE_TIME 10
  #define PID_MIN_OUTPUT 0.0
  #define PID_MAX_OUTPUT 0.25

// Parachute

  // Drogue
  
  #define DROGUE_LOOP_LENGTH 50
  #define DROGUE_CONFIDENCE 10
  #define DROGUE_SAFETY_FACTOR 0.2 // meters, altitude decrease more than this value for the decrease to count
  
  // Main
  
  #define MAIN_LOOP_LENGTH 10
  #define MAIN_DEPLOY_ALTITUDE 179 // 457.2 according to competition rules
  #define MAIN_SAFETY_FACTOR 0 // meters, distance above MAIN_DEPLOY_ALTITUDE for main chutes to activate
