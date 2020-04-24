#pragma once
#include "Logger.h"
#include "Serials.h"
#include "Data.h"
#include "Defines.h"

class CommunicationController {
  private:
    Logger* sd;
    bool bmp = false;
    bool bno = false;
    bool data = true;
    bool time = false;
    void restartTeensy();
    void processInput(String input);
  public:
    CommunicationController();
    void update();
};
