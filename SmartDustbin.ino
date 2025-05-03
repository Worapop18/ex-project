#include <Servo.h>       // Include the Servo library 
#define SERVO    3
#define TRIGPIN  12
#define ECHOPIN  11
#define PIEZO    8
Servo myServo;           // Create a servo object
int val = 0;
long duration;
long distance;

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_G5  784
#define NOTE_C6  1047


int openMelody[] = {NOTE_G5, NOTE_C6};
int openNoteDurations[] = {12, 8};

int closeMelody[] = {NOTE_C6, NOTE_G5};
int closeNoteDurations[] = {12, 8};

#define playOpenMelody() playMelody(openMelody, openNoteDurations, 2)
#define playCloseMelody() playMelody(closeMelody, closeNoteDurations, 2)

char inChar;
String inString;

void setup() {
  myServo.attach(SERVO);
  pinMode(TRIGPIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN, INPUT);  // Sets the echoPin as an Input
  pinMode(PIEZO, OUTPUT);
}

void loop() {

  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.017;        // Calculating the distance

  if (distance < 10 ) {           
    myServo.write(0);
    playOpenMelody();
    delay(5000);
    playCloseMelody();
  }
  else {          //Check data
    myServo.write(90);
    delay(15);
  }
}

void playMelody(int *melody, int *noteDurations, int notesLength)
{
  for (int thisNote = 0; thisNote < notesLength; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(PIEZO, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIEZO);
  }
}
