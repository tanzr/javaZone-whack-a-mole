#ifndef cSpeedOfSound_h
#define cSpeedOfSound_h
#include "Arduino.h"
#include "Bounce2.h"

class Button {

  private:
          bool prevLedState;
          bool currLedState;
          bool nextLedState;
          unsigned long currTime; //milliseconds

          // Used to set led state.
          void setLed(bool onOff);

  public:
          Button();
          Button(int setOnForTime, uint8_t buttonPin, uint8_t ledPin); // in milliseconds

          // Checks if this button can light up:
          //   if prevLedState == False, returns True
          //   otherwise – False
          bool canSetLed(bool onOff);

          // Checks if button was on:
          //   if yes, returns value in millis since it was on
          //   if no, returns -1
          int getScore();

          // Used for debug purposes only.
          void debugCheck();

          // Read value from the pin
          uint8_t readValue();

          uint8_t getButtonPin();
          uint8_t getLedPin();
};

#endif
