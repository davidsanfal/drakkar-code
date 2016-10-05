#include "pid.h"

class Drakkar{
public:
  Drakkar (int,int,int,int,int,int,int,int);
  void run();
  void readEMG(){};
private:
  int potentiometer_pin;
  int currentSensor_pin;
  int endstop_pin;
  int up_pin;
  int down_pin;
  int speed_pin;
  int EMGFront_pin;
  int EMGBack_pin;
  PID pid;
};
