#pragma once
#include <Wire.h>

#define NEUTRAL String("NEUTRAL: ")
#define FAILURE String("FAILURE: ")
#define SUCCESS String("SUCCESS: ")
#define WARNING String("WARNING: ")

class Bluetooth {
    private:
      static Bluetooth* bt;
    public:
      static void init(int baud);
      static void print(String text, bool newline=true);
      static void inputHandler(String input);
};
