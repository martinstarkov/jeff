#include "DataService.h"

DataService* DataService::instance;

void DataService::init() {
  if (instance == 0) {
    instance = new DataService();
    // other init
  }
}

float DataService::getAltitude() {
  return instance->currentAltitude;
}

void DataService::setAltitude(float altitude) {
  instance->currentAltitude = altitude;
}


float DataService::getTemperature() {
  return instance->currentTemperature;
}

void DataService::setTemperature(float temperature) {
  instance->currentTemperature = temperature;
}


float DataService::getPressure() {
  return instance->currentPressure;
}

void DataService::setPressure(float pressure) {
  instance->currentPressure = pressure;
}
