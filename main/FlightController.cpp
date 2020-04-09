#include "FlightController.h"

FlightController::FlightController() {
  Bluetooth::init(BLUETOOTH_BAUD);
  init();
}

void FlightController::init() {
  sc = new SensorController();
  //pc = new ParachuteController();
  //ac = new AirbrakeController();
  delay(3000);
}

void FlightController::restart() {
  Bluetooth::end(); // clear serials
  SCB_AIRCR = 0x05FA0004; // write value for restart
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  //dataService->update();
  //ProcessedData currentData = dataService->getProcessedData();
  Bluetooth::print("Average altitude: " + String(sc->getAltitude()));
  Bluetooth::print("Average orientation: " + String(sc->getOrientation()));
  //Bluetooth::print("Raw Data:");
  if (Bluetooth::printData) {
    Bluetooth::print("77;78;79;100101;100102;100103;30.1;30.2;30.3;31;(1,-1,1);(2,-2,2);(3,-3,3);(4,-4,4);(5,-5,5);(6,-6,6);");
    //dataService->printRawData();
  }
  //dataService->printProcessedData();
  
  //parachuteController->check(currentData);

  //airbrakeController->controlLoop(currentData.altitude);
  //airbrakeController->deployFlaps();
}
