#include "Serials.h"

void Serials::begin() {
  Serial.begin(SERIAL_BAUD); // USB
  while (!Serial);
  Serial2.begin(SERIAL_BAUD); // BT
  while (!Serial2);
  Serial3.begin(SERIAL_BAUD); // GPS
  while (!Serial3);
}

void Serials::print(String string, bool newline) { // print to all serials
  if (newline) {
    Serial.println(string);
    Serial2.println(string);
    Serial3.println(string);
  } else {
    Serial.print(string);
    Serial2.print(string);
    Serial3.print(string);
  }
}

void handleInput(Stream* serial) {
  String input = "";
  while (serial->available()) {
    char c = (char)(serial->read()); // read byte
    if (c == '\n') { // newline character is detected
      Data::setCommand(input.replace("\r", "")); // formatted commands are sent to Data class
    }
    input += c; // add byte to input
  }
}

// Serial event handlers
void serialEvent() {
  handleInput(&Serial);
}
void serialEvent2() {
  handleInput(&Serial2);
}
void serialEvent3() {
  handleInput(&Serial3);
}

void Serials::flush() {
  Serial.flush();
  Serial2.flush();
  Serial3.flush();
}

void Serials::end() {
  Serial.end();
  Serial2.end();
  Serial3.end();
}
