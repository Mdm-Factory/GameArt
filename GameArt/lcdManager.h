/*****************************************
 * name: I2C LCD2004
 * function: You should now see your I2C LCD2004 display "Hello,world!","IIC/I2C LCD2004"
 * "20 cols, 4 rows","www.sunfounder.com"
 ********************************/
//Email:service@sunfounder.com
//Website:www.sunfounder.com

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
void setupLCDHomeScreen()
{
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
   
  
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("      GameArt!      "); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("   By Luke & Dad    "); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("                    "); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print("Press Button To Play");
}



void startProgress(){
  lcd.setCursor ( 0, 0 ); 
  lcd.print("Score :              ");   // clear line
  lcd.setCursor ( 0, 1 ); 
  lcd.print("Health:              ");   // clear line
  lcd.setCursor ( 0, 2 ); 
  lcd.print("                    ");   // clear line
  lcd.setCursor ( 0, 3 ); 
  lcd.print("                    ");   // clear line
}

void displayProgress(int score, int health){

  String lineText = "";

  // Line 0 Score
  lineText = "";
  lineText += score;  
  lcd.setCursor ( 7, 0 );      
  lcd.print(lineText);

  // Line 1 Health
  lineText = "";
  if (health > 10) {health=10;}
  for (int i=1; i <= health; i++ ){
      lineText.concat("#");
  }
  lcd.setCursor ( 7, 1 );    
  lcd.print("           ");   // clear line  
  lcd.setCursor ( 7, 1 );  
  lcd.print(lineText);   
      
    
  
}


// you lose
void endProgress(int score)
{   
  lcd.setCursor ( 0, 0 );           
  lcd.print("Game Over!           "); 
  lcd.setCursor ( 0, 1 );            
  lcd.print("Final Score:         ");
  lcd.setCursor ( 0, 2 );            
  lcd.print(score);
  lcd.setCursor ( 0, 3 );           
  lcd.print("Press to play Again!");
}