#pragma once
#include <Wire.h>
#include "Defines.h"

#define SEPARATE_CHAR String(":")
#define END_CHAR String(";")

class Data {
  private:
  public:
    static String command;
    static String debug;
    static String raw;
    static String processed;
    static String filtered;
    static String status;
    static String combined;
    static void set(String format, String type, String value);
    static String get(String format, String type);
    static void add(String type, String value);
    static String& getString(String format);
    static void clearData();
};
