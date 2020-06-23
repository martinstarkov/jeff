#pragma once

#include "SensorController.h"

class DataController {
  public:
    DataController() {
      _sc = new SensorController();
    }
    void update() {
      _sc->update();
    }
  private:
    SensorController* _sc;
};
