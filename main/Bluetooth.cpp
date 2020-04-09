#include "Bluetooth.h"

// Singleton variable declarations
Bluetooth* Bluetooth::bt;
String Bluetooth::logHistory;
bool Bluetooth::printData;

void Bluetooth::init(int baud) {
  if (bt == 0) {
    // Initialize singleton and static variables
    bt = new Bluetooth();
    logHistory = "";
    printData = false;
    Serial.begin(baud);
    Serial2.begin(baud);
    while (!Serial) {} // Initializing Regular Serial...
    while (!Serial2) {} // Initializing Bluetooth Serial...
    print(SUCCESS + "Bluetooth serial initialized");
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
  return logHistory;
}

void Bluetooth::printLog() {
  print(logHistory);
}

void Bluetooth::resetLog() {
  logHistory = "";
}

void Bluetooth::log(String s) {
  logHistory += s + ";" + "\n";
}

void serialEvent() {
  if (Serial.available()) {
    Bluetooth::inputHandler(Serial.readString());
  }
}

void serialEvent2() {
  if (Serial2.available()) {
    Bluetooth::inputHandler(Serial2.readString());
  }
}

void Bluetooth::inputHandler(String input) {
  input.replace("\r\n", "");
  if (input == "init") {
    log(NEUTRAL + "Initializing jeff...");
  } else if (input == "restart") {
    log(NEUTRAL + "Restarting flight controller");
  } else if (input == "startData") {
    log(NEUTRAL + "Starting data printing");
    printData = true;
  } else if (input == "stopData") {
    log(NEUTRAL + "Stopping data printing");
    printData = false;
  } else if (input == "print") {
    printLog();
  }
}
