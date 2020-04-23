#pragma once
#include "Serials.h"
#include "Data.h"
#include "Defines.h"

class CommunicationController {
  private:
    bool bmp = false;
    bool bno = false;
    void processInput(String input);
  public:
    CommunicationController() {}
    void update();
};
