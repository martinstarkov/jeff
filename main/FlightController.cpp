#include "FlightController.h"

FlightController::FlightController() {
  Bluetooth::init(BLUETOOTH_BAUD);
  dataService = new DataService();
  parachuteController = new ParachuteController();
  airbrakeController = new AirbrakeController();
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  dataService->update();
  ProcessedData currentData = dataService->getProcessedData();
  
  Bluetooth::print("Raw Data:");
  dataService->printRawData();
  Bluetooth::print("Processed Data:");
  dataService->printProcessedData();
  
  parachuteController->check(currentData);

  airbrakeController->loop(currentData.altitude);
  airbrakeController->deployFlaps();
}
