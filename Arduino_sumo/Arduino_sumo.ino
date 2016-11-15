#include <Servo.h>
#include <stdio.h>

const int servoPin = 3;
const int motL_enPin = 14; // A0
const int motL_csPin = A2;
const int motL_pwmPin = 5;
const int motL_inaPin = 7;
const int motL_inbPin = 8;
const int motR_enPin = 15; // A1
const int motR_csPin = A3;
const int motR_pwmPin = 6;
const int motR_inaPin = 4;
const int motR_inbPin = 9;

int inByte = 0;
String inputString_L;
String inputString_R;
boolean stringComplete = false;
boolean dato_en_curso = false;
Servo myservo;
char mot = '0';
int mot_L = 0;
int mot_R = 0;

void setup()
{
  myservo.attach(servoPin);
  myservo.write(0);
  
  analogWrite(motL_pwmPin, 0);
  analogWrite(motR_pwmPin, 0);
  pinMode(motL_enPin, OUTPUT);
  pinMode(motR_enPin, OUTPUT);
  pinMode(motL_inaPin, OUTPUT);
  pinMode(motL_inbPin, OUTPUT);
  pinMode(motR_inaPin, OUTPUT);
  pinMode(motR_inbPin, OUTPUT);  
  digitalWrite(motL_enPin, HIGH);
  digitalWrite(motR_enPin, HIGH);
  
  Serial.begin(115200);
}

void loop()
{
  while (Serial.available())
  {
    char inByte = (char)Serial.read();
    
//    Serial.print(inByte);
    
    if(inByte == 'U')
      myservo.write(180);
    else if(inByte == 'D')
      myservo.write(0);
    else if(inByte == 'L' || dato_en_curso == true)
    {
      if(inByte == 'L')
      {
        inputString_L = "";
        inputString_R = "";
        dato_en_curso = true;
        mot = '1';
      }
      else if(inByte == 'R')
        mot = '2';
      else if(inByte == 'S')
      {
        dato_en_curso = false;
        stringComplete = true;
      }
      else if(mot == '1')
        inputString_L += inByte;
      else if(mot == '2')
        inputString_R += inByte;
    }      
  }

  if (stringComplete == true)
  {
    mot_L = inputString_L.toInt();
    mot_R = inputString_R.toInt();

    if(mot_L < 10 && mot_L > -10)
      mot_L = 0;
    if(mot_R < 10 && mot_R > -10)
      mot_R = 0;
      
//    Serial.println("");
//    Serial.println(mot_L);
//    Serial.println(mot_R);
    
    if(mot_L < 0)
    {
      digitalWrite(motL_inaPin, HIGH);
      digitalWrite(motL_inbPin, LOW);
      analogWrite(motL_pwmPin, -mot_L);
    }
    else
    {
      digitalWrite(motL_inaPin, LOW);
      digitalWrite(motL_inbPin, HIGH);
      analogWrite(motL_pwmPin, mot_L);
    }
    if(mot_R < 0)
    {
      digitalWrite(motR_inaPin, HIGH);
      digitalWrite(motR_inbPin, LOW);
      analogWrite(motR_pwmPin, -mot_R);
    }
    else
    {
      digitalWrite(motR_inaPin, LOW);
      digitalWrite(motR_inbPin, HIGH);
      analogWrite(motR_pwmPin, mot_R);
    }
    
    inputString_L = "";
    inputString_R = "";
    stringComplete = false;    
  }
  
  //comprobar batería y mandar indicación
  //  Serial.print('W');
    
}
