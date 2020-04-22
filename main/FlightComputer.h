#pragma once
#include "DataService.h"
#include "StateMachine.h"

class FlightComputer {
  private:
    static FlightComputer* instance;
    FlightComputer();
    DataService* ds;
    //StateMachine* sm;
  public:
    static FlightComputer* getInstance();
    void update();
};
