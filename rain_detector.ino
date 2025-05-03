#include <Servo.h> // Include the library for the servo

#define RAIN_SENSOR A0
#define SERVO1_PIN  10
#define SERVO2_PIN  11

Servo myservo1; // Create servo object to control a servo
Servo myservo2;

int rainAdc = 0;
boolean rainState = false;
boolean previousRainState = false;
boolean changeState = false;
boolean moveServo = false;
int servoLoop = 0;
int pos1 = 0;
int pos2 = 0;

long currentMillis = 0;
long previousMillis = 0;
int interval = 2000;

void setup()
{
  pinMode(RAIN_SENSOR, INPUT_PULLUP);

  Serial.begin(9600);

  myservo1.attach(SERVO1_PIN);
  myservo2.attach(SERVO2_PIN);
}

void loop()
{
  rainAdc = analogRead(RAIN_SENSOR);
  if (rainAdc < 800) {
    if (rainState == false && changeState == false) {
      changeState = true;
      previousMillis = millis();
    }
    else if (rainState == true && changeState == true) {
      changeState = false;
    }
  }
  else {
    if (rainState == true && changeState == false) {
      changeState = true;
      previousMillis = millis();
    }
    else if (rainState == false && changeState == true) {
      changeState = false;
    }
  }

  if (changeState == false) {
    previousMillis = millis();
  }

  if (changeState == true) {
    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
      
      changeState == false;
      
      if (rainState == false) {
        rainState = true;
        moveServo = true;
      }
      else {
        rainState = false;
        moveServo = true;
      }
    }
  }

  if (moveServo == true) {
    if (rainState == true) {
      pos1 = 0;
      pos2 = 90;
      for (servoLoop = 0; servoLoop < 90; servoLoop++) {
        myservo1.write(pos1++);
        myservo2.write(pos2--);
        delay(30);
      }
      myservo1.write(103);
      myservo2.write(0);

      moveServo = false;
    }

    else {
      pos1 = 103;
      pos2 = 0;
      for (servoLoop = 0; servoLoop < 90; servoLoop++) {
        myservo1.write(pos1--);
        myservo2.write(pos2++);
        delay(30);
      }
      myservo1.write(0);
      myservo2.write(90);

      moveServo = false;
    }
  }
}
