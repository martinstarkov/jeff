#include "CommunicationController.h"

void CommunicationController::update() {
  Serials::print("Time: " + Data::get(TRANSMISSION_TIME));
  processInput(Data::getCommand());
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

void CommunicationController::processInput(String input) {
  if (input != "") {
    if (input == "init" || input == "initialize" || input == "restart") {
      Serials::end();
      (*(volatile uint32_t *)0xE000ED0C) = 0x05FA0004;
    } else if (input == "bmp") {
      if (bmp) {
        bmp = false;
      } else {
        bmp = true;
      }
    } else if (input == "bno") {
      if (bno) {
        bno = false;
      } else {
        bno = true;
      }
    }
    Data::setCommand(""); // reset command after actions completed
  }
}
