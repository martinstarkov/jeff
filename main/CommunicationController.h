#pragma once
#include "Data.h"
#include "Defines.h"
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>

class CommunicationController {
  private:
    void initSerials();
    void initSD();
    void send();
    void log(String string, bool newline=true);
    static void end(); // static because it is called in restartTeensy()
    int flightNumber;
    File logFile;
  public:
    CommunicationController();
    void update();
    void stopSDCard();
    static void print(String string, bool newline=true);
    static void inputHandler(String input); // static because it relies on arduino's serial event handlers which are static methods
    static void restartTeensy(); // static because it is called in inputHandler()
};
