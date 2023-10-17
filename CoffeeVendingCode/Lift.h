#ifndef Lift_h
#define Lift_h
#include <Arduino.h>
//#include "./libraries/AccelStepper/src/AccelStepper.h"
#include <AccelStepper.h>

class Lift {
  private:
    int enablePin = 0; //Stores the enable pin
    int stepPin = 0; //Stores the step pin
    int directionPin = 0; //Stores the direction pin
    int homingPin = 0; //Stores the homing pin

    const int stepsPerRev = 200; //number of steps per rev
    const int MMPerRev = 20*2; //20 tooth gear, 2mm Pitch
    const float stepsPerMM = stepsPerRev / MMPerRev; 

    const int upPositionMM = 310; //Travel in MM
    const float upSpeedMM = 40; //up speed in MM/s
    const float upAccelMM = 80; //up Acceleration in MM/s/s
    const float downSpeedMM = 40; //down speed in MM/s
    const float downAccelMM = 80; //down Acceleration in MM/s/s 

    const int upSpeedSteps   = floor(upSpeedMM * stepsPerMM);
    const int downSpeedSteps = floor(downSpeedMM * stepsPerMM);
    const int upAccelSteps   = floor(upAccelMM *stepsPerMM);
    const int downAccelSteps = floor(downAccelMM *stepsPerMM);

    bool homingPinState = false;
    AccelStepper* liftMotor;

    typedef enum LiftState : byte {
      LIFT_UNKNOWN,
      LIFT_LOWERING,
      LIFT_AT_BOTTOM,
      LIFT_RISING,
      LIFT_AT_TOP
    } LiftState;
    LiftState liftState = LIFT_UNKNOWN;

    void stopMotor();

  public:
    void init(int Enable, int Direction, int Step, int Homing);
    void up();
    void down();
    void update();
    bool busy();

};

#endif