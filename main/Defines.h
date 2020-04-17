#pragma once
#include "Data.h"

// General

#define READ_REFRESH_DELAY 0 // milliseconds
#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Teensy interruption and reset control location

// JSON

#define JSON_ALLOCATION 262144 // bytes in the RAM

// Serials / SD

#define SERIAL_BAUD 9600 // data mode: 9600, command mode: 38400
#define SD_CHIP_SELECT 4 // SD card chip select
#define FLIGHT_NUMBER_ADDRESS 0 // initial counter value for SD card file names (using EEPROM)
#define SD_FILE_FORMAT "_flight_log.txt"

#define debug(message) { Data::set(DEBUG, message); } // debug function

  // Data formats
  #define RAW "raw_data"
  #define PROCESSED "processed_data"
  #define FILTERED "filtered_data"
  #define STATUS "statuses"
  #define DEBUG "debug"

  // Data types
  #define BMP_PRESSURE "bmp_pressure"
  #define BMP_ALTITUDE "bmp_altitude"
  #define BMP_TEMPERATURE "bmp_temperature"
  #define BNO_TEMPERATURE "bno_temperature"
  #define BNO_ORIENTATION "bno_orientation"
  #define BNO_ANGULAR_VELOCITY "bno_angular_velocity"
  #define BNO_LINEAR_ACCELERATION "bno_linear_acceleration"
  #define BNO_NET_ACCELERATION "bno_net_acceleration"
  #define BNO_GRAVITY "bno_gravity"
  #define BNO_MAGNETIC_FIELD "bno_magnetic_field"

  // Stages
  #define STAGE "stage"
  #define STAGE_STANDBY "standby"
  #define STAGE_BOOSTING "powered_ascent"
  #define STAGE_COASTING "coasting"
  #define STAGE_DROGUE_DESCENT "drogue_descent"
  #define STAGE_MAIN_DESCENT "main_descent"
  #define STAGE_LANDED "landed"

  // Statuses
  #define TRANSMISSION_TIME "time_since_startup"
  #define MAIN_CHUTE "main_chute_deployed"
  #define DROGUE_CHUTE "drogue_chute_deployed"
  #define AIRBRAKES_DEPLOYED "airbrakes_deployed"
  #define ENGINE_FIRING "engine_firing"
  #define AIRBRAKE_EXTENSION "airbrake_extension"
  #define ROLL_RANGE "safe_roll_range"
  #define PRESSURE_RANGE "safe_pressure_range"
  #define TEMPERATURE_RANGE "safe_temperature_range"
  #define ACCELERATION_RANGE "acceleration_tolerance"
  
// Debug

#define FAILURE String("FAILURE: ") // String conversion required because Arduino interprets "" as char*
#define SUCCESS String("SUCCESS: ")
#define WARNING String("WARNING: ")
#define NEUTRAL String("NEUTRAL: ")

// Sensors

#define BMPS 4 // amount of BMPs attached to teensy
#define BNOS 1 // amount of BNOs attached to teensy
#define BNO_ID 55
// I2C Addresses
#define BMP_I2C_1 0x77
#define BMP_I2C_2 0x76
#define BNO_I2C_1 0x29
#define BNO_I2C_2 0x28

#define STANDARD_PRESSURE 1025 // hPa (obtained from local weather forecast: https://www.worldweatheronline.com/edinburgh-weather/city-of-edinburgh/gb.aspx)

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

// StateMachine

#define LIFTOFF_LOOP_LENGTH 10
#define BURNOUT_LOOP_LENGTH 10
#define FREEFALL_LOOP_LENGTH 10
#define LIFTOFF_THRESHOLD 1
#define BURNOUT_THRESHOLD 2
#define FREEFALL_THRESHOLD 10
