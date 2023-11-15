#ifndef Button_h
#define Button_h
#include <Arduino.h>

class Button {
  private:
    unsigned int buttonPin;
    bool buttonState;
    bool lastButtonState;
    unsigned long endTimeMillis;

    const unsigned long  debounceTime = 100; //time in MS button has to be pressed for
    
  public:
    void init(unsigned int setButtonPin);
    bool readButton();
    void update();
};

#endif

//Change to Button single instance