int minMagnitude = 200;   // you must press joystick this far to count as in input
int levelDelaySpeeds[5] = {500, 400, 300, 200, 100};  //higher levels, less delay
int anglePositions[4] = {-180, 0, 180, -360};  // target radial angle (up, right, down, left)
int pauseAfterMiss = 750;
int angleTolerance1 = 45;  //how close you need to get points1
int points1 = 5;

int angleTolerance2 = 15;  //how close you need to get points2
int points2 = 10;

unsigned int startTime = 0;

int currentLevel = 1;

int getCurrentDelay() {
    return levelDelaySpeeds[currentLevel -1];
}

// turn on the next random led and start the timer.
int nextRandomLed(){
  startTime = millis();
  return random(0, 4);
}

bool outOfTime(){
    if (millis() > startTime + getCurrentDelay()){  
        return true;
    }
    return false;
}

void waitForButtonPress(int buttonIsPressed){
  while (!buttonIsPressed){
    delay(50);
  }
}

// returns number of points to award 0, 5, 10.  -1 will indicate a miss
int checkUserInput(int targetLED, int angle, int magnitude){
    int awardedPoints = 0;
    int targetAngle = anglePositions[targetLED];

    for (int i = 0; i< 100; i++ ){
        
        if (outOfTime()){
            //registers as a misss (no input received and no  time left .)
            Serial.println("Miss...out of time");
            return -1;  
        }        

        delay(10);
        bool triggeredMagnitude = (magnitude > minMagnitude); 
        if (triggeredMagnitude){
            Serial.println("Triggered: " + angle);
        
        if ((angle >= targetAngle - angleTolerance2) && (angle <= targetAngle - angleTolerance2)){
                // within tight tolerance, more points!!
                awardedPoints = points2; 
                Serial.println("Good hit!");
        } else if ((angle >= targetAngle + angleTolerance1) && (angle <= targetAngle + angleTolerance1)){
                // within looser tolerance, fewer points.
                awardedPoints = points1;
                Serial.println("Okay hit.");
        }
        }
        return awardedPoints;
    }

}
