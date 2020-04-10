/*#pragma once
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
