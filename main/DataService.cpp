#include "DataService.h"

DataService* DataService::instance;
float DataService::currentPressure;
float DataService::currentTemperature;
float DataService::currentAltitude;

void DataService::init() { // make sure DataService is only able to initialize once
  if (instance == 0) {
    instance = new DataService();
    // other init functions (setting default values for temp, pressure, etc)
  }
}

void DataService::printData() {
  Bluetooth::print("Pressure: " + String(getPressure()));
  Bluetooth::print("Temperature: " + String(getTemperature()));
  Bluetooth::print("Altitude: " + String(getAltitude()));
}

float DataService::getAltitude() {
  return currentAltitude;
}

void DataService::setAltitude(float altitude) {
  currentAltitude = altitude;
}


float DataService::getTemperature() {
  return currentTemperature;
}

void DataService::setTemperature(float temperature) {
  currentTemperature = temperature;
}


float DataService::getPressure() {
  return currentPressure;
}

void DataService::setPressure(float pressure) {
  currentPressure = pressure;
}
