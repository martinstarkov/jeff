#include "CommunicationController.h"

CommunicationController::CommunicationController() {
  Data::getInstance();
  initSerials();
  initSD();
  debug(SUCCESS + "Communication controller initialized");
}

void CommunicationController::initSerials() { // serial initialization
  // USB
  Serial.begin(SERIAL_BAUD);
  while (!Serial);
  // Bluetooth
  Serial2.begin(SERIAL_BAUD);
  while (!Serial2);
  // GPS
  Serial3.begin(SERIAL_BAUD);
  while (!Serial3);
  debug(SUCCESS + "Serials (USB, Bluetooth, GPS) initialized");
}

void CommunicationController::initSD() { // SD card initialization
  // Read last flight number and increment by one to get current flight number
  flightNumber = EEPROM.read(FLIGHT_NUMBER_ADDRESS) + 1;
  EEPROM.update(FLIGHT_NUMBER_ADDRESS, flightNumber);
  // Initialize SD card on given chip select
  if (!SD.begin(SD_CHIP_SELECT)) {
    debug(WARNING + "Could not initialize SD card");
    return;
  }
  // Create new log file
  const char* fileName = flightNumber + SD_FILE_FORMAT;
  logFile = SD.open(fileName, FILE_WRITE);
  // Check if log file was created successfully
  if(!logFile) {
    debug(WARNING + "Could not write to SD card file '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
    return;
  }
  debug(SUCCESS + "SD card initialized, writing to '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
}

void CommunicationController::print(String string, bool newline) { // print to all serials
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

void CommunicationController::log(String string, bool newline) {
  if(logFile) {
    if (newline) {
      logFile.println(string);
    } else {
      logFile.print(string);
    }
  }
}

void CommunicationController::send() {
  Data::set(STATUS, TRANSMISSION_TIME, double(millis() / 1000.0000L)); // add time since start signature to data packet
  print(Data::getString(true)); 
  log(Data::getString(false));
  Data::clearData(); // clear RAW, PROCESSED, FILTERED data after each cycle
}

void CommunicationController::update() {
  send();
}

// Serial event handlers
void serialEvent() {
  if (Serial.available()) {
    CommunicationController::inputHandler(Serial.readString());
  }
}
void serialEvent2() {
  if (Serial2.available()) {
    CommunicationController::inputHandler(Serial2.readString());
  }
}
void serialEvent3() {
  if (Serial3.available()) {
    CommunicationController::inputHandler(Serial3.readString());
  }
}

void CommunicationController::stopSDCard() {
  // Close log file shortly after landing
  logFile.close();
  debug(SUCCESS + "Closed SD log file");
}

void CommunicationController::end() {
  Serial.end();
  Serial2.end();
  Serial3.end();
}

void CommunicationController::restartTeensy() { // Restart teensy programmatically
  // Make sure (at least how it was implemented online, need to test this) to end serials before this call
  end();
  SCB_AIRCR = 0x05FA0004; // write value for restart
}

void CommunicationController::inputHandler(String input) {
  input.replace("\r\n", ""); // remove newline characters
  if (input == "init") {
    
  } else if (input == "restart") {
    CommunicationController::restartTeensy();
  }
  // remember to clear debug after finished with task
  // Data::clear(DEBUG);
}
