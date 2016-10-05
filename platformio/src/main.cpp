#include "Arduino.h"
#include "drakkar.h"


int potentiometer_pin = A0;
int currentSensor_pin = A1;
int EMGFront_pin = A2;
int EMGBack_pin = A3;
int endstop_pin = 11;
int clockwise_pin = 8;
int counterclockwise_pin = 9;
int speed_pin = 10;
Drakkar drakkar(potentiometer_pin,
                currentSensor_pin,
                endstop_pin,
                clockwise_pin,
                counterclockwise_pin,
                speed_pin,
                EMGFront_pin,
                EMGBack_pin);

void setup() {
  Serial.begin(9600);
  pinMode(potentiometer_pin, INPUT);
  pinMode(currentSensor_pin, INPUT);
  pinMode(endstop_pin, INPUT);
  pinMode(clockwise_pin, OUTPUT);
  pinMode(counterclockwise_pin, OUTPUT);
  pinMode(speed_pin, OUTPUT);
}

void loop() {
  drakkar.run();
  delay(100);

}
