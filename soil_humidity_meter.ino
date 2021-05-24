#include<LiquidCrystal.h>
int buzzerPin = 9;  // Buzzer pin
int R = 12; // Red pin of RGB led
int G = 11; // Green pin of RGB led
int B = 10; // Blue pin of RGB led
int nemDegeri; //Current readed humidity
int nemSensorPin = A0; // humidity sensor pin

int delayTime = 100;  //initial delay time

LiquidCrystal lcd(8,7,6,5,4,3);  //initiliaze lcd screen


void setup() 
{
  //set up pins
  pinMode(nemSensorPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  lcd.begin(16,2); //start lcd screen
  lcd.print("Loading...");
  delay(1000);
}
void loop() {
  nemDegeri = analogRead(nemSensorPin);
  nemDegeri = map(nemDegeri,0,1023,0,100); //map humidity to range of 0 100
  nemDegeri = 100 - nemDegeri; //map  it to per cent
  lcd.clear(); //clear lcd screen
  char buffer [16];  //create a buffer to write in a lcd screen
  sprintf (buffer, "     %c %d",'%',nemDegeri); //set up humidity percent
  lcd.print("Toprak Nem Yuzde");  //print header
  lcd.setCursor(0,1); //go to new line
  lcd.print(buffer); //print humidity per cent
  if(nemDegeri>60){  //if percent above 60 it means plant not needs any water
      analogWrite(R,0);  //show a red color
      analogWrite(G,255);
      analogWrite(B,255);
      digitalWrite(buzzerPin,HIGH); //sound instantly to not add water
      delay(100);
      digitalWrite(buzzerPin,LOW);
      delay(100);
    }
  else if(nemDegeri>=50 && nemDegeri<=60){ // %50-%60 is good for plants
      analogWrite(R,255);
      analogWrite(G,0);  //green color
      analogWrite(B,255);
      digitalWrite(buzzerPin,HIGH);  //make a calmer sound
      delay(1000);
      digitalWrite(buzzerPin,LOW);
      delay(1000);
    }
   else{
    analogWrite(R,255);  //if below %50 just a blue color
    analogWrite(G,255);
    analogWrite(B,0);
    digitalWrite(buzzerPin,LOW); //and not sound buzzer
    delay(200);
   }
}