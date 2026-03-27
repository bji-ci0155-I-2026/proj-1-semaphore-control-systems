const int RED=7;
const int YELLOW=4;
const int GREEN=2;
const int BUZZER = 6;
const int BUTTON = 12;
const int TRIGGER = 10;
const int ECHO = 13;

float duration, distance;

#include "pitches.h"

int semaphore_beep[] = {
  NOTE_CS6, NOTE_A5
};

int durations_beep[] = {
  4, 4
};

int durations_beep_increased_tempo[] = {
  8, 8
};



void setup() {
  // Declare output pins
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);   
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  // Initialize input pins
  pinMode(BUTTON, INPUT);
  pinMode(ECHO, INPUT);
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  digitalWrite(GREEN,HIGH);
  
  // Clear the trigger pin by setting it LOW
  digitalWrite(TRIGGER, LOW);
  // Allow the sensor to settle
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 10 microseconds to send out the ultrasonic pulse
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  // Clear the trigger pin again
  digitalWrite(TRIGGER, LOW);

  // Read the duration of the echo pulse (time it takes for the pulse to return)
  duration = pulseIn(ECHO, HIGH);

  // Speed of sound is approximately 340 meters per second
  // Calculate the distance in centimeters (duration is in microseconds, so we convert it to seconds and then to centimeters)
  distance = (duration*.0343)/2;

  Serial.print("Distance (cm): ");  
	Serial.println(distance);  
	delay(100);  

  // Check if the distance is less than or equal to 5 cm, which indicates a pedestrian is waiting
  if (distance <= 5.0) {
    allow_pedestrians();
  }
}

void allow_pedestrians(){
  delay(1000);
  blink(GREEN, 7);
  digitalWrite(GREEN, LOW);

  digitalWrite(YELLOW, HIGH);
  delay(4000);
  digitalWrite(YELLOW, LOW);
  
  digitalWrite(RED, HIGH);
  // Begin audio countdown
  for (int i = 0; i < 8; ++i) {
    PlayMusic(semaphore_beep, durations_beep, sizeof(semaphore_beep) / sizeof(int));
    delay(1000);
  }
  // Begin faster audio countdown
  for (int i = 0; i < 8; ++i) {
    PlayMusic(semaphore_beep, durations_beep_increased_tempo, sizeof(semaphore_beep) / sizeof(int));
    delay(700);
  }
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
}

// Credits https://github.com/arashjafari/audio-to-arduino?tab=readme-ov-file
void PlayMusic(int melody[], int durations[], int size) {
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(BUZZER, melody[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER);
  }
}

void blink(int LED_PIN, int repetitions){
  for (int i = 0; i < repetitions; ++i){
    digitalWrite(LED_PIN, LOW);
    delay(400);
    digitalWrite(LED_PIN, HIGH);
    delay(400);
  }
}