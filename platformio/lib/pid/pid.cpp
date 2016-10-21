#include <Arduino.h>
#include "pid.h"

#define MANUAL 0
#define AUTOMATIC 1

PID::PID( double kp, double ki, double kd, double outMin, double outMax){
  this->kp = kp;
  this->ki = ki;
  this->kd = kd;
  this->outMin = outMin;
  this->outMax = outMax;
  this->inAuto = true;
}

void PID::Initialize(){
  lastInput = Input;
  ITerm = Output;
  if (ITerm > outMax) ITerm = outMax;
  else if (ITerm < outMin) ITerm = outMin;
}

float PID::Compute(float Setpoint, float Input){
  this->Setpoint = Setpoint;
  this->Input = Input;
  if (!inAuto) return 0.0;
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  if (timeChange < 0.0) timeChange = 0;

  double error = this->Setpoint - this->Input;

  ITerm += (ki * error * timeChange);
  if (ITerm > outMax) ITerm = outMax;
  else if (ITerm < outMin) ITerm = outMin;

  double dErr = (error - lastErr) / timeChange;

  Output = kp * (error + ITerm + kd * dErr);
  if (Output > outMax) ITerm = ITerm - (double)(Output - outMax);
  else if (Output < outMin) ITerm += (double)(outMin - Output);
  Output = kp * error + ITerm + kd * dErr;

  lastErr = error;
  lastTime = now;
  return Output;
}

void PID::SetTunings(double Kp, double Ki, double Kd){
  this->kp = Kp;
  this->ki = Ki;
  this->kd = Kd;
}

void PID::SetOutputLimits(double Min, double Max){
  if (Min > Max) return;
  outMin = Min;
  outMax = Max;
  if (Output > outMax) Output = outMax;
  else if (Output < outMin) Output = outMin;
  if (ITerm > outMax) ITerm = outMax;
  else if (ITerm < outMin) ITerm = outMin;
}

void PID::SetMode(int Mode){
  bool newAuto = (Mode == AUTOMATIC);
  if (newAuto && !inAuto) Initialize();
  inAuto = newAuto;
}
