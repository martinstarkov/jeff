#pragma once
#include <Wire.h>

#define SEPARATE_PROPERTY_CHAR ":"
#define END_PROPERTY_CHAR ";"

enum Stage {
  STANDBY = 0,
  POWERED_ASCENT = 1,
  COASTING = 2,
  DROGUE_DESCENT = 3,
  MAIN_DESCENT = 4,
  LANDED = 5
};

class Data {
  private:
    static String data;
    static Stage stage;
    static String command;
    static int cycle;
  public:
    static int getCycle();
    static void incrementCycle();
    static void setCommand(String newCommand);
    static String getCommand();
    static void setStage(Stage newStage);
    static Stage getStage();
    static String getData();
    static void clearData();
    static String get(String property);
    static void add(String property, String value);
};
