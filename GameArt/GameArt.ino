//#include <TimedAction.h>
#include "lcdManager.h"
#include "soundManager.h"
#include "joystickManager.h"
#include "gameRules.h"

//TimedAction timedAction = TimedAction(1000,blink);

int currentLEDOn = 11;  // which random LED is about to blink?
int currentScore = 0;
int currentHealth = 10;
struct positions joystickVector;

int ledOutputs[4] = {11,8,9,13};  // up, right, down, left

void setup() {

  // so we can debug the ouput
   Serial.begin(9600); 

  // special setup for header modules
  setupJoystick();
  setupSound();

  // fun welcome sequence, also set LED to OUTPUT mode
  for (int i=0; i <4; i++){
    pinMode(ledOutputs[i], OUTPUT); 
    digitalWrite(ledOutputs[i], 1); 
    PlayOk();
    digitalWrite(ledOutputs[i], 0);  
  }

}


void loop() {

  // reset the progress indicators
  setupLCDHomeScreen();
  currentHealth = 10;
  currentScore = 0;

  // wait until player is ready!
  while (!buttonIsPressed()){
    delay(100);
  }

  // game start
  startProgress(); 

  bool advanceNextLED = true;
  //currentLEDOn = nextRandomLed();
  // game loop
  while (currentHealth > 0){   

    if (advanceNextLED){
        digitalWrite(currentLEDOn, 0);  // turn off current LED
        currentLEDOn = ledOutputs[nextRandomLed()];   
        digitalWrite(currentLEDOn, 1); // light it up!
        //Serial.println("New target: " + currentLEDOn);
        //PlayOk();
        advanceNextLED = false;
    }

    joystickVector = checkJoytickPosition();  //need to check user inputs
    int points = checkUserInput(currentLEDOn, joystickVector.angle, joystickVector.magnitude );
    displayProgress(currentScore, currentHealth, joystickVector.angle, joystickVector.magnitude);

    switch (points) {
      case 0:
        // No points, but not out of time
        break;
      case -1:
        // Miss, user loses health
        PlayMiss();
        currentHealth--;
        advanceNextLED = true;
        //delay(pauseAfterMiss);  // catch your breath
        break;
      default:   
        // any positive number of points to award
        PlayOk();
        currentScore = currentScore + points;
        advanceNextLED = true;   
        break;
    }

    delay(100);
    currentScore++;  //you get somepoints for showing up.
  }

  // Game Over
  endProgress(currentScore);
  PlayGameOver();
  delay(3000);

}