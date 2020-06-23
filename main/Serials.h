#pragma once

class Serials {
  public:
    // TODO: Template begin() to allow as many serials to initialize as necessary
    static void begin(int baud) {
      Serial.begin(baud); // USB
      while (!Serial);
      //Serial2.begin(baud); // Bluetooth
      //while (!Serial2);
      //Serial3.begin(baud); // GPS
      //while (!Serial3);
    }
    static void print(const char* output) {
      Serial.print(output);
      //Serial2.print(output);
      //Serial3.print(output);
    }
    static void println(const char* output) {
      Serial.println(output);
      //Serial2.println(output);
      //Serial3.println(output);
    }
    static void flush() {
      Serial.flush();
      Serial2.flush();
      Serial3.flush();
    }
    static void end() {
      Serial.end();
      Serial2.end();
      Serial3.end();
    }
};
