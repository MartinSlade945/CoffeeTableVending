// SysControl.h
#ifndef SysControl_h
#define SysControl_h
#include <Arduino.h>
#include "Pinouts.h"
#include "SodaDispenser.h"
#include "Lift.h"
#include "CandyDispenser.h"
#include "Button.h"

class SysControl {
  private:
    int sodaFallTime = 1000;

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
    SodaDispenser leftSodaDispenser;
    SodaDispenser rightSodaDispenser;
    CandyDispenser candyDispenser1;
    CandyDispenser candyDispenser2;
    CandyDispenser candyDispenser3;  
    Button soda1Button;  
    Button soda2Button;
    Button candy1Button;
    Button candy2Button;
    Button candy3Button;

    SysControl();
    void init();
    void update();
    void readButtons();
    void StartDispensing();
    void HandleDispensing();
    void runStateModel();
};

#endif // SysControl.h