#pragma once
#include "Bluetooth.h"
#include "Data.h"
#include "Defines.h"
#include "PID_v1.h"
#include <PWMServo.h>

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
      void deployFlaps();
      
};
