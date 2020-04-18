#include "StateMachine.h"

StateMachine::StateMachine() {
  cc = new CommunicationController();
  pc = new ParachuteController();
  ac = new AirbrakeController();
  // initial state set to standby
  currentStage = STANDBY;
  Data::set(STATUS, STAGE, STAGE_STANDBY);
  debug(SUCCESS + "State machine initialized");
}

void StateMachine::update() {
  
  determineStage();
  
  // Send everything via serials at the end of the cycle
  cc->update();
}

void StateMachine::determineStage() {
  switch (currentStage) { // switch statement because stage transition can only occur incrementally
    case STANDBY:
      // check if criteria for powered ascent are met
      if (poweredAscentCheck()) {
        currentStage = POWERED_ASCENT;
        Data::set(STATUS, STAGE, STAGE_POWERED_ASCENT);
      }
      break;
    case POWERED_ASCENT:
      // check if criteria for coasting are met
      if (coastingCheck()) {
        currentStage = COASTING;
        Data::set(STATUS, STAGE, STAGE_COASTING);
      }
      break;
    case COASTING:
      // check if criteria for drogue chute deploy are met
      if (pc->drogueDescentCheck()) {
        currentStage = DROGUE_DESCENT;
        Data::set(STATUS, STAGE, STAGE_DROGUE_DESCENT);
      }
      break;
    case DROGUE_DESCENT:
      // check if criteria for main chute deploy are met
      if (pc->mainDescentCheck()) {
        currentStage = MAIN_DESCENT;
        Data::set(STATUS, STAGE, STAGE_MAIN_DESCENT);
      }
      break;
    case MAIN_DESCENT:
      // check if criteria for sufficient still time (i.e. landing) are met
      if (landingCheck()) {
        currentStage = LANDED;
        Data::set(STATUS, STAGE, STAGE_LANDED);
      }
      break;
    case LANDED:
      // turn off data logging after X seconds
      break;
    default:
      // error
      break;
  }
}

bool StateMachine::poweredAscentCheck() {
  return false;
}

bool StateMachine::coastingCheck() {
  return false;
}

bool StateMachine::landingCheck() {
  return false;
}

/*
//Initial State
StateMachine::initStateMachine(){
    State currentState = State::STANDBY;

    for(int i = 0; i<LIFTOFF_LOOP_LENGTH; i++){
        liftoffCache[i] = 0;
    } 
    for(int i = 0; i<BURNOUT_LOOP_LENGTH; i++){
        burnoutCache[i] = 0;
    }
    for(int i = 0; i<FREEFALL_LOOP_LENGTH; i++){
        freefallCache[i] = 0;
    }

    Bluetooth::print("STATE MACHINE INITIALIZED: ON STANDBY");
}

StateMachine::runStateMachine(){
    switch (currentState){
        case State::STANDBY:
            //on standby, do nothing
            //check for state transition
            int liftoffCount = 0;
            if(DataService::getProcessedData->netAcceleration > LIFTOFF_THRESHOLD){
                liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] = 1;
            }
            else{
                liftoffCache[cycle % LIFTOFF_LOOP_LENGTH] = 0;
            }

            for(int i = 0; i<LIFTOFF_LOOP_LENGTH; i++){
                if(liftoffCache[i] == 1){
                    liftoffCount++;
                }
            }

            if(liftoffCount == LIFTOFF_LOOP_LENGTH){
                // liftoffStatus = true;
                currentState = State::BOOSTING;
            }
            break;
        case State::BOOSTING:
            //start logging data

            //check for burnout
            int burnoutCount = 0;
            if(DataService::getProcessedData->netAcceleration < BURNOUT_THRESHOLD){
                burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 1;
            }
            else{
                burnoutCache[cycle % BURNOUT_LOOP_LENGTH] = 0;
            }

            for(int i = 0; i<BURNOUT_LOOP_LENGTH; i++){
                if(burnoutCache[i] == 1){
                    burnoutCount++;
                }
            }

            if(burnoutCount == BURNOUT_LOOP_LENGTH){
                // burnoutStatus = true;
                currentState = State::COASTING;
            }
            break;
        case State::COASTING:
            //operate airbrakes + log data

            //check state transition
            if(ParachuteController::drogueDeploymentCheck){
                currentState = State::FALLING_DROGUE;
            }
            break;
        case State::FALLING_DROGUE:
            //deploy drogue parachute + log data

            //check state transition
            if(ParachuteController::mainChuteDeploymentCheck){
                currentState = State::FALLING_MAIN;
            }
            break;
        case State::FALLING_MAIN:
            //deploy main parachute + log data

            //check state transition
            int freefallCount = 0;
            if(DataService::getProcessedData->netAcceleration < FREEFALL_THRESHOLD){
                freefallCache[cycle % FREEFALL_THRESHOLD] = 1;
            }
            else{
                freefallCache[cycle % FREEFALL_THRESHOLD] = 0;
            }

            for(int i = 0; i<FREEFALL_LOOP_LENGTH; i++){
                if(freefallCache[i] == 1){
                    freefallCount++;
                }
            }

            if(freefallCount == FREEFALL_LOOP_LENGTH){
                // freefallStatus = true;
                currentState = State::LANDED;
            }            

            break;
        case State::LANDED:
            //landed, do nothing
            break;
        default:
            Bluetooth::print("STATE MACHINE ERROR: Invalid State");
    }
}*/
