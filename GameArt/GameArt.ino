int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

int randomOutputPin;
const int buzzer = 9;

void PayYouLose(){
  int starttone = 800;

  for (int i=0; i<500; i--){
    tone(buzzer, starttone);
    starttone--;
    delay(4);
  }
  delay(1000);       
  noTone(buzzer);     
  //delay(400);       
}

void PayMiss(){
  int starttone = 500;
  tone(buzzer, starttone);
  delay(100);
  noTone(buzzer); 
}


void setup() {
  // so we can debug the ouput
  Serial.begin(115200); 
  
  //assign pins for joystick inputs
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);  

  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  PayMiss();

}


void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  randomOutputPin = random(5, 9);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print("Random Output: ");
  Serial.print(randomOutputPin);  
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  digitalWrite(LED_BUILTIN, !SW_state);
  if (SW_state == 0){ PayMiss();}
  


  delay(100);
  
}