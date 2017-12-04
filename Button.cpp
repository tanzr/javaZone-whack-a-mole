#include "Button.h"

bool prevLedState;
bool currLedState;
bool nextLedState;
unsigned long currTime = 0;
Bounce debouncer;
uint8_t thisButtonPin;
uint8_t thisLedPin;

Button::Button() {
  
}

Button::Button(int setOnForTime, uint8_t buttonPin, uint8_t ledPin) {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  thisButtonPin = buttonPin;
  thisLedPin = ledPin;
  debouncer = Bounce();
  debouncer.attach(buttonPin);
  debouncer.interval(5);
}

// Used to set led state.
void setLed(bool onOff) {
  prevLedState = currLedState;
  currLedState = onOff;
  currTime = millis();
  digitalWrite(thisLedPin, onOff);
}

// Checks if this button can light up:
//   if prevLedState == false, returns true
//   otherwise – false
bool Button::canSetLed(bool onOff) {
  if(prevLedState == onOff) {
    return false;
  } else {
      setLed(onOff); 
      return true;
  }
}

// Checks if button was on:
//   if yes, returns value in millis since it was on
//   if no, returns -1
int Button::getScore() {
  if(currLedState == true) {
    return millis() - currTime;
  } else {
      return -1;
  }
}

// Debug purposes only!
void debugCheck() {
  for (int i = 0; i < 3; i++) {
    setLed(true);
    delay(50);
    setLed(false);
    delay(50);
  }
}

uint8_t readValue() {
  return debouncer.read();
}

uint8_t getButtonPin() {
  return thisButtonPin;
}

uint8_t getLedPin() {
  return thisLedPin;
}
