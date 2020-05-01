#pragma once
#include <stdlib.h>

class ErrorController {
  private:
    
  public:
    void init(float threshold);
    // replace averages with template average
    float getAverage(float data[]);
    bool getAverage(bool data[]);
};
