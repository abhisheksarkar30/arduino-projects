#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int in=10,set=13,up=8,down=9,infan=1,exfan=0,tech=6,tecc=7,c=0;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Hello!");
  for(int i=0;i<7;i=i==1?6:i+1)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i,HIGH);
  }
  for(int i=8;i<11;i++)
  pinMode(i, INPUT);
  pinMode(13, INPUT);
  //delay(5000);
}

void loop()
{
  // when characters arrive over the serial port...
  double extemp=(analogRead(A0)+analogRead(A1))/2.0*0.48828125,intemp=(analogRead(A2)+analogRead(A3)+analogRead(A4)+analogRead(A5))/4.0*0.48828125,req=0;
  in=digitalRead(10);set=digitalRead(13);
  if(in)
    {
      delay(500);
      c++;
      lcd.clear();
      lcd.setCursor(0, 0);
      if(c%2)
      lcd.print("External Temp:");
      else
      lcd.print("Internal Temp:");
      lcd.setCursor(0, 1);
      lcd.print(c%2?extemp:intemp);
    }
    /*else if(ex)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("External Temp:");
      lcd.setCursor(0, 1);
      lcd.print(extemp);
    }*/
    else if(set)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Desired Temp:");
      delay(100);
      req=intemp;
      while(true)
      {
        lcd.setCursor(0, 1);
        lcd.print(req);
        up=digitalRead(8);
        down=digitalRead(9);
        if(up)
        req++;
        else if(down)
        req--;
        delay(100);
        if(digitalRead(10))
        break;
      }
        if(req<3||req>45)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Invalid Temp!!!");
          lcd.setCursor(0, 1);
          lcd.print("Plz Try Again!!!");
        }
      }
      if(req)
      if(intemp==req||extemp>50.0||intemp>45.0||intemp<3.0)
      {
        digitalWrite(tecc,LOW);
        digitalWrite(tech,LOW);
        req=0;
      }
      else if(intemp<req)
      {
        digitalWrite(tech,HIGH);
        digitalWrite(tecc,LOW);
      }
      else if(intemp>req)
      {
        digitalWrite(tecc,HIGH);
        digitalWrite(tech,LOW);
      }
      delay(100);
}
