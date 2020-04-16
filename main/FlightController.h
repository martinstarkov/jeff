#pragma once
#include "DataService.h"
#include "StateMachine.h"

class FlightController {
  private:
    static FlightController* instance;
    static int cycle;
    FlightController();
    DataService* ds;
    StateMachine* sm;
  public:
    static FlightController* getInstance();
    void update();
};
