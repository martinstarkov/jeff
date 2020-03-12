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

float BNO055::getTemperature() { // Ambient temperature (Celsius)
  return instance->getTemp();
}

Vector3D BNO055::getOrientation() { // 3d Euler Angles (degrees)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_EULER);
  return Vector3D(data.orientation.x, data.orientation.y, data.orientation.z);
}

Vector3D BNO055::getAngularVelocity() { // Gyroscope, rotation speed (rad / s)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_GYROSCOPE);
  return Vector3D(data.gyro.x, data.gyro.y, data.gyro.z);
}

Vector3D BNO055::getLinearAcceleration() { // Acceleration without gravity (m / s^2)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_LINEARACCEL);
  return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
}

Vector3D BNO055::getNetAcceleration() { // Acceleration with gravity (m / s^2)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
}

Vector3D BNO055::getGravity() { // Gravity (m / s^2)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_GRAVITY);
  return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
}

Vector3D BNO055::getMagneticField() { // Magnetometer (uT)
  sensors_event_t data;
  instance->getEvent(&data, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  return Vector3D(data.magnetic.x, data.magnetic.y, data.magnetic.z);
}
