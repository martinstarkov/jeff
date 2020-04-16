#pragma once
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "Defines.h"

class BMP280 {
  private:
    Adafruit_BMP280* instance;
    bool status = false;
    String name = "BMP280";
    String id = "";
  public:
    BMP280() {}
    BMP280(TwoWire* wire, uint8_t address) {
      instance = new Adafruit_BMP280(wire);
      instance->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating mode */
      Adafruit_BMP280::SAMPLING_X2,                           /* Temperature oversampling */
      Adafruit_BMP280::SAMPLING_X16,                          /* Pressure oversampling */
      Adafruit_BMP280::FILTER_X16,                            /* Filtering */
      Adafruit_BMP280::STANDBY_MS_500);                       /* Standby time */
      if (!instance->begin(address)) {
        debug(FAILURE + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " not detected, check wiring / I2C address");
      } else {
        id = "BMP280-" + String(address, HEX) + "-" + String(int(wire));
        status = true;
        debug(SUCCESS + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
      }
    }
    String getId() {
      return id;
    }
    String getName() {
      return name;
    }
    bool initialized() {
      return status && id != "";
    }
    float getPressure() { // Pressure (pascals)
      return instance->readPressure();
    }
    float getAltitude() { // Altitude (meters)
      return instance->readAltitude(STANDARD_PRESSURE);
    }
    float getTemperature() { // Ambient temperature (Celsius)
      return instance->readTemperature();
    }
};
