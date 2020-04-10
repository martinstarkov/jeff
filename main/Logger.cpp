/*#include "Logger.h"

void Logger::init() {
  if(!SD.begin(chipSelect)) {
    Serial.println("Could not initialize SD card");
  }

  //Read last flight number and increment by one to get current flight number
  flightNumber = EEPROM.read(FLIGHT_NUMBER_ADDRESS) + 1;
  EEPROM.update(FLIGHT_NUMBER_ADDRESS, flightNumber);
  
  // Create new Log File
  char* fileName = flightNumber+".txt";
  logFile = SD.open(fileName,FILE_WRITE);

  // Check if Log File was created successfully
  if(!logFile) {
    Serial.println("Could not create log file");
  }

  Serial.println("Initialized SD card");
}

Logger::~Logger() {
  // Close Log File when Logger is deconstructed
  logFile.close();
  Serial.println("Log file closed");
}

void Logger::log(String type, int data) {
  if(logFile) {
    // Format timestamp type:data
    String log_data = millis()+" "+type+":"+data;
    logFile.println(log_data);
    Serial.println(log_data);
  }
}*/
