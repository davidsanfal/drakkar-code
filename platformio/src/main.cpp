#include <Arduino.h>
#include <drakkar.h>

#define pidTime 10 //ms

// (potentiometer, currentSensor, endstop, up, down, speed, EMGFront, EMGBack)
Drakkar drakkar(A0, A1, 2, 4, 5, 3, A2, A3);

void endstop(){
  drakkar.endstop();
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(drakkar.get_endstop_pin()), endstop, CHANGE);
  Serial.begin(9600);
}

void loop() {
  drakkar.debug();
  delay(100);

}
