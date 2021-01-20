#include "lcdManager.h"
#include "soundManager.h"
#include "joystickManager.h"

int randomOutputPin;  // which random LED is about to blink?
int currentScore = 0;
int currentHealth = 10;
void setup() {

  // so we can debug the ouput
  Serial.begin(115200); 
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);  
  setupJoystick();
  setupSound();

}


void loop() {

  // reset the progress indicators
  setupLCDHomeScreen();
  currentHealth = 10;
  currentScore = 0;

  // wait until player is ready!
  while (!buttonIsPressed()){
    delay(50);
  }

  // game start
  startProgress(); 

  // game loop
  while (currentHealth > 0){
    randomOutputPin = random(5, 9);
    checkJoytickPosition(randomOutputPin);  //need to check user inputs

    digitalWrite(LED_BUILTIN, buttonIsPressed());  //just for testing
    
    // for testing the UI
    if (buttonIsPressed())
      { 
        PlayMiss();
        currentHealth--;
        displayProgress(currentScore, currentHealth);
      } else {
        currentScore++;
      }

    // only display score in increments of 10  (refresh rate problem)
    if (currentScore % 10 == 0) {
      displayProgress(currentScore, currentHealth);
    }

    // wait for inputs
    delay(50);
  }

  // Game Over
  endProgress(currentScore);
  PlayYouLose();

  // wait until player is ready to start again!
  while (!buttonIsPressed()){
    delay(50);
  }

}