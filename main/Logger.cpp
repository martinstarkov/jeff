#include "Logger.h"

Logger::Logger() {
  // Read last flight number and increment by one to get current flight number
  flightNumber = EEPROM.read(FLIGHT_NUMBER_ADDRESS) + 1;
  EEPROM.update(FLIGHT_NUMBER_ADDRESS, flightNumber);
  initSD();
}

void Logger::initSD() {
  // Initialize SD card reader on given chip select
  if (!SD.begin(SD_CHIP_SELECT)) {
    Data::add(DEBUG, WARNING + "Could not initialize SD card");
    return;
  }
  // Create new log file
  const char* fileName = flightNumber + SD_FILE_FORMAT;
  logFile = SD.open(fileName, FILE_WRITE);
  // Check if log file was created successfully
  if(!logFile) {
    Data::add(DEBUG, FAILURE + "Could not write to SD card file '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
    return;
  }
  Data::add(DEBUG, SUCCESS + "SD card initialized, writing to '" + String(flightNumber) + String(SD_FILE_FORMAT) + "'");
}

void Logger::log(String string, bool newline) {
  if(logFile) {
    if (newline) {
      logFile.println(string);
    } else {
      logFile.print(string);
    }
  }
}
void Logger::close() {
  // Close log file shortly after landing
  logFile.close();
  Data::add(DEBUG, NEUTRAL + "Closed SD log file");
}
