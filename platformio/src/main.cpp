#include <Arduino.h>
#include <drakkar.h>

#define stepTime 100 //ms

// (potentiometer, currentSensor, endstop, up, down, speed, EMGFront, EMGBack)
Drakkar drakkar(A0, A1, 2, 4, 5, 3, A2, A3);
unsigned long step = 0;

void endstop(){
  drakkar.endstop();
}

void setup() {
  attachInterrupt(digitalPinToInterrupt((unsigned int)drakkar.get_endstop_pin()), endstop, CHANGE);
  Serial.begin(9600);
}

void loop() {

  if(step < millis()){
    drakkar.debug();
    step = (unsigned long)stepTime + millis();
  }

}
