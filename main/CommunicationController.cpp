#include "CommunicationController.h"

CommunicationController::CommunicationController() {
  // Serial initialization
  Serials::begin();
//  while (Data::getCommand() != COMMAND_INIT) { // wait for init command
//    Serials::print(WAIT_FOR_INIT + Data::getCommand());
//  }
  Data::add(DEBUG, NEUTRAL + "Initializing Darwin");
  // SD initialization
  sd = new Logger();
}

void CommunicationController::update() {
  processInput(Data::getCommand());
  if (data) {
    Serials::print(Data::getData());
    sd->log(Data::getData());
  }
  if (time) {
    Serials::print("Time: " + Data::get(TRANSMISSION_TIME));
  }
  if (bmp) {
    Serials::print("--- BMP ---");
    Serials::print("Altitude: " + Data::get(ALTITUDE));
    Serials::print("Pressure: " + Data::get(PRESSURE));
    Serials::print("Temperature: " + Data::get(BMP_TEMPERATURE));
  }
  if (bno) {
    Serials::print("--- BNO ---");
    Serials::print("Orientation: " + Data::get(ORIENTATION));
    Serials::print("Acceleration: " + Data::get(NET_ACCELERATION));
    Serials::print("Angular Velocity: " + Data::get(ANGULAR_VELOCITY));
  }
}

void CommunicationController::restartTeensy() {
  sd->close();
  Serials::end();
  (*(volatile uint32_t *)0xE000ED0C) = 0x05FA0004;
}

void CommunicationController::processInput(String input) {
  if (input != "") {
    if (input == COMMAND_RESTART) {
      restartTeensy();
    } else if (input == COMMAND_DATA) {
      if (data) {
        data = false;
      } else {
        data = true;
      }
    }
    Data::setCommand(""); // reset command after actions completed
  }
}
