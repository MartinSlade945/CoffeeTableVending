#include "Button.h"

void Button::init(unsigned int setButtonPin) {
  buttonPin = setButtonPin;
  pinMode(buttonPin,INPUT); 
}

bool Button::readButton() {
  return buttonState;
}

void Button::update() {
  unsigned long nowTime = millis(); //get current time
  bool readButton = digitalRead(buttonPin); //read button 
  if (buttonState != readButton) { //if change of state
    if (lastButtonState != readButton) { //if timer is not set
      endTimeMillis = nowTime + debounceTime;
    }
    if (nowTime > endTimeMillis) { //Check if debounce timer is up 
      buttonState = readButton;
    }
  }
  lastButtonState = readButton;
}