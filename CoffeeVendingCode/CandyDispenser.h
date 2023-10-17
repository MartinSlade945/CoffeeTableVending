#ifndef CandyDispenser_h
#define CandyDispenser_h
#include <Arduino.h>
#include <AccelStepper.h>

class CandyDispenser {
  private:
    int enablePin = 0; //Stores the enable pin
    int stepPin = 0; //Stores the step pin
    int directionPin = 0; //Stores the direction pin

    const int stepsPerRotation = 200; //Number of steps to rotate 1
    const int motorSpeed = 1 * stepsPerRotation;
    const int motorAccel = 1 * stepsPerRotation;

    AccelStepper* coilMotor;

  public:
    void init(int Enable, int Direction, int Step);
    void dispense();
    void update();
    bool busy();
};

#endif