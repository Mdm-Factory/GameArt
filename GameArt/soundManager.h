const int buzzerPin = 6;  

void PlayGameOver(){
  int starttone = 800;

  tone(buzzerPin, 500);
  delay(2000);
  noTone(buzzerPin);         
}

void PlayMiss(){
  int starttone = 500;
  tone(buzzerPin, starttone);
  delay(100);
  noTone(buzzerPin); 
}

void PlayOk(){
  int starttone = 1500;
  tone(buzzerPin, starttone);
  delay(100);
  noTone(buzzerPin); 
}


void setupSound(){
  pinMode(buzzerPin, OUTPUT); // Set buzzer - pin 9 as an output
  PlayOk();
}
