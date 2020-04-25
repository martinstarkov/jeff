#pragma once
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>
#include "Data.h"
#include "Defines.h"

#define FLIGHT_NUMBER_ADDRESS 0 // initial counter value for SD card file names (using EEPROM)

class Logger {
  private:
    void initSD();
    File logFile;
    int flightNumber;
  public:
    Logger();
    void log(String string, bool newline=true);
    void close();
};
