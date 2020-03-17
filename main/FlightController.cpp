#include "FlightController.h"

FlightController::FlightController() {
  Bluetooth::init(BLUETOOTH_BAUD);
  dataService = new DataService();
  parachuteController = new ParachuteController();
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  dataService->update();
  
  Bluetooth::print("Raw Data:");
  dataService->printRawData();
  Bluetooth::print("Processed Data:");
  dataService->printProcessedData();
  
  parachuteController->check(dataService->getProcessedData());
}
