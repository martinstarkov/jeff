#include "Serials.h"

void Serials::begin() {
  Serial.begin(SERIAL_BAUD); // USB
  while (!Serial);
  Serial2.begin(SERIAL_BAUD); // Bluetooth
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
      Data::setCommand(input.replace("\r", "")); // commands are sent to Data class
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

//#include <SD.h>
//#include <SPI.h>
//#include <EEPROM.h>
//    void initSD();
//    void log(String string, bool newline=true);
//    File logFile;
//    void stopSDCard();
//    int flightNumber;
//void Serials::initSD() { // SD card initialization
//  // Read last flight number and increment by one to get current flight number
//  flightNumber = EEPROM.read(FLIGHT_NUMBER_ADDRESS) + 1;
//  EEPROM.update(FLIGHT_NUMBER_ADDRESS, flightNumber);
//  // Initialize SD card on given chip select
//  if (!SD.begin(SD_CHIP_SELECT)) {
//    debug(WARNING + "Could not initialize SD card");
//    return;
//  }
//  // Create new log file
//  const char* fileName = flightNumber + SD_FILE_FORMAT;
//  logFile = SD.open(fileName, FILE_WRITE);
//  // Check if log file was created successfully
//  if(!logFile) {
//    debug(WARNING + "Could not write to SD card file '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
//    return;
//  }
//  debug(SUCCESS + "SD card initialized, writing to '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
//}
//void CommunicationController::log(String string, bool newline) {
//  if(logFile) {
//    if (newline) {
//      logFile.println(string);
//    } else {
//      logFile.print(string);
//    }
//  }
//}
//void CommunicationController::stopSDCard() {
//  // Close log file shortly after landing
//  logFile.close();
//  debug(SUCCESS + "Closed SD log file");
//}
////log(Data::getString(false));
