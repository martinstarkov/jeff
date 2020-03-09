#include "Bluetooth.h"

Bluetooth* Bluetooth::bt;
int Bluetooth::baud;

void Bluetooth::init(int baudRate) {
  if (bt == 0) {
    
    bt = new Bluetooth();
    baud = baudRate;
    Serial2.begin(baud);
    
    while (!Serial2) {
      print(NEUTRAL + "Initializing Bluetooth Serial...");
    }
    
    print(SUCCESS + "Bluetooth Serial initialized");
  }
}

void serialEvent2() {
  String userInput = Bluetooth::read().trim().toLowerCase();
  
  if (userInput == "jonah sucks") {
    Bluetooth::print("Yes he does");
  }
}

String Bluetooth::read() {
  if (Serial2.available() > 0) {
    return Serial2.readString();
  }
  return "";
}

void Bluetooth::print(String text, bool newline) {
  if (newline) {
    Serial2.println(text);
  } else {
    Serial2.print(text);
  }
}
