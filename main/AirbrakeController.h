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
      double* inputData;
      double* referenceAltitude;
      // Output
      PWMServo* servo;
      double* servoData;
      float rotateAngle;
      float getServoOutput();
    public:
      AirbrakeController();
      void loop(float altitude);
      void deployFlaps();
      
};
