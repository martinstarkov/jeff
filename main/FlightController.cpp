#include "FlightController.h"

FlightController::FlightController() {
  Bluetooth::init(BLUETOOTH_BAUD);
  //dataService = new DataService();
  //parachuteController = new ParachuteController();
  //airbrakeController = new AirbrakeController();
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  //dataService->update();
  //ProcessedData currentData = dataService->getProcessedData();
  
  //Bluetooth::print("Raw Data:");
  if (Bluetooth::printData) {
    Bluetooth::print("77;78;79;100101;100102;100103;30.1;30.2;30.3;31;(1,-1,1);(2,-2,2);(3,-3,3);(4,-4,4);(5,-5,5);(6,-6,6);");
    //dataService->printRawData();
  }
  //Bluetooth::print("Processed Data:");
  //dataService->printProcessedData();
  
  //parachuteController->check(currentData);

  //airbrakeController->controlLoop(currentData.altitude);
  //airbrakeController->deployFlaps();
}
