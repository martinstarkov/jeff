#pragma once
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "CommunicationController.h"
#include "Defines.h"

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
    ParachuteController* pc;
    AirbrakeController* ac;
    CommunicationController* cc;
    Stage currentStage;
    void determineStage();
    bool poweredAscentCheck();
    bool coastingCheck();
    bool landingCheck();
  public:
    StateMachine();
    void update();
};

/*

class StateMachine{
    private:
        State currentState;
        int liftoffCache[LIFTOFF_LOOP_LENGTH];
        // bool liftoffStatus = false;
        int burnoutCache[BURNOUT_LOOP_LENGTH];
        // bool burnoutStatus = false;
        int freefallCache[FREEFALL_LOOP_LENGTH];
        // bool freefallStatus = false;
    public:
        initStateMachine();
        runStateMachine();
};*/
