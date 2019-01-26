#ifndef AutoEngine_h
#define AutoEngine_h

#include "Arduino.h"

class AutoEngine
{
  public:
    const byte MAX_SPEED = 200;

    AutoEngine(
      byte leftRearPin,
      byte leftFrontPin,
      byte rightRearPin,
      byte rightFrontPin,
      byte leftPwmPin,
      byte rightPwmPin
    );
    void setup();
    void setSpeed(byte speed);
    void setFillUpInterval(unsigned short interval);
    byte getSpeed();
    byte increaseSpeed(byte speed);
    byte decreaseSpeed(byte speed);
    void moveForward();
    void moveBack();
    void turnLeft();
    void turnRight();
    void fillUp();
    void stopEngine();
    void processEngine();
  private:
    byte _leftRearPin;
    byte _leftFrontPin;
    byte _rightRearPin;
    byte _rightFrontPin;
    byte _leftPwmPin;
    byte _rightPwmPin;
    byte _currentSpeed;
    unsigned long _lastFillUp;
    unsigned short _fillUpInterval;
};

#endif
