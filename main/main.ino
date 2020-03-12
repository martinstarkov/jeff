#include "SensorController.h"
#include "ParachuteController.h"
#include "Bluetooth.h"
#include "DataService.h"

SensorController* sController;
ParachuteController* pController;

#define BLUETOOTH_BAUD 9600 // data mode: 9600, command mode: 38400

#define READ_REFRESH_DELAY 100 // milliseconds

void setup() {
  Bluetooth::init(BLUETOOTH_BAUD);
  DataService::init();
  sController = new SensorController();
  sController->init();
  pController = new ParachuteController();
  pController->init();
}

void loop() {
  sController->update();
  Bluetooth::print(DataService::processData());
  delay(READ_REFRESH_DELAY);
}
