#pragma once
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include "Vector3D.h"
#include "Defines.h"

class BNO055 {
  private:
    Adafruit_BNO055* instance;
    bool status = false;
    String name = "BNO055";
    String id = "";
  public:
    BNO055() {}
    BNO055(TwoWire* wire, uint8_t address) {
      instance = new Adafruit_BNO055(BNO_ID, address, wire);
      if (!instance->begin()) {
        debug(FAILURE + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " not detected, check wiring / I2C address");
      } else {
        id = "BNO055-" + String(address, HEX) + "-" + String(int(wire));
        status = true;
        debug(SUCCESS + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
      }
    }
    String getId() {
      return id;
    }
    String getName() {
      return name;
    }
    bool initialized() {
      return status;
    }
    float getTemperature() { // Ambient temperature (Celsius)
      return instance->getTemp();
    }
    Vector3D getOrientation() { // 3d Euler Angles (degrees)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_EULER);
      return Vector3D(data.orientation.x, data.orientation.y, data.orientation.z);
    }
    Vector3D getAngularVelocity() { // Gyroscope, rotation speed (rad / s)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_GYROSCOPE);
      return Vector3D(data.gyro.x, data.gyro.y, data.gyro.z);
    }
    Vector3D getLinearAcceleration() { // Acceleration without gravity (m / s^2)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_LINEARACCEL);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getNetAcceleration() { // Acceleration with gravity (m / s^2)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_ACCELEROMETER);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getGravity() { // Gravity (m / s^2)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_GRAVITY);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getMagneticField() { // Magnetometer (uT)
      sensors_event_t data;
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_MAGNETOMETER);
      return Vector3D(data.magnetic.x, data.magnetic.y, data.magnetic.z);
    }
};
