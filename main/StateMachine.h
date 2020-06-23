#pragma once

#include "Defines.h"

#include "State.h"
#include "States.h"

class StateMachine {
public:
  using StateID = unsigned int;
	StateMachine() {
		// add state pointers to state map
		_states[STATE_STANDBY] = new State(&StandbyState::onEntry, &StandbyState::update, &StandbyState::onExit);
    _states[STATE_POWERED_ASCENT] = new State(&PoweredAscentState::onEntry, &PoweredAscentState::update, &PoweredAscentState::onExit);
		
		// initialize what state the program starts on
    _currentState = STATE_STANDBY;
		_states[_currentState]->onEntry();
	}
	void update() {
		_states[_currentState]->update(this);
	}
	void changeState(StateID state) {
		_states[_currentState]->onExit();
		_currentState = state;
		_states[_currentState]->onEntry();
	}
  StateID getState() {
    return _currentState;
  }
private:
	State* _states[STATE_LANDED + 1];
	StateID _currentState;
};
