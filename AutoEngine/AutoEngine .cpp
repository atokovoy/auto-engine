#include "Arduino.h"
#include "AutoEngine.h"

AutoEngine::AutoEngine(
  byte leftRearPin,
  byte leftFrontPin,
  byte rightRearPin,
  byte rightFrontPin,
  byte leftPwmPin,
  byte rightPwmPin
) {
  _currentSpeed = 0;
  _lastFillUp = 0;
  _fillUpInterval = 0;
  _leftRearPin = leftRearPin;
  _leftFrontPin = leftFrontPin;
  _rightRearPin = rightRearPin;
  _rightFrontPin = rightFrontPin;
  _leftPwmPin = leftPwmPin;
  _rightPwmPin = rightPwmPin;
}

void AutoEngine::setup()
{
  pinMode(_leftRearPin, OUTPUT);
  pinMode(_leftFrontPin, OUTPUT);
  pinMode(_rightRearPin, OUTPUT);
  pinMode(_rightFrontPin, OUTPUT);
  pinMode(_leftPwmPin, OUTPUT);
  pinMode(_rightPwmPin, OUTPUT);

  stopEngine();
}

void AutoEngine::setSpeed(byte speed)
{
  _currentSpeed = speed;

  analogWrite(_leftPwmPin, speed);
  analogWrite(_rightPwmPin, speed);

  fillUp();
}

unsigned char AutoEngine::getSpeed()
{
  return _currentSpeed;
}

byte AutoEngine::increaseSpeed(byte speed)
{
  word newSpeed = _currentSpeed + speed;

  if (newSpeed > MAX_SPEED) {
    newSpeed = MAX_SPEED;
  }

  setSpeed(newSpeed);

  return newSpeed;
}

byte AutoEngine::decreaseSpeed(byte speed)
{
  word newSpeed = _currentSpeed - speed;

  if (newSpeed < 0) {
    newSpeed = 0;
  }

  setSpeed(newSpeed);

  return newSpeed;
}

void AutoEngine::fillUp()
{
  _lastFillUp = millis();
}

void AutoEngine::moveForward()
{
  digitalWrite(_rightRearPin, LOW);
  digitalWrite(_rightFrontPin, HIGH);
  digitalWrite(_leftRearPin, LOW);
  digitalWrite(_leftFrontPin, HIGH);

  fillUp();
}

void AutoEngine::moveBack()
{
  digitalWrite(_rightRearPin, HIGH);
  digitalWrite(_rightFrontPin, LOW);
  digitalWrite(_leftRearPin, HIGH);
  digitalWrite(_leftFrontPin, LOW);

  fillUp();
}

void AutoEngine::turnLeft()
{
  digitalWrite(_rightRearPin, HIGH);
  digitalWrite(_rightFrontPin, LOW);
  digitalWrite(_leftRearPin, LOW);
  digitalWrite(_leftFrontPin, HIGH);

  fillUp();
}

void AutoEngine::turnRight()
{
  digitalWrite(_rightRearPin, LOW);
  digitalWrite(_rightFrontPin, HIGH);
  digitalWrite(_leftRearPin, HIGH);
  digitalWrite(_leftFrontPin, LOW);

  fillUp();
}

void AutoEngine::stopEngine()
{
  digitalWrite(_rightRearPin, HIGH);
  digitalWrite(_rightFrontPin, HIGH);
  digitalWrite(_leftRearPin, HIGH);
  digitalWrite(_leftFrontPin, HIGH);
}

void AutoEngine::setFillUpInterval(unsigned short interval)
{
  _fillUpInterval = interval;
}

void AutoEngine::processEngine()
{
  if (_fillUpInterval && (millis() - _lastFillUp >= _fillUpInterval)) {
    stopEngine();
  }
}
