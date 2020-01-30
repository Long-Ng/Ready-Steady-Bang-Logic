#include <SR04.h>;
#include "SR04.h"
#include "pitches.h"
#define BLUE1 7
#define GREEN1 8
#define RED1 9

#define BLUE2 4
#define GREEN2 5
#define RED2 6
int melody[] = {
  NOTE_D3, NOTE_D3, NOTE_D4, NOTE_A3};
int reload1 = A0;
int fire1 = A1;
int reload2 = A2;
int fire2 = A3;
int startbutton = 0;
//int led1 = 2;
int led2 = 3;
int led3 = A4;
int led4 = A5;
int trig1 = 13;
int echo1 = 12;
int trig2 = 11;++6
38
int echo2 = 10;
int sound = 2;


SR04 sr041 = SR04(echo1,trig1);
SR04 sr042 = SR04(echo2,trig2);
int c1,c2,c3,c4;
int p1,p2,p3,p4=0;

int P1H = 3;
int P2H = 3;
bool SB = false;
bool P1R = false;
bool P2R = false;
bool light1 = false;
bool light2 = false;
bool light3 = false;
bool light4 = false;
bool shooton = false;
bool P1S = false;
bool P2S = false;
bool P1U = false;
bool P2U = false;
bool P1W = false;
bool P2W = false;
int  identify;
long int ran = 0;
bool once = false;
long int dis1;
long int dis2;
long int trigdis1 =50;
long int trigdis2 =50;

int redValue1;
int greenValue1;
int blueValue1;

int redValue2;
int greenValue2;
int blueValue2;

void checkready()
{ 
  if(analogRead(A0) <= 150 && P1R == false)
  { Serial.println(analogRead(A0));
    delay(1000);
    Serial.println("P1 Ready");
    P1R = true;
    
  }
  if(analogRead(A2) <= 150 && P2R == false)
  {
    Serial.println(analogRead(A2));
    delay(1000);
    Serial.println("P2 Ready");
    
    P2R = true;
    
  }
  if(P1R == true && P2R == true)
  {
    //Serial.println("Let's play");
    //Serial.println("Resetting...");
    //P1R = false;
   // P2R = false;
    //SB = false;
  }
}

void setmillisforc()
{
  c1= millis();
  c2= millis();
  c3= millis();
  c4= millis();
}

void setmillisforp()
{
  p1= millis();
  p2= millis();
  p3= millis();
  p4= millis();
}

void setlightlow()
{
  //digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void reset()
{
   Serial.println("Reset");
   delay(2000);
      light1 = false;
      light2 = false;
      light3 = false;
      light4 = false;
  //    digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      p1 = millis();
      p2 = millis();
      p3 = millis();
      p4 = millis();
      identify=0;
         Serial.println("Resetting...");
      P1R = false;
      P2R = false;
     
      once = false;
      shooton = false;
      P1U = false;
      P2U = false;
      P1S = false;
      P2S = false;
      P1W = false;
      P2W = false;
}

void timing()
{
  c1= millis();
  c2= millis();
  c3= millis();
  c4= millis();
  for(identify; identify<1;identify++)
  {
    ran = random(3000,7000);   
    Serial.println(ran);
  }
  if(c1-p1>=1000 && light1 == false)
    {
      p1 = millis();
      //digitalWrite(led1,HIGH);
      Serial.println("light 1");
      light1 = true;
      tone(sound,NOTE_C4,500);
      
    }
  if(c2-p2>=2000 && light2 == false)
  {
    p2 = millis();
    Serial.println("light 2");
    digitalWrite(led2,HIGH);
    light2 = true;
    tone(sound,NOTE_C4,500);
  }
  if(c3-p3>=3000 && light3 == false)
  {
    p3 = millis();
    Serial.println("light 3");
    light3 = true;
    digitalWrite(led3,HIGH);
    tone(sound,NOTE_C4,500);
  }
  if(c4-p4>=ran && light4 == false)
  {
    p4 = millis();
    Serial.println(ran);
    Serial.println("light 4");
    digitalWrite(led4,HIGH);
    light4 = true;
    shooton = true;
    tone(sound,NOTE_C5,1000);
  }
//  if(light1 == true && light2 == true && light3 == true && light4 == true)
//    {
//      delay(2000);
//      Serial.println("Reset");
//      light1 = false;
//      light2 = false;
//      light3 = false;
//      light4 = false;
//      digitalWrite(led1,LOW);
//      digitalWrite(led2,LOW);
//      digitalWrite(led3,LOW);
//      digitalWrite(led4,LOW);
//      p1 = millis();
//      p2 = millis();
//      p3 = millis();
//      p4 = millis();
//      identify=0;
//         Serial.println("Resetting...");
//      P1R = false;
//      P2R = false;
//      SB = false;
//      once = false;
//      shooton = false;
//      P1U = false;
//      P2U = false;
//      P1S = false;
//      P2S = false;
//    }
}

void upcheck()
{
  dis1 = sr041.Distance();
  dis2 = sr042.Distance();
  if(trigdis1 >= dis1 && P1U == false)
  {
    P1U = true;
    if(P1U == true && shooton == false)
    {
      Serial.println("P1 prematurely aimed at P2, P2 wins");
      P2W = true;
      return;
    }
    else
      Serial.println("P1 gun leveled");
  }
  if(trigdis2 >= dis2 && P2U ==false)
  {
    P2U = true;
    if(P2U == true && shooton == false)
    {
      Serial.println("P2 prematurely aimed at P1,P1 wins");
      P1W = true;
      return;
    }
    else
      Serial.println("P2 gun leveled");
  }
}

void firecheck()
{
  if(digitalRead(fire1) == LOW&& P1S == false)
  { 
    Serial.println("P1 Shot");
    P1S = true;
    if(P1S == true)
    {
      if(P1U == false || shooton == false)
      {
        Serial.println("P1 missed the shot. P2 wins");
        P2W = true;
        return;
      }
      else
      {
        Serial.println("P2 got hit. P1 wins");
        P1W = true;
        return;
      }
    }
  }
  if(analogRead(A3) <= 280 && P2S == false)
  {
    Serial.println("P2 Shot");
    P2S = true;
    if(P2S == true)
    {
      if(P2U == false || shooton == false)
      {
        Serial.println("P2 missed the shot. P1 wins");
        P1W = true;
        return;
      }
      else
      {
        Serial.println("P1 got hit. P2 wins");
        P2W = true;
        return;
      }
    }
  }
}

void healthmod()
{
  if(P1W == true)
  {
    P2H--;
    Serial.println("P2 health is decreased");
    Serial.println(P2H);
    tone(sound,NOTE_C4,100);
    delay(150);
    tone(sound,NOTE_E4,100);
    delay(150);
    tone(sound,NOTE_G4,100);
    delay(150);
    tone(sound,NOTE_C5,1000);
    delay(250);
    return;
    
  }
  if(P2W == true)
  {
    P1H--;
    Serial.println("P1 health is decreased");
    Serial.println(P1H);
    tone(sound,NOTE_C4,100);
    delay(150);
    tone(sound,NOTE_E4,100);
    delay(150);
    tone(sound,NOTE_G4,100);
    delay(150);
    tone(sound,NOTE_C5,1000);
    delay(250);
    return;
  }
}

void GOcheck()
{
  showlife();
  if(P1H <= 0)
  {
    Serial.println("P2 wins the game");
    reset();
    SB = false;
    P1H = 3;
    P2H = 3;
    return;
  }
  if(P2H <= 0)
  {
    Serial.println("P1 wins the game");
    reset();
    SB = false;
    P1H = 3;
    P2H = 3;
    return;
  }
  else if(P1W == true || P2W == true)
    reset();
}

void showlife()
{
    //RGP1
  if(P1H==1)
   {
      redValue1 = 255;
      greenValue1 = 0;
      blueValue1 = 0;
      analogWrite(RED1, redValue1);
      analogWrite(GREEN1, greenValue1);
      analogWrite(BLUE1, blueValue1);;
   }

  if(P1H==3)
  { 
    redValue1 = 0;
    greenValue1 = 0;
    blueValue1 = 255;
    analogWrite(RED1, redValue1);
    analogWrite(GREEN1, greenValue1);
    analogWrite(BLUE1, blueValue1);
  }

  if(P1H == 2)
  {
    redValue1 = 0 ;
    greenValue1 = 255;
    blueValue1 = 0;
    analogWrite(RED1, redValue1);
    analogWrite(GREEN1, greenValue1);
    analogWrite(BLUE1, blueValue1);
  }
  if(P1H == 0)
  {
    redValue1 = 0;
    greenValue1 = 0;
    blueValue1 = 0;
    analogWrite(RED1, redValue1);
    analogWrite(GREEN1, greenValue1);
    analogWrite(BLUE1, blueValue1);
  }

  //RGB2

    if(P2H==1)
   {
      redValue2 = 255;
      greenValue2 = 0;
      blueValue2 = 0;
      analogWrite(RED2, redValue2);
      analogWrite(GREEN2, greenValue2);
      analogWrite(BLUE2, blueValue2);
   }

  if(P2H==3)
  { 
    redValue2 = 0;
    greenValue2 =0;
    blueValue2 = 255;
    analogWrite(RED2, redValue2);
    analogWrite(GREEN2, greenValue2);
    analogWrite(BLUE2, blueValue2);
  }

  if(P2H == 2)
  {
    redValue2 = 0;
    greenValue2 = 255;
    blueValue2 = 0;
    analogWrite(RED2, redValue2);
    analogWrite(GREEN2, greenValue2);
    analogWrite(BLUE2, blueValue2);
  }
  if(P2H == 0)
  {
    redValue2 = 0;
    greenValue2 = 0;
    blueValue2 = 0;
    analogWrite(RED2, redValue2);
    analogWrite(GREEN2, greenValue2);
    analogWrite(BLUE2, blueValue2);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(startbutton, INPUT_PULLUP);
  pinMode(fire1,INPUT_PULLUP);
  //pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(sound,OUTPUT);
  //digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  randomSeed(analogRead(0));
  
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(BLUE1, OUTPUT);
  digitalWrite(RED1, HIGH);
  digitalWrite(GREEN1, LOW);
  digitalWrite(BLUE1, LOW);
  
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  digitalWrite(RED2, HIGH);
  digitalWrite(GREEN2, LOW);
  digitalWrite(BLUE2, LOW);
  
  
}

void loop() 
{
  
  if(digitalRead(startbutton) == LOW)
  {  
    SB = true;
    Serial.println("Start button pressed");
  }
  while(SB == true)
  {
    showlife();
    checkready();
    if(P2R == true && P1R == true)
    {
    if(once == false)
    {
      setmillisforp(); once = true;
    }
      timing();
      firecheck();
      upcheck();
    }
    healthmod();
    GOcheck();
  }
}
