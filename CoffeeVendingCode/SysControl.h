// SysControl.h
#ifndef SysControl_h
#define SysControl_h
#include <Arduino.h>
#include "Pinouts.h"
#include "SodaDispenser.h"
#include "Lift.h"
#include "CandyDispenser.h"

class SysControl {
  private:
    bool sodaButton1State  = false;
    bool sodaButton2State  = false;
    bool candyButton1State = false;
    bool candyButton2State = false;
    bool candyButton3State = false;

    typedef enum DispenseOption : byte {
      NONE,
      SODA1,
      SODA2,
      CANDY1,
      CANDY2,
      CANDY3,
    } DispenseOption;
    DispenseOption dispenseOption = NONE;

    typedef enum ActionState : byte {
      WAITING_INPUT,
      START_LIFT_FALLING,
      LIFT_FALLING,
      START_DISPENSING,
      DISPENSING,
      START_LIFT_RISING,
      LIFT_RISING
    } ActionState;
    ActionState actionState = WAITING_INPUT;

  public:
    Lift lift;
    SodaDispenser leftCanDispenser;
    SodaDispenser rightCanDispenser;
    CandyDispenser candyDispenser1;
    CandyDispenser candyDispenser2;
    CandyDispenser candyDispenser3;    
 
    SysControl();
    void init();
    void update();
    void readButtons();
};

#endif // SysControl.h