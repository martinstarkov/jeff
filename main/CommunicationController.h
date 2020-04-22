#pragma once
#include "Serials.h"
#include "Data.h"
#include "Defines.h"

class CommunicationController {
  private:
    void inputHandler(String input);
  public:
    CommunicationController() {}
    void update();
};
