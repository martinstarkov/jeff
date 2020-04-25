#pragma once
#include <Wire.h>

#define SEPARATE_PROPERTY_CHAR ":"
#define END_PROPERTY_CHAR ";"

enum Stage {
  STANDBY,
  POWERED_ASCENT,
  COASTING,
  DROGUE_DESCENT,
  MAIN_DESCENT,
  LANDED
};

class Data {
  private:
    static String data;
    static Stage stage;
    static String command;
  public:
    static void setCommand(String newCommand);
    static String getCommand();
    static void setStage(Stage newStage);
    static Stage getStage();
    static String getData();
    static void clearData();
    static String get(String property);
    static void add(String property, String value);
};
