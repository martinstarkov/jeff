#include "CommunicationController.h"

CommunicationController::CommunicationController(int baud) {
  // serial initialization
  // USB
  Serial.begin(baud);
  while (!Serial);
  // Bluetooth
  Serial2.begin(baud);
  while (!Serial2);
  // GPS
  Serial3.begin(baud);
  while (!Serial3);
  Data::getInstance();
  debug(SUCCESS + "Initialized serials (USB, Bluetooth, GPS)");
}

void CommunicationController::print(String string, bool newline) {
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

void CommunicationController::send() {
  print(Data::getString(true)); // change to false if you wish to print compacated version of json / true = prettified
  Data::clearData();
}

void CommunicationController::update() {
  send();
}

/*
void Bluetooth::end() {
  Serial.end();
  Serial2.end();
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
  // remember to clear debug after finished with task
  // Data::clear(DEBUG);
}
*/
/*
#pragma once
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>

#define FLIGHT_NUMBER_ADDRESS 0

class Logger {
  private:
    const int chipSelect = 4;
    int flightNumber;
    File logFile;
  public:
    ~Logger();
    void init();
    void log(String type, int data);
};*/

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
