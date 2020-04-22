#include "SensorController.h"

SensorController::SensorController() {
  init();
  //debug(SUCCESS + "Sensor controller initialized");
}

//template <typename Sensor>
//void SensorController::initI2C(int count, Sensor* sensors[], uint8_t addresses[]) {
//  int num = 0;
//  Sensor* s = new Sensor();
//  for (int i = 0; i < count; i++) {
//    if (i % 2 == 0) { // for I2C pair created on separate wire
//      s = new Sensor(&Wire, addresses[int(floor(float(i) / 2))]);
//    } else {
//      s = new Sensor(&Wire1, addresses[int(floor(float(i) / 2))]);
//    }
//    if (s->initialized()) {
//      sensors[num] = s;
//      num++;
//    }
//  }
//  if (num == count) {
//    debug(SUCCESS + "Initialized " + String(num) + " " + String(s->getName()) + " sensor(s)");
//  } else {
//    debug(WARNING + "Only initialized " + String(num) + "/" + String(count) + " " + String(s->getName()) + " sensor(s)");
//    // promptConfirmation();
//  }
//}

void SensorController::initBMPs() {
  bmpCount = 0;
  if (BMPS > 0) {
    for (uint8_t i = 0; i < sizeof(BMPAddresses) / sizeof(uint8_t); i++) { // initalize all BMPs
      BMP280* bmp = new BMP280(&Wire, BMPAddresses[i]);
      if (bmp->init()) {
        bmps[bmpCount] = bmp;
        bmpCount++;
      }
      bmp = new BMP280(&Wire1, BMPAddresses[i]);
      if (bmp->init()) {
        bmps[bmpCount] = bmp;
        bmpCount++;
      }
    }
    if (bmpCount == BMPS) {
      //debug(SUCCESS + String(bmpCount) + "/" + String(BMPS) + " BMP sensor(s) initialized");
    } else if (bmpCount == 0) {
      //debug(FAILURE + "No BMP sensor(s) detected");
    } else { // some sensors but not all have initialized correctly
      //debug(WARNING + String(bmpCount) + "/" + String(BMPS) + " BMP sensor(s) initialized");
    }
  }
}
void SensorController::initBNOs() {
  bnoCount = 0;
  if (BNOS > 0) {
    for (uint8_t i = 0; i < sizeof(BNOAddresses) / sizeof(uint8_t); i++) {
      BNO055* bno = new BNO055(&Wire, BNOAddresses[i]);
      if (bno->init()) {
        bnos[bnoCount] = bno;
        bnoCount++;
      }
    }
    if (bnoCount == BNOS) {
      //debug(SUCCESS + String(bnoCount) + "/" + String(BNOS) + " BNO sensor(s) initialized");
    } else if (bnoCount == 0) {
      //debug(FAILURE + "No BNO sensor(s) detected");
    } else { // some sensors but not all have initialized correctly
      //debug(WARNING + String(bnoCount) + "/" + String(BNOS) + " BNO sensor(s) initialized");
    }
  }
}

void SensorController::init() {
  initBMPs();
  initBNOs();
}

void SensorController::update() {
  Data::add(PRESSURE, String(average(bmpCount, bmps, &BMP280::getPressure), 1));
  Data::add(ALTITUDE, String(average(bmpCount, bmps, &BMP280::getAltitude), 1));
  Data::add(BMP_TEMPERATURE, String(average(bmpCount, bmps, &BMP280::getTemperature), 1));
  Data::add(BNO_TEMPERATURE, String(average(bnoCount, bnos, &BNO055::getTemperature), 0));
  Data::add(ORIENTATION, String(average(bnoCount, bnos, &BNO055::getOrientation)));
  Data::add(ANGULAR_VELOCITY, String(average(bnoCount, bnos, &BNO055::getAngularVelocity)));
  Data::add(NET_ACCELERATION, String(average(bnoCount, bnos, &BNO055::getNetAcceleration)));
  //Data::add(MAGNETIC_FIELD, String(average(bnoCount, bnos, &BNO055::getMagneticField))); // optional
  //Data::add(LINEAR_ACCELERATION, String(average(bnoCount, bnos, &BNO055::getLinearAcceleration))); // optional
  //Data::add(GRAVITY, String(average(bnoCount, bnos, &BNO055::getGravity))); // optional
}

template <typename Data, typename Sensor>
Data SensorController::average(int count, Sensor* sensors[], Data (Sensor::*functionPointer)()) {
  Data sum = Data(); // initialize data type so compiler doesn't complain
  if (count == 1) {
    return (sensors[0]->*functionPointer)();
  } else if (count > 1) {
    for (int i = 0; i < count; i++) {
      Data value = (sensors[i]->*functionPointer)(); // call function pointer parameter for array parameter
      //Serial.println(sensors[i]->getName() + ": " + String(value)); // print individual named components of the average
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
