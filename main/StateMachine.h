/*#pragma once
#include "Defines.h"

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
