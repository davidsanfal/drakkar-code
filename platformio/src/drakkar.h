#include "pid.h"

struct EMGInfo {
  float power;
  float speed;
};

class Drakkar{
public:
  Drakkar (int,int,int,int,int,int,int,int);
  void debug();
  int run();
  void endstop();
  EMGInfo readEMG();
  void writeMotor();
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
  unsigned long lastTime;
  int endstop_status;
  float output;
};
