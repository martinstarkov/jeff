#pragma once
#include <ArduinoJson.h>
#include "Defines.h"

enum JsonTypes {
  PRESSURE,
  TEMPERATURE,
  ALTITUDE,
  ORIENTATION
};


class Data {
  private:
    static Data* instance;
    static DynamicJsonDocument* data;
    static DynamicJsonDocument* statuses;
    static DynamicJsonDocument* debug;
    static void combine(JsonDocument* dst, const JsonDocument* src) {
      for (auto p : src->as<JsonObject>()) {
          (*dst)[p.key()] = p.value();
      }
    }
    Data();
  public:
    static Data* getInstance();
    static void add();
    static void print(Stream& serial);
    static void clear(String type);
    static void populate(String type);
};
