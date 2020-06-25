#pragma once

#include "common.h"
#include "ParachuteController.h"
#include "AirbrakeController.h"

class StateMachine;

struct State {
    State(void (*entryFunction)(), void (*updateFunction)(StateMachine*), void (*exitFunction)()) : onEntry(entryFunction), update(updateFunction), onExit(exitFunction) {}
    void (*onEntry)();
    void (*update)(StateMachine*);
    void (*onExit)();
};
