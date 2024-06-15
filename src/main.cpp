#include <Arduino.h>

void setup() {
  // Initialize the GPIO23 pin as an output
  pinMode(2, OUTPUT);
}

void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(2, HIGH);
  // Wait for a second
  delay(200);
  // Turn the LED off by making the voltage LOW
  digitalWrite(2, LOW);
  // Wait for a second
  delay(1000);
  digitalWrite(2, HIGH);
  // Wait for a second
  delay(200);
  // Turn the LED off by making the voltage LOW
  digitalWrite(2, LOW);
  // Wait for a second
  delay(3000);
}
