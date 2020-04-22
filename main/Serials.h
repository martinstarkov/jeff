#pragma once
#include <Wire.h>
#include "Defines.h"
#include "Data.h"

#define SERIAL_BAUD 115200

class Serials {
  public:
    static void begin();
    static void print(String string, bool newline=true);
    static void inputHandler(String input); // static because it relies on arduino's serial event handlers which are static methods
    static void flush();
    static void end();
};
