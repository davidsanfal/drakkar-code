#include "Arduino.h"

#define MANUAL 0
#define AUTOMATIC 1

class PID {

  public:

    PID( double kp, double ki, double kd, double outMin, double outMax)
    {
      this->kp = kp;
      this->ki = ki;
      this->kd = kd;
      this->outMin = outMin;
      this->outMax = outMax;
      this->inAuto = true;
    }

    void Initialize()
    {
      lastInput = Input;
      ITerm = Output;
      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
    }

    float Compute(float Setpoint, float Input)
    {
      this->Setpoint = Setpoint;
      this->Input = Input;
      if (!inAuto)
      {
        return 0.0;
      }
      unsigned long now = millis();
      double timeChange = (double)(now - lastTime);
      if (timeChange < 0.0) timeChange = 0;

      double error = this->Setpoint - this->Input;
      ITerm += (ki * error * timeChange);

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
      double dErr = (error - lastErr) / timeChange;

      Output = kp * (error + ITerm + kd * dErr);

      if (Output > outMax)
      {
        double ITermAux = Output - outMax;
        ITerm = ITerm - ITermAux;
      }

      else if (Output < outMin)
      {
        double ITermAux = outMin - Output;
        ITerm += ITermAux;
      }

      Output = kp * error + ITerm + kd * dErr;

      lastErr = error;
      lastTime = now;
      return Output;
    }

    void SetTunings(double Kp, double Ki, double Kd)
    {
      this->kp = Kp;
      this->ki = Ki;
      this->kd = Kd;
    }

    void SetOutputLimits(double Min, double Max)
    {
      if (Min > Max) return;
      outMin = Min;
      outMax = Max;

      if (Output > outMax) Output = outMax;
      else if (Output < outMin) Output = outMin;

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
    }

    void SetMode(int Mode)
    {
      bool newAuto = (Mode == AUTOMATIC);
      if (newAuto && !inAuto)
      {
        Initialize();
      }
      inAuto = newAuto;
    }

  private:
    unsigned long lastTime;
    double Input, Output, Setpoint;
    double errSum, lastErr;
    double ITerm, lastInput;
    double kp, ki, kd;
    double outMin, outMax;
    bool inAuto;
};
