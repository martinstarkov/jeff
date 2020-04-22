#include "DataService.h"

DataService::DataService() {
  sc = new SensorController();
}

void DataService::update() {
  sc->update();
}
