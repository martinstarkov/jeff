#pragma once

#include "common.h"

#include "DataController.h"
#include "StateMachine.h"

class FlightComputer {
  public:
    static FlightComputer* getInstance() {
      static FlightComputer* instance = nullptr;
      if (!instance) {
        instance = new FlightComputer();
      }
      return instance;
    }
    static void clean() {
      FlightComputer* fc = getInstance();
      delete fc;
      fc = nullptr;
    }
    void update() {
      //_dc->update();
      _sm->update();
    }
    StateMachine* _sm;
  private:
    FlightComputer() {
      _dc = new DataController();
      _sm = new StateMachine();
    }
    ~FlightComputer() {
      delete _dc;
      _dc = nullptr;
      delete _sm;
      _sm = nullptr;
    }
    DataController* _dc;
};
