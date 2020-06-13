#pragma once
#include "DataService.h"
#include "StateMachine.h"

class FlightComputer {
  public:
    static FlightComputer* getInstance();
    // static void clean(); // it is important to implement good habits of memory clean up, even if Arduino doesn't have anything past the loop() method
  public:
    void update();
  private:
    static FlightComputer* _instance;
  private:
    FlightComputer();
    ~FlightComputer();
    DataService* _ds;
    StateMachine* _sm;
};
