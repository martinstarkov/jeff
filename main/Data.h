#pragma once
#include <ArduinoJson.h>
#include "Vector3D.h"
#include "Defines.h"

class Data {
  private:
    static Data* instance;
    static DynamicJsonDocument document;
    Data();
  public:
    static Data* getInstance();
    static String getString(bool pretty=false);
    static JsonVariant get(String format, String type="") {
      if (type == "") { // debug
        return document[format].as<JsonVariant>();
      }
      return document[format][type]; // everything else (ints, floats, bools
    }
    static void set(String format, String type, int value);
    static void set(String format, String type, float value);
    static void set(String format, String type, double value);
    static void set(String format, String type, float values[], int length);
    static void set(String format, String type, bool value);
    static void set(String format, String type, Vector3D value);
    static void set(String format, String value);
    static void clear(String format);
    static void clearData();
};
