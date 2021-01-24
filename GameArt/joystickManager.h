#include <math.h>

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;

int xpos = 0;
int ypos = 0;
int* returnValues[2] = {0, 0};  // angle, magnitude

struct positions  {
   int angle;
   double magnitude;
};

struct positions pos;
void setupJoystick(){
  // assign pins for joystick inputs
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

struct positions checkJoytickPosition(){

    long x = analogRead(VRx) - 512;
    long y = analogRead(VRy) - 512;

    float angle = atan2( y, x );                 // in radians, zero is joystick move to right
    float angleDegrees = abs(angle * 57.2958 * 2);
    float magnitude = sqrt( x*x + y*y);    // Pythagoras

    if( magnitude > 512) magnitude = 512;

    // for future use?
    x = magnitude * cos( angle );
    y = magnitude * sin( angle );

    pos.angle = angleDegrees;
    pos.magnitude = magnitude;    
    return pos;   

}

int buttonIsPressed(){
    return !digitalRead(SW);
}