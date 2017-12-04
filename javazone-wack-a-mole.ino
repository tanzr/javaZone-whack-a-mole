#include "Button.h"


// Addresses for the LEDs. We have 28 LEDs (one in each button).
static const uint8_t buttonPins[] = {13, 11, 4, 7, 5, 3, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48};
static const uint8_t ledPins[] = {12, 10, 8, 6, 4, 2, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49};

int const sizeOfArray = 28;
static Button* allButtons[sizeOfArray];

uint8_t score = 0;
uint8_t previousValue = -1;
int setOnForTime = 5000;

// Game modes
bool gameIsRunning = false;
bool debugMode = false;
bool demoMode = false;

//time in seconds for how long a game lasts is set in Python code.

//here we store the value for a random button
uint8_t randomNum = 0;

Bounce debouncer = Bounce(); 

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  for (int i = 0; i < sizeOfArray; i++) {
    allButtons[i] = new Button(setOnForTime, buttonPins[i], ledPins[i]);
    debouncer.attach(buttonPins[i]);
  }

  // Get new button to light up
  randomNum = random(sizeOfArray);
  
  // Reset all buttons' LEDs
  resetLEDs();

  //get some random noise from a pin that is not set to anything and set it as a seed
  randomSeed(analogRead(A10));
}

void loop() {
  debouncer.update();
  int value = debouncer.read();
  
  checkGameStateFromSerial(); 
  if (gameIsRunning) {
    while (true) {
      randomNum = random(sizeOfArray);
      if (allButtons[randomNum].canSetLed(true)) {
        break;
      }
    }
  }
}

void resetLEDs() {
  for (int i = 0; i < sizeOfArray; i++) {
    allButtons[i].canSetLed(false);
  }
}

void beginGame() {
  gameIsRunning = true;
}

void beginDemoMode() {
  demoMode = true;
  for (int i = 0; i < sizeOfArray; i++) {
    allButtons[i].canSetLed(true);
    delay(1000);
    allButtons[i].canSetLed(false);
  }
}

void beginDebugMode() {
  debugMode = true;
  for (int i = 0; i < sizeOfArray; i++) {
    allButtons[i].canSetLed(true);
    bool buttonPressed = false;
    uint8_t pressedButtonPin = -1;
    
    while (!buttonPressed) {
      for (int j = 0; j < sizeOfArray; j++) {
        uint8_t value = allButtons[j].readValue();
        if (value == LOW) {
          buttonPressed = true;
          pressedButtonPin = allButtons[j].getButtonPin();
          allButtons[j].checkDebug();
          break;
        } 
      }
    } 
    Serial.print("*Debugging button with LED pin: " + String(allButtons[i].getLedPin()));
    Serial.print("Registered button press on pin: " + String(pressedButtonPin);
  }
}


void endGame() {
  //reset values
  writeToSerial(score);
  gameIsRunning = false;
  score = 0;
  randomNum = random(sizeOfArray);
}


void writeToSerial(int data) {
  Serial.println(data);
}


void checkGameStateFromSerial() {
  //char serialListener = Serial.read();
  //if(serialListener == 'Y') {
    gameIsRunning = true;
  //}
}
