#include "BMP280.h"

BMP280::BMP280(TwoWire* wire, uint8_t address, float sp) {
  
  wire = wire;
  address = address;
  standardPressure = sp;
  
  instance = new Adafruit_BMP280(wire);
  
  instance->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating mode */
  Adafruit_BMP280::SAMPLING_X2,                           /* Temperature oversampling */
  Adafruit_BMP280::SAMPLING_X16,                          /* Pressure oversampling */
  Adafruit_BMP280::FILTER_X16,                            /* Filtering */
  Adafruit_BMP280::STANDBY_MS_500);                       /* Standby time */
  
  if (!instance->begin(address)) {
    Bluetooth::print(FAILURE + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " not detected. Check wiring / I2C address");
  } else {
    status = true;
    Bluetooth::print(SUCCESS + "BMP sensor with address=" + String(address, HEX) + ", wire=" + String(int(wire)) + " initialized");
  }
}

bool BMP280::initialized() {
  return status;
}

float BMP280::getPressure() {
  return instance->readPressure();
}

float BMP280::getAltitude() {
  return instance->readAltitude(standardPressure);
}

float BMP280::getTemperature() {
  return instance->readTemperature();
}
