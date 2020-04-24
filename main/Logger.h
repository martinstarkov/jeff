#pragma once
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>
#include "Data.h"
#include "Defines.h"

#define SD_CHIP_SELECT 4 // SD card chip select
#define FLIGHT_NUMBER_ADDRESS 0 // initial counter value for SD card file names (using EEPROM)
#define SD_FILE_FORMAT "_flight_log.txt"

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
