#include "BMP280.h"

BMP280::BMP280(TwoWire* theWire, uint8_t address, float standardPressure) {
  
  sPressure = standardPressure;
  instance = new Adafruit_BMP280(theWire);
  
  instance->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating mode */
  Adafruit_BMP280::SAMPLING_X2,                           /* Temperature oversampling */
  Adafruit_BMP280::SAMPLING_X16,                          /* Pressure oversampling */
  Adafruit_BMP280::FILTER_X16,                            /* Filtering */
  Adafruit_BMP280::STANDBY_MS_500);                       /* Standby time */
  
  if (!instance->begin(address)) {
    // BMP sensor not detected. Check wiring.
    // while (1) {}
  }
}

float BMP280::getPressure() {
  return instance->readPressure();
}

float BMP280::getAltitude() {
  return instance->readAltitude(sPressure);
}

float BMP280::getTemperature() {
  return instance->readTemperature();
}
