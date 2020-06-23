#pragma once

#include "common.h"

class StateMachine;

struct StandbyState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};

struct PoweredAscentState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};
