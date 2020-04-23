#pragma once
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include "Vector3D.h"
#include "Defines.h"
#include "Data.h"

class BNO055 {
  private:
    Adafruit_BNO055* instance;
    sensors_event_t data;
    uint8_t address;
    TwoWire* wire;
  public:
    BNO055() {}
    BNO055(TwoWire* wire, uint8_t address): instance(new Adafruit_BNO055(-1, address, wire)), address(address), wire(wire) {}
    bool init() {
      if (instance->begin()) {
        Data::add(DEBUG, SUCCESS + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
        return true;
      }
      Data::add(DEBUG, FAILURE + "BNO sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " not detected, check wiring / I2C address");
      return false;
    }
    float getTemperature() { // Temperature (Celsius)
      return instance->getTemp();
    }
    Vector3D getOrientation() { // 3d Euler Angles (degrees)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_EULER);
      return Vector3D(data.orientation.x, data.orientation.y, data.orientation.z);
    }
    Vector3D getAngularVelocity() { // Gyroscope, rotation speed (rad / s)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_GYROSCOPE);
      return Vector3D(data.gyro.x, data.gyro.y, data.gyro.z);
    }
    Vector3D getLinearAcceleration() { // Acceleration without gravity (m / s^2)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_LINEARACCEL);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getNetAcceleration() { // Acceleration with gravity (m / s^2)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_ACCELEROMETER);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getGravity() { // Gravity (m / s^2)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_GRAVITY);
      return Vector3D(data.acceleration.x, data.acceleration.y, data.acceleration.z);
    }
    Vector3D getMagneticField() { // Magnetometer (uT)
      instance->getEvent(&data, Adafruit_BNO055::VECTOR_MAGNETOMETER);
      return Vector3D(data.magnetic.x, data.magnetic.y, data.magnetic.z);
    }
};
