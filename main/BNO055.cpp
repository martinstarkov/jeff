#include "BNO055.h"

BNO055::BNO055(TwoWire* wire, uint8_t address, int id) {
  
  wire = wire;
  id = id;
  address = address;
  
  instance = new Adafruit_BNO055(id, address, wire);
  
  if (!instance->begin()) {
    Bluetooth::print(FAILURE + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + ", id=" + String(id) + " not detected. Check wiring / I2C address");
  } else {
    status = true;
    Bluetooth::print(SUCCESS + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
  }
}

bool BNO055::initialized() {
  return status;
}

//bnos[i]->getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
//bnos[i]->getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
//bnos[i]->getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
//bnos[i]->getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
//bnos[i]->getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);

float BNO055::getTemperature() {
  return instance->getTemp();
}

Vector3D BNO055::getOrientation() {
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_EULER);
  return Vector3D(data.orientation.x, data.orientation.y, data.orientation.z);
}
