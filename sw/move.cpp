#include "subnorbot.h"

int speedToAngle(int speed)
{
  return (float)speed*0.9 + 90;
}

void SubnorBot::move()
{
  engines.left.write(engines.speedL);
  engines.right.write(engines.speedR);
}

void SubnorBot::setSpeed(int l, int r)
{
  engines.speedL = speedToAngle(l * LEFT_SPEED_CORRECTION);
  engines.speedR = speedToAngle(r * RIGHT_SPEED_CORRECTION);
}
