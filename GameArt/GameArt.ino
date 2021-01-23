#include "lcdManager.h"
#include "soundManager.h"
#include "joystickManager.h"
#include "gameRules.h"

int currentLEDOn;  // which random LED is about to blink?
int currentScore = 0;
int currentHealth = 10;
struct positions joystickVector;

int ledOutputs[4] = {11,8,9,13};  // up, right, down, left

void setup() {

  // so we can debug the ouput
  Serial.begin(115200); 

  // special setup for header modules
  setupJoystick();
  setupSound();

  // fun welcome sequence, also set LED to OUTPUT mode
  for (int i=0; i <4; i++){
    Serial.println(ledOutputs[i]);
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
    delay(50);
  }

  // game start
  startProgress(); 

  bool advanceNextLED = true;
  //currentLEDOn = nextRandomLed();
  // game loop
  while (currentHealth > 0){   
    joystickVector = checkJoytickPosition();  //need to check user inputs
    int points = checkUserInput(currentLEDOn, joystickVector.angle, joystickVector.magnitude );

    if (advanceNextLED){
        digitalWrite(currentLEDOn, 0);  // turn off current LED
        delay(pauseAfterMiss);  // catch your breath
        currentLEDOn = ledOutputs[nextRandomLed()];   
        digitalWrite(currentLEDOn, 1); // light it up!
    }

    switch (points) {
      case 0:
        // No points, but not out of time
        break;
      case -1:
        // Miss, user loses health
        PlayMiss();
        currentHealth--;
        advanceNextLED = true;
        break;
      default:   
        // any positive number of points to award
        PlayOk();
        currentScore = currentScore + points;
        advanceNextLED = true;   
        break;
    }



    displayProgress(currentScore, currentHealth, joystickVector.angle, joystickVector.magnitude);
    delay(50);      // wait for inputs
  }

  // Game Over
  endProgress(currentScore);
  PlayYouLose();

  // wait until player is ready to start again!
  while (!buttonIsPressed()){
    delay(50);
  }

}