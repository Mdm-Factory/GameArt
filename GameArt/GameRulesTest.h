int minMagnitude = 200;   // you must press joystick this far to count as in input
int pauseAfterMiss = 750;

int startTime = 0;

// turn on the next random led and start the timer.
int nextRandomLed(){
startTime = millis();
  return random(0, 4);
  //Serial.println(startTime);
}

bool outOfTime(){
    int elapsedTime = millis() - startTime;
    if (elapsedTime >= 500){  
        Serial.println(elapsedTime);
        return true;
    }
    return false;
}

int checkUserInput(int targetLED, int angle, int magnitude){

    int awardedPoints = 10;
    bool triggeredMagnitude = (magnitude > minMagnitude);
    if (outOfTime()){
        if (triggeredMagnitude){
            return awardedPoints;
        } else{
            return -1;  // miss
        }
    }
    return 0; //still have time
}
