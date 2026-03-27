/*
Developed in the Universidad de Costa Rica for the course 
Sistemas Empotrados de Tiempo Real - CI-0155
*/

// Define constants for the Arduino Uno R3 semaphore
const uint8_t RED = 2;            // define the red led pin
const uint8_t YELLOW = 4;         // define the yellow led pin
const uint8_t GREEN = 7;          // define the green led pin

// Define stop and pass tempos
const uint16_t STOP_TEMPO = 4000;   // define the stop tempo
const uint16_t WARNING_TEMPO = 2000;   // define the warning tempo
const uint16_t PASS_TEMPO = 4000;   // define the pass tempo

void setup() {
  // Declare output pins for LEDs
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);   
}

void loop() {
  // Red light
  digitalWrite(RED, HIGH);
  delay(STOP_TEMPO);
  digitalWrite(RED, LOW);

  // Green light
  digitalWrite(GREEN, HIGH);
  delay(PASS_TEMPO);
  digitalWrite(GREEN, LOW);

  // Yellow light
  digitalWrite(YELLOW, HIGH);
  delay(WARNING_TEMPO);
  digitalWrite(YELLOW, LOW);
}
