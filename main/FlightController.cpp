#include "FlightController.h"

FlightController::FlightController() {
  Bluetooth::init(BLUETOOTH_BAUD);
  init();
}

void FlightController::init() {
  sc = new SensorController();
  pc = new ParachuteController();
  ac = new AirbrakeController();
  dp = new DataProcessor();
  Bluetooth::log(SUCCESS + "Flight controller initialized");
  Bluetooth::printLog();
}

void FlightController::restart() { // Restart teensy programmatically
  Bluetooth::end(); // clear serials
  SCB_AIRCR = 0x05FA0004; // write value for restart
}

void FlightController::cycle() { // update every flight component for each microcontroller cycle
  //float altitude = sc->getAltitude();
  //Bluetooth::print("Average altitude: " + String(altitude));
  //Bluetooth::print("Average orientation: " + String(sc->getOrientation()));
  if (Bluetooth::printData) {
    Bluetooth::print("Data...");
    //Bluetooth::print("77;78;79;100101;100102;100103;30.1;30.2;30.3;31;(1,-1,1);(2,-2,2);(3,-3,3);(4,-4,4);(5,-5,5);(6,-6,6);");
  }
  
  //pc->check(altitude);

  //ac->controlLoop(altitude);
  //ac->deployFlaps();
}
