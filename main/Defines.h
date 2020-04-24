#pragma once

// General

#define SCB_AIRCR (*(volatile uint32_t *)0xE000ED0C) // Teensy interruption and reset control location

// Serials / SD

#define SERIAL_BAUD 115200

// Bluetooth commands
#define WAIT_FOR_INIT String("Waiting for initialization ('init'), current input: ")
#define COMMAND_INIT String("init")
#define COMMAND_RESTART String("restart")
#define COMMAND_DATA String("data")
#define COMMAND_TIME String("time")

  // Data formats
  #define RAW String("RAW")
  #define PROCESSED String("PRCSD")
  #define FILTERED String("FLTR")
  #define STATUS String("STAT")
  #define DEBUG String("D")

  // Data types
  #define PRESSURE String("press")
  #define ALTITUDE String("alt")
  #define BMP_TEMPERATURE String("bmp_temp")
  #define BNO_TEMPERATURE String("bno_temp")
  #define ORIENTATION String("orien")
  #define ANGULAR_VELOCITY String("ng_vel")
  #define NET_ACCELERATION String("net_accel")
  #define MAGNETIC_FIELD String("mag_fld")
  #define LINEAR_ACCELERATION String("lin_accel")
  #define GRAVITY String("g")

  // Stages
  #define STAGE "stage"//"S"//
  #define STAGE_STANDBY "standby"//"1"//
  #define STAGE_POWERED_ASCENT "powered_ascent"//"2"//
  #define STAGE_COASTING "coasting"//"3"//
  #define STAGE_DROGUE_DESCENT "drogue_descent"//"4"//
  #define STAGE_MAIN_DESCENT "main_descent"//"5"//
  #define STAGE_LANDED "landed"//"6"//

  // Statuses
  #define CYCLE "cycle"//"c"//
  #define TRANSMISSION_TIME String("time")//"ut"//
  #define AIRBRAKES_DEPLOYED "airbrakes_deployed"
  #define AIRBRAKE_EXTENSION "airbrake_extension"
  
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

// State Machine

#define LIFTOFF_LOOP_LENGTH 10
#define LIFTOFF_CONFIDENCE 8 // how many of the loop values must be evaluated as true in order for computer to consider liftoff event
#define LIFTOFF_THRESHOLD 1 // m / s^2, net acceleration on smallest axis must be above this value
#define BURNOUT_LOOP_LENGTH 10
#define BURNOUT_CONFIDENCE 8
#define BURNOUT_THRESHOLD -4 // m / s^2, net acceleration on smallest axis must be below this value
