#include "drakkar.h"


Drakkar::Drakkar(int potentiometer_pin, int currentSensor_pin, int endstop_pin,
                 int up_pin, int down_pin, int speed_pin,
                 int EMGFront_pin, int EMGBack_pin): pid(1,0,0,0,1024){
  this->potentiometer_pin = potentiometer_pin;
  this->currentSensor_pin = currentSensor_pin;
  this->endstop_pin = endstop_pin;
  this->up_pin = up_pin;
  this->down_pin = down_pin;
  this->speed_pin = speed_pin;
  this->EMGFront_pin = EMGFront_pin;
  this->EMGBack_pin = EMGBack_pin;
  this->pid.Initialize();
}

void Drakkar::run(){
  Serial.print(analogRead(this->potentiometer_pin));
  Serial.print(" , ");
  Serial.print(digitalRead(this->endstop_pin));
  Serial.print(" , ");
  Serial.print(analogRead(this->EMGFront_pin));
  Serial.print(" , ");
  Serial.print(analogRead(this->EMGBack_pin));
  float output = this->pid.Compute(500, analogRead(this->potentiometer_pin));
  Serial.print(" , ");
  Serial.println(output);
}
