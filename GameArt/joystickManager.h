int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;

void setupJoystick(){
  // assign pins for joystick inputs
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

void checkJoytickPosition(int currentTargetLed){
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print("Random Output: ");
  Serial.println(currentTargetLed);  
}

int buttonIsPressed(){
    return !digitalRead(SW);
}