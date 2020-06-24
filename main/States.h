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

struct CoastingState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};

struct DrogueDescentState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};

struct MainDescentState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};

struct LandedState {
    // TODO add array buffer
    static void onEntry();
    static void update(StateMachine* stateMachine);
    static void onExit();
};