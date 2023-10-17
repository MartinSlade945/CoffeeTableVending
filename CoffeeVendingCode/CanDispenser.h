#ifndef CanDispenser_h
#define CanDispenser_h

#include <Arduino.h>

class CanDispenser {
  private:
    unsigned long endTimeMillis = 0; // Stores the time to turn the solenoid off
    const unsigned long solenoidTimeout = 500; // Time Interval solenoid is active in milliseconds
    int solenoidPin = 0; // Stores the digital output pin of the solenoid

  public:
    void init(int digitalOutputPin);
    void dispense();
    void update();
};

#endif