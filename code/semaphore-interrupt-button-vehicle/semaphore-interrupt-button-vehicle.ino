/*
Developed in the Universidad de Costa Rica for the course 
Sistemas Empotrados de Tiempo Real - CI-0155
*/

// Define constants for the Arduino Uno R3
const int RED=2;            // define the pin for the RED LED
const int YELLOW=4;         // define the pin for the YELLOW LED
const int GREEN=7;          // define the pin for the GREEN LED
const int BUZZER = 9;       // define the pin for the BUZZER
const int BUTTON = 10;      // define the pin for the BUTTON

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
  // Declare output pins for LEDs
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);   
  pinMode(BUZZER, OUTPUT);
  // Initialize the pushbutton pin as an input:
  pinMode(BUTTON, INPUT);
}

void loop() {
  digitalWrite(GREEN,HIGH);
  // read the state of the pushbutton value:
  int buttonState = digitalRead(BUTTON);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
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
  // (ti - tu) sounds. 2 sounds per function call.
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