#include "subnorbot.h"

int speedToAngle(int speed);
int angleToSpeed(int angle);

void SubnorBot::move()
{    
  engines.right.write(speedToAngle(engines.speedR));
}

int speedToAngle(int speed)
{
  return ((float)speed*0.9 + 90);
}

int angleToSpeed(int angle)
{
  return ((/9)*10);
}
