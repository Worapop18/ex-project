#include <Servo.h>       // Include the Servo library 

// Define pin numbers
#define SERVO1    3
#define SERVO2    5
#define TRIGPIN   12
#define ECHOPIN   11
#define PIEZO     8

// Create servo objects
Servo myServo1;           
Servo myServo2;           
long duration;
long distance;

// Define notes for melodies
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

void setup() {
  // Attach servos to their respective pins
  myServo1.attach(SERVO1);
  myServo2.attach(SERVO2);

  // Initialize pins for Ultrasonic Sensor
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  // Initialize piezo pin
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  // Measure distance using Ultrasonic Sensor
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  duration = pulseIn(ECHOPIN, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.017;        // Convert to distance in cm

  // Check distance and control servos and piezo
  if (distance < 10) {                // Object detected within 10 cm
    myServo1.write(0);                // Move servo1 to 0 degrees
    myServo2.write(180);              // Move servo2 to 180 degrees
    playOpenMelody();                 // Play opening melody
    delay(5000);                      // Wait for 5 seconds
    playCloseMelody();                // Play closing melody
  } else {                            // No object detected or far away
    myServo1.write(90);               // Reset servo1 to 90 degrees
    myServo2.write(90);               // Reset servo2 to 90 degrees
    delay(15);
  }
}

// Function to play melodies
void playMelody(int *melody, int *noteDurations, int notesLength) {
  for (int thisNote = 0; thisNote < notesLength; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(PIEZO, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIEZO);
  }
}
