#include "States.h"
#include "StateMachine.h"
#include "DataInterface.h"

void StandbyState::update(StateMachine* stateMachine) {
  if (DataInterface::getInstance()->getProcessedData().netAcceleration.x > 5.0f) {
    stateMachine->changeState(STATE_POWERED_ASCENT);
  }
}

void PoweredAscentState::update(StateMachine* stateMachine) {
  stateMachine->changeState(STATE_COASTING);
}

void CoastingState::update(StateMachine* stateMachine) {
  stateMachine->changeState(STATE_DROGUE_DESCENT);
}

void DrogueDescentState::update(StateMachine* stateMachine) {
  stateMachine->changeState(STATE_MAIN_DESCENT);
}

void MainDescentState::update(StateMachine* stateMachine) {
  stateMachine->changeState(STATE_LANDED);
}

void LandedState::update(StateMachine* stateMachine) {
  stateMachine->changeState(STATE_STANDBY);
}
