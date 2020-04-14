#pragma once
#include "Data.h"
#include "Defines.h"

class CommunicationController {
  private:
    void send();
    void print(String string, bool newline=true);
  public:
    CommunicationController(int baud);
    void update();
};
