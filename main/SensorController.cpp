#include "SensorController.h"

SensorController::SensorController() {
  init();
  Bluetooth::log(SUCCESS + "Sensor controller initialized");
}

template <typename Sensor>
void SensorController::initI2C(int count, Sensor* sensors[], uint8_t addresses[]) {
  int num = 0;
  Sensor* s = new Sensor();
  for (int i = 0; i < count; i++) {
    if (i % 2 == 0) { // for I2C pair created on separate wire
      s = new Sensor(&Wire, addresses[int(floor(float(i) / 2))]);
    } else {
      s = new Sensor(&Wire1, addresses[int(floor(float(i) / 2))]);
    }
    if (s->initialized()) {
      sensors[num] = s;
      num++;
    }
  }
  if (num == count) {
    Bluetooth::log(SUCCESS + "Initialized " + String(num) + " " + String(s->getName()) + " sensor(s)");
  } else {
    Bluetooth::log(WARNING + "Only initialized " + String(num) + "/" + String(count) + " " + String(s->getName()) + " sensor(s)");
    // Bluetooth::promptConfirmation();
  }
}

void SensorController::init() {
  initI2C(BMPS, bmps, bmpAddresses);
  initI2C(BNOS, bnos, bnoAddresses);
}

float SensorController::getAltitude() {
  return average(BMPS, bmps, &BMP280::getTemperature);
}

Vector3D SensorController::getOrientation() {
  return average(BNOS, bnos, &BNO055::getOrientation);
}

template <typename Data, typename Sensor>
Data SensorController::average(int count, Sensor* sensors[], Data (Sensor::*functionPointer)()) {
  Data sum = Data(); // initialize data type so compiler doesn't complain
  if (count == 1) {
    return (sensors[0]->*functionPointer)();
  } else if (count > 1) {
    for (int i = 0; i < count; i++) {
      Data value = (sensors[i]->*functionPointer)(); // call function pointer parameter for array parameter
      //Bluetooth::print(sensors[i]->getName() + ": " + String(value)); // print individual named components of the average
      // pass value through error correction here (check that it isn't crazy)
      sum = sum + value;
    }
    return sum / count;
  } else {
    return sum; // shown as 0.0 or (0,0,0) (default value), indicates a problem in initialization of specific sensor
  }
}

/*
  Altitude units: hPa
  Altitude inaccuracy: ±1m (±0.12 hPa)
  SENSOR_TYPE_ACCELEROMETER = (1) // Gravity + linear acceleration
  SENSOR_TYPE_MAGNETIC_FIELD = (2)
  SENSOR_TYPE_ORIENTATION = (3)
  SENSOR_TYPE_GYROSCOPE = (4)
  SENSOR_TYPE_PRESSURE = (6)
  SENSOR_TYPE_GRAVITY = (9)
  SENSOR_TYPE_LINEAR_ACCELERATION = (10) // Acceleration not including gravity
  SENSOR_TYPE_ROTATION_VECTOR = (11)
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13)
  SENSOR_TYPE_TEMPERATURE_BNO 69420
  SENSOR_TYPE_TEMPERATURE_BMP 69422
  SENSOR_TYPE_PRESSURE 69424
  SENSOR_TYPE_ALTITUDE 69426
  SENSOR_TYPE_SEA_PRESSURE 69428
  sensors_vec_t acceleration; // acceleration values are in meter per second per second (m/s^2)
  sensors_vec_t magnetic; // magnetic vector values are in micro-Tesla (uT)
  sensors_vec_t orientation; // orientation values are in degrees
  sensors_vec_t gyro;        // gyroscope values are in rad/s
  float temperature; // temperature is in degrees centigrade (Celsius)
  float pressure;    // pressure in hectopascal (hPa)
*/
