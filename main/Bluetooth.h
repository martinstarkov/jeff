#pragma once
#include <SoftwareSerial.h>
        
class Bluetooth {
    private:
      static SoftwareSerial* ss;
    public:
      static void init(int RX, int TX, int baud);
      static void print(String text, bool newline=true);
};
