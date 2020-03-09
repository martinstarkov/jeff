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
    
      static int baud;
      static void init(int baudRate);
      static void reinit(int baudRate);
      static void print(String text, bool newline=true);
      static String read();
      
};
