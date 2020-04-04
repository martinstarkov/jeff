#include "Bluetooth.h"

Bluetooth* Bluetooth::bt;
bool Bluetooth::printData = false;

Bluetooth* Bluetooth::init(int baud) {
  if (bt == 0) {
    bt = new Bluetooth();
    printData = false;
    Serial2.begin(baud);
    while (!Serial2) {
      print(NEUTRAL + "Initializing Bluetooth Serial...");
    }
    print(SUCCESS + "Bluetooth Serial initialized");
  }
  return bt;
}

void Bluetooth::print(String text, bool newline) {
  if (newline) {
    Serial2.println(text);
  } else {
    Serial2.print(text);
  }
}

void serialEvent2() {
  if (Serial2.available()) {
    Bluetooth::inputHandler(Serial2.readString());
  }
}

void Bluetooth::inputHandler(String input) {
  String lc = input.toLowerCase();
  if (lc == "i") {
    Bluetooth::print("Initializing JEFF");
  } else if (lc == "d") { // toggle data printing
    if (!printData) {
      Bluetooth::print("Beginning data printing");
      printData = true;
    }
  }
}
