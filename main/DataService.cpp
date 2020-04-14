#include "DataService.h"

DataService::DataService() {
  sc = new SensorController();
  debug(SUCCESS + "Data controller initialized");
}

void DataService::update() {
  sc->update();
}
