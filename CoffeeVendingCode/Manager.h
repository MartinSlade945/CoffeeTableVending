// Manager.h
#ifndef Manager_h
#define Manager_h
#include <Arduino.h>

#include "global.h"
#include "CanDispenser.h"
//#include "LiftAxis.h"
//#include "CandyVender.h"

class Manager {
  private:
    unsigned long previousPollMillis = 0; // Stores the previous millisecond count
    const unsigned long pollingInterval = 5; // Polling Interval in milliseconds

  public:
    //LiftAxis lift;
    CanDispenser leftCanDispenser;
    CanDispenser rightCanDispenser;
    //CandyVender candyVender1;
    //CandyVender candyVender2;
    //CandyVender candyVender3;    
 
    Manager();
    void init();
    void update();
};

#endif // Manager.h