#pragma once
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "Defines.h"
#include "Data.h"

class BMP280 {
  private:
    Adafruit_BMP280* instance;
    uint8_t address;
    TwoWire* wire;
  public:
    BMP280(TwoWire* wire, uint8_t address): instance(new Adafruit_BMP280(wire)), address(address), wire(wire) {}
    /*
    instance->setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating mode
    Adafruit_BMP280::SAMPLING_X2,                           // Temperature oversampling
    Adafruit_BMP280::SAMPLING_X16,                          // Pressure oversampling
    Adafruit_BMP280::FILTER_X16,                            // Filtering
    Adafruit_BMP280::STANDBY_MS_500);                       // Standby time
    */
    bool init() {
      if (instance->begin(address)) {
        Data::add(DEBUG, SUCCESS + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
        return true;
      }
      Data::add(DEBUG, FAILURE + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " not detected, check wiring / I2C address");
      return false;
    }
    float getPressure() { // Pressure (pascals)
      return instance->readPressure();
    }
    float getAltitude() { // Altitude (meters)
      return instance->readAltitude(STANDARD_PRESSURE);
    }
    float getTemperature() { // Temperature (Celsius)
      return instance->readTemperature();
    }
};
