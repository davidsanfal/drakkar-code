class PID {

  public:
    PID(double, double, double, double, double);
    void Initialize();
    float Compute(float, float);
    void SetTunings(double, double, double);
    void SetOutputLimits(double, double);
    void SetMode(int);
  private:
    unsigned long lastTime;
    double Input, Output, Setpoint;
    double errSum, lastErr;
    double ITerm, lastInput;
    double kp, ki, kd;
    double outMin, outMax;
    bool inAuto;
};
