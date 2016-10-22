struct EMGInfo {
  float power;
  float speed;
};

class LegEMG{
public:
  LegEMG(int, int);
  void debug();
  EMGInfo read();
private:
  unsigned int front_pin;
  unsigned int back_pin;
};
