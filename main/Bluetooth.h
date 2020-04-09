#pragma once
#include <Wire.h>
#include "Defines.h"

class Bluetooth {
    private:
      static Bluetooth* bt;
      static String history;
    public:
      static void init(int baud);
      static void end();
      static void inputHandler(String input);
      static String getLog();
      static void log(String s);
      static void resetLog();
      static bool printData;
      static void print(String text, bool newline=true);
};
