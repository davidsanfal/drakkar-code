#include <pid.h>

struct EMGInfo {
  float power;
  float speed;
};

class Drakkar{
public:
  Drakkar(int,int,int,int,int,int,int,int);
  void debug();
  int run();
  void endstop();
  EMGInfo readEMG();
  void writeMotor();
  unsigned int get_endstop_pin(){return this->endstop_pin;}
private:
  unsigned int potentiometer_pin;
  unsigned int currentSensor_pin;
  unsigned int endstop_pin;
  unsigned int up_pin;
  unsigned int down_pin;
  unsigned int speed_pin;
  unsigned int EMGFront_pin;
  unsigned int EMGBack_pin;
  PID pid;
  unsigned long lastTime;
  int endstop_status;
  float output;
};
