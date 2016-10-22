#include "legEMG.h"
#include <Arduino.h>

#define EMGMin 1
#define AnalogResolution 1023
#define MaxSpeed 20

LegEMG::LegEMG(int front_pin, int back_pin){
  this->front_pin = front_pin;
  this->back_pin = back_pin;
}

void LegEMG::debug(){
  Serial.print(analogRead(this->front_pin));
  Serial.print(" , ");
  Serial.print(analogRead(this->back_pin));
}

EMGInfo LegEMG::read(){
  int quadriceps = analogRead(this->front_pin);
  int hamstring = analogRead(this->back_pin);

  float speed = (quadriceps - hamstring) / AnalogResolution;

  float power = 0.0;
  if((quadriceps > EMGMin) or (hamstring > EMGMin)){
    if (speed >= 0.0) power = quadriceps/AnalogResolution;
    else power = hamstring/AnalogResolution;
  }

  EMGInfo info = {power, speed};
  return info;
}
