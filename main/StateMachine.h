#pragma once
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "CommunicationController.h"
#include "Data.h"
#include "Serials.h"
#include "Defines.h"
#include "Vector3D.h"

enum Stage {
  STANDBY,
  POWERED_ASCENT,
  COASTING,
  DROGUE_DESCENT,
  MAIN_DESCENT,
  LANDED
};

class StateMachine {
  private:
    int cycle = 0;
    ParachuteController* pc;
    AirbrakeController* ac;
    CommunicationController* cc;
    Stage currentStage;
    void determineStage();
    bool poweredAscentCheck();
    int liftoffCache[LIFTOFF_LOOP_LENGTH];
    int liftoffCount = 0;
    bool coastingCheck();
    int burnoutCache[BURNOUT_LOOP_LENGTH];
    int burnoutCount = 0;
    bool landingCheck();
  public:
    StateMachine();
    void update();
};
