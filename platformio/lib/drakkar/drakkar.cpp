#include "drakkar.h"
#include <Arduino.h>

#define AnalogResolution 1023
#define MaxSpeed 20
#define PotentiometerLong 100


Drakkar::Drakkar(int potentiometer_pin, int currentSensor_pin, int endstop_pin,
                 int up_pin, int down_pin, int speed_pin,
                 int EMGFront_pin, int EMGBack_pin):
                 pid(1,0,0,0,1024),
                 leg_EMG(EMGFront_pin, EMGBack_pin){
  pinMode(potentiometer_pin, INPUT);
  pinMode(currentSensor_pin, INPUT);
  pinMode(endstop_pin, INPUT);
  pinMode(up_pin, OUTPUT);
  pinMode(down_pin, OUTPUT);
  pinMode(speed_pin, OUTPUT);
  this->potentiometer_pin = potentiometer_pin;
  this->currentSensor_pin = currentSensor_pin;
  this->endstop_pin = endstop_pin;
  this->up_pin = up_pin;
  this->down_pin = down_pin;
  this->speed_pin = speed_pin;
  this->pid.Initialize();
  this->lastTime = 0;
  this->endstop_status = digitalRead(this->endstop_pin);
  this->output = 0;
}

void Drakkar::debug(){
  Serial.print(analogRead(this->potentiometer_pin));
  Serial.print(" , ");
  Serial.print(digitalRead(this->endstop_pin));
  Serial.print(" , ");
  this->leg_EMG.debug();
  Serial.print(" , ");
  Serial.println(this->output);
}

int Drakkar::run(){
  unsigned long now = millis();
  double position = (analogRead(this->potentiometer_pin)/AnalogResolution) * PotentiometerLong;
  EMGInfo emg_info = this->leg_EMG.read();
  double new_position = position +((double)(MaxSpeed*emg_info.speed) * (double)(now-lastTime));
  this->output = this->pid.Compute(new_position, position/AnalogResolution)*AnalogResolution;
  this->writeMotor();
  this->lastTime = now;
  return 0;
}

void Drakkar::writeMotor(){
  this->endstop_status = digitalRead(this->endstop_pin);
  digitalWrite(this->up_pin, (int)(this->output > 0));
  digitalWrite(this->down_pin, (int)(this->output < 0));
  if(this->output > 0) this->output = this->output * this->endstop_status;
  analogWrite(this->speed_pin, abs(this->output));
}

void Drakkar::endstop(){
  Serial.print("Endstop Interrupt");
  this->writeMotor();
}
