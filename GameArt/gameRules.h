int minMagnitude = 200;   // you must press joystick this far to count as in input
int anglePositions[4] = {180, 0, 180, 360};  // target radial angle (up, right, down, left)
int pauseAfterMiss = 750;

int angleTolerance1 = 45;  //how close you need to get points1
int points1 = 5;

int angleTolerance2 = 15;  //how close you need to get points2
int points2 = 10;
int startingDelay = 1000;
int minimumDelay = 250;  
int delayDecrement = 15;

unsigned int startTime = 0;

int currentLevel = 1;

// turn on the next random led and start the timer.
int nextRandomLed(){
    startTime = millis();
    return random(0, 4);
}

bool outOfTime(){
    int elapsedTime = millis() - startTime;
    if (elapsedTime >= startingDelay){  
        return true;
    }
    return false;
}


// returns number of points to award 0, 5, 10.  -1 will indicate a miss
int checkUserInput(int targetLEDPos, int angle, int magnitude){

    if (!outOfTime()){ return 0;}
    
    // increase speed
    startingDelay = startingDelay - delayDecrement ;
    if (startingDelay < minimumDelay) {startingDelay = minimumDelay;}

    int awardedPoints = 0;
    int targetAngle = anglePositions[targetLEDPos];
    bool triggeredMagnitude = (magnitude > minMagnitude); 

    Serial.println(targetAngle);
    if (triggeredMagnitude){
        if ((angle >= targetAngle - angleTolerance2) && (angle <= targetAngle + angleTolerance2)){
                // within tight tolerance, more points!!
                awardedPoints = points2; 
                Serial.println("Good hit!");
        } else if ((angle >= targetAngle - angleTolerance1) && (angle <= targetAngle + angleTolerance1)){
                // within looser tolerance, fewer points.
                awardedPoints = points1;
                Serial.println("Okay hit.");
        } else {
            awardedPoints = -1;  //miss
        }
        return awardedPoints;
    }

    return -1; 


}
