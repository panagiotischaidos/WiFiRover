#include<Wire.h>
//#include<LiquidCrystal_I2C.h>
#include<Servo.h>

/*const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
 
const int i2c_addr = 0x27;
 
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
*/
Servo myServo;

int Buzzer=3, Rspeed=5, Rneg=6, Rpos=7, Lpos=8, servoPin=9, Lneg=10, Lspeed=11, Trig=12, Echo=13, blockForwardMoves=0, currentServo=90, assistedMode=0;

int finalInt=20, crashOffset=5;

int crashZone=finalInt + crashOffset;

char currentMove='S';

void setup() 
{
  //lcd.begin(16,2);
  //lcd.setCursor(0,0);
  //lcd.print("Mode: Free");
  Serial.begin(115200);
  myServo.attach(9);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(Buzzer,OUTPUT);
  pinMode(Rspeed,OUTPUT);
  pinMode(Lspeed,OUTPUT);
  pinMode(Rpos,OUTPUT);
  pinMode(Rneg,OUTPUT);
  pinMode(Lpos,OUTPUT);
  pinMode(Lneg,OUTPUT);
  digitalWrite(Rspeed,HIGH);
  digitalWrite(Lspeed,HIGH);
  digitalWrite(Trig,LOW);
  while(!Serial);
}

void loop() 
{
  char charRead;
  while(!Serial.available())
  {
    if(assistedMode==1)
    {
      if (currentMove=='A')
      {
        if(currentServo!=90)
        {
          myServo.write(90);
          currentServo=90;
          //delay(100);                    <-------
        }
        digitalWrite(Trig,LOW);
        delayMicroseconds(2);
        digitalWrite(Trig,HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig,LOW);
        float duration=pulseIn(Echo,HIGH);
        float distance=(duration/2)*0.0343;
        //lcd.setCursor(0,1);
        //lcd.print("Distance: ");
        //int distanceInt=distance;
        //lcd.print(distanceInt);
        if (distance<=crashZone)
        {
          digitalWrite(Rpos,LOW);
          digitalWrite(Rneg,LOW);
          digitalWrite(Lpos,LOW);
          digitalWrite(Lneg,LOW);
          blockForwardMoves=1;
          currentMove='S';
          tone(Buzzer,2000,1000);
        }
      }
      else if (currentMove=='E')
      {
        if(currentServo!=130)
        {
          myServo.write(130);
          currentServo=130;
          //delay(100);                         <-----
        }
        digitalWrite(Trig,LOW);
        delayMicroseconds(2);
        digitalWrite(Trig,HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig,LOW);
        float duration=pulseIn(Echo,HIGH);
        float distance=(duration/2)*0.0343;
        //lcd.setCursor(0,1);
        //lcd.print("Distance: ");
        //int distanceInt=distance;
        //lcd.print(distanceInt);
        if (distance<=crashZone)
        {
          digitalWrite(Rpos,LOW);
          digitalWrite(Rneg,LOW);
          digitalWrite(Lpos,LOW);
          digitalWrite(Lneg,LOW);
          blockForwardMoves=1;
          currentMove='S';
          tone(Buzzer,2000,1000);
        }
      }
      else if (currentMove=='F')
      {
        if(currentServo!=50)
        {
          myServo.write(50);
          currentServo=50;
          //delay(100);                        <------
        }
        digitalWrite(Trig,LOW);
        delayMicroseconds(2);
        digitalWrite(Trig,HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig,LOW);
        float duration=pulseIn(Echo,HIGH);
        float distance=(duration/2)*0.0343;
        if (distance<=crashZone)
        {
          digitalWrite(Rpos,LOW);
          digitalWrite(Rneg,LOW);
          digitalWrite(Lpos,LOW);
          digitalWrite(Lneg,LOW);
          blockForwardMoves=1;
          currentMove='S';
          tone(Buzzer,2000,1000);
        }
      }
    }  
  }
  charRead=Serial.read();    
  
  if(charRead=='S')  // STOP
    {
      digitalWrite(Rpos,LOW);
      digitalWrite(Rneg,LOW);
      digitalWrite(Lpos,LOW);
      digitalWrite(Lneg,LOW); 
    }
  else if(charRead=='A')  // FORWARD
    {
      if(blockForwardMoves==0)
      {
        digitalWrite(Rpos,HIGH);
        digitalWrite(Rneg,LOW);
        digitalWrite(Lpos,HIGH);
        digitalWrite(Lneg,LOW);
        analogWrite(Lspeed,255);
        analogWrite(Rspeed,255);
      }  
    }
  else if(charRead=='B')  //BACKWARD
    {
      noTone(Buzzer);
      digitalWrite(Rpos,LOW);
      digitalWrite(Rneg,HIGH);
      digitalWrite(Lpos,LOW);
      digitalWrite(Lneg,HIGH); 
      analogWrite(Rspeed,255);
      analogWrite(Lspeed,255);
      if(currentServo!=90)
      {
        myServo.write(90); 
        currentServo=90;
      }
      blockForwardMoves=0;
    }
  else if(charRead=='C')  //LEFT
    {
      noTone(Buzzer);
      digitalWrite(Rpos,HIGH);
      digitalWrite(Rneg,LOW);
      digitalWrite(Lpos,LOW); 
      digitalWrite(Lneg,HIGH);
      analogWrite(Rspeed,200);
      analogWrite(Lspeed,200);
      if(currentServo!=90)
      {
        myServo.write(90); 
        currentServo=90;
      }
      blockForwardMoves=0;
    }
  else if(charRead=='D')   //RIGHT
    {
      noTone(Buzzer);
      digitalWrite(Rpos,LOW);
      digitalWrite(Rneg,HIGH);
      digitalWrite(Lpos,HIGH);
      digitalWrite(Lneg,LOW); 
      analogWrite(Rspeed,200);
      analogWrite(Lspeed,200);
      if(currentServo!=90)
      {
        myServo.write(90); 
        currentServo=90;
      }
      blockForwardMoves=0;
    }
  else if(charRead=='E')   //FRONTLEFT
    {
      if(blockForwardMoves==0)
      {
        digitalWrite(Rpos,HIGH);
        digitalWrite(Rneg,LOW);
        digitalWrite(Lpos,HIGH);
        digitalWrite(Lneg,LOW); 
        analogWrite(Rspeed,255);
        analogWrite(Lspeed,140);
      }  
    }
  else if(charRead=='F')   //FRONTRIGHT
    {
      if(blockForwardMoves==0)
      {
        digitalWrite(Rpos,HIGH);
        digitalWrite(Rneg,LOW);
        digitalWrite(Lpos,HIGH);
        digitalWrite(Lneg,LOW); 
        analogWrite(Rspeed,140);
        analogWrite(Lspeed,255);
      }  
    }
  else if(charRead=='G')   //BACKLEFT
    {
      noTone(Buzzer);
      digitalWrite(Rpos,LOW);
      digitalWrite(Rneg,HIGH);
      digitalWrite(Lpos,LOW);
      digitalWrite(Lneg,HIGH); 
      analogWrite(Rspeed,255);
      analogWrite(Lspeed,140);
      if(currentServo!=90)
      {
        myServo.write(90); 
        currentServo=90;
      }
      blockForwardMoves=0;
    }
  else if(charRead=='H')   //BACKRIGHT
    {
      noTone(Buzzer);
      digitalWrite(Rpos,LOW);
      digitalWrite(Rneg,HIGH);
      digitalWrite(Lpos,LOW);
      digitalWrite(Lneg,HIGH); 
      analogWrite(Rspeed,140);
      analogWrite(Lspeed,255);
      if(currentServo!=90)
      {
        myServo.write(90); 
        currentServo=90;
      }
      blockForwardMoves=0;
    }
  else if (charRead=='I')    //ASSISTED MODE ON
  {
   
      myServo.write(90);
      /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Mode: Assisted");*/
      assistedMode=1;
  }
  else if(charRead=='J')      //ASSISTED MODE OFF
  {  
      blockForwardMoves=0;
      myServo.write(90);
     /* lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Mode: Free");*/
      assistedMode=0;
  }
  else
  {
    blockForwardMoves=0;
    delay(1);
    finalInt = ((int)charRead - 48);
    if(Serial.available())
    {
      charRead=Serial.read();
      finalInt=((finalInt*10)+((int)charRead-48));
      if(Serial.available())
      {
        charRead=Serial.read();
        finalInt=((finalInt*10)+((int)charRead-48));
        if(Serial.available() or finalInt>400)
        {
          finalInt=400;
          while(Serial.available()){Serial.read();}
        }
      }
    }
  }
  crashZone=finalInt + crashOffset;
  currentMove=charRead;
  /*lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(charRead);
  lcd.setCursor(0,1);
  lcd.print(crashZone);
  */
}
