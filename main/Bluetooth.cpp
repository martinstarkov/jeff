#include "Bluetooth.h"

// Singleton variable declarations
Bluetooth* Bluetooth::bt;
String Bluetooth::history;
bool Bluetooth::printData;

void Bluetooth::init(int baud) {
  if (bt == 0) {
    // Initialize singleton and static variables
    bt = new Bluetooth();
    history = "";
    printData = false;
    Serial.begin(baud);
    Serial2.begin(baud);
    while (!Serial) {} // Initializing Regular Serial...
    while (!Serial2) {} // Initializing Bluetooth Serial...
    log(SUCCESS + "Bluetooth Serial Initialized");
  }
}

void Bluetooth::end() {
  Serial.end();
  Serial2.end();
}

void Bluetooth::print(String text, bool newline) {
  if (newline) {
    Serial.println(text);
    Serial2.println(text);
  } else {
    Serial.print(text);
    Serial2.print(text);
  }
}

String Bluetooth::getLog() {
  return history;
}

void Bluetooth::resetLog() {
  history = "";
}

void Bluetooth::log(String s) {
  history += s + ";";
}

void serialEvent2() {
  if (Serial2.available()) {
    Bluetooth::inputHandler(Serial2.readString());
  }
}

void Bluetooth::inputHandler(String input) {
  if (input == "init") {
    log(NEUTRAL + "Initializing Jeff...");
  } else if (input == "restart") {
    log(NEUTRAL + "Restarting Flight Controller");
  } else if (input == "startData") {
    log(NEUTRAL + "Starting data printing");
    printData = true;
  } else if (input == "stopData") {
    log(NEUTRAL + "Stopping data printing");
    printData = false;
  }
}
