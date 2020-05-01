#pragma once
#include <stdlib.h>

class ErrorController {
  private:
    
  public:
    void init(float threshold);
    float getAverage(float data[]);
    bool getAverage(bool data[]);
};
