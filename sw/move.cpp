#include "subnorbot.h"

int speedToAngle(int speed)
{
  return (float)speed*0.9 + 90;
}

void SubnorBot::move()
{
  engines.left.write(speedToAngle(engines.speedL));
  engines.right.write(speedToAngle(engines.speedR));
}

void SubnorBot::setSpeed(int l, int r)
{
  engines.speedL = l - ENGINE_SPEED_CORRECTION;
  engines.speedR = r + ENGINE_SPEED_CORRECTION;
}
