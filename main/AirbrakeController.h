#pragma once
#include <PWMServo.h>
#include "PID_v1.h"
#include "Defines.h"

class AirbrakeController {
  private:
    PID* pid;
    // Input
    double altitude = 0;
    double* inputData = &altitude;
    double* referenceAltitude;
    // Output
    PWMServo* servo;
    double* servoData;
    float rotateAngle;
    float getServoOutput();
  public:
    AirbrakeController();
    void controlLoop(float altitude);
    void deployAirbrakes();
};
