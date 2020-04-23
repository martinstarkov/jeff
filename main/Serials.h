#pragma once
#include <Wire.h>
#include "Defines.h"
#include "Data.h"

class Serials {
  public:
    static void begin();
    static void print(String string, bool newline=true);
    static void flush();
    static void end();
};
