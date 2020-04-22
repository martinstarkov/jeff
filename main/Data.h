#pragma once
#include <Wire.h>
#include "Defines.h"

#define SEPARATE_PROPERTY_CHAR ":"
#define END_PROPERTY_CHAR ";"

class Data {
  private:
    static String data;
    static String command;
  public:
    static void setCommand(String newCommand);
    static String getCommand();
    static String getData();
    static void clearData();
    static String get(String property);
    static void add(String property, String value);
};
