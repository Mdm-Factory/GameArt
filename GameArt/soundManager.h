const int buzzer = 9;

void PlayYouLose(){
  int starttone = 800;

  for (int i=0; i<200; i--){
    tone(buzzer, starttone);
    starttone--;
    delay(10);
  }     
  noTone(buzzer);         
}

void PlayMiss(){
  int starttone = 500;
  tone(buzzer, starttone);
  delay(100);
  noTone(buzzer); 
}

void PlayOk(){
  int starttone = 1000;
  tone(buzzer, starttone);
  delay(100);
  noTone(buzzer); 
}


void setupSound(){
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  PlayOk();
}
