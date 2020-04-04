#pragma once
#include <Wire.h>
#include "Defines.h"

class Bluetooth {
    private:
      static Bluetooth* bt;
    public:
      static bool printData;
      static Bluetooth* init(int baud);
      static void print(String text, bool newline=true);
      static void inputHandler(String input);
};
