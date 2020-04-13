#pragma once
#include "ParachuteController.h"
#include "AirbrakeController.h"
#include "CommunicationController.h"
#include "Defines.h"

class StateMachine {
  private:
    ParachuteController* pc;
    AirbrakeController* ac;
    CommunicationController* cc;
  public:
    StateMachine();
    void update();
};

/*
enum class State{
    STANDBY,
    BOOSTING,
    COASTING,
    FALLING_DROGUE,
    FALLING_MAIN,
    LANDED
};

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
