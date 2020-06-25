#pragma once

#include "common.h"

class StateMachine;

struct StandbyState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};

struct PoweredAscentState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};

struct CoastingState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};

struct DrogueDescentState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};

struct MainDescentState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};

struct LandedState {
    static void onEntry() {}
    static void update(StateMachine* sm);
    static void onExit() {}
};
