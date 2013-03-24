#include "subnorbot.h"

typedef enum {
  Searching,
  Charging
} State;

void _printVector(int x, int y)
{
    Serial.write("(");
    Serial.print((int)((float)x*0.9 + 90));
    Serial.write(",");
    Serial.print((int)((float)y*0.9 + 90));
    Serial.write(")\n");
}

void SubnorBot::resolve()
{  
  static int i = -100;
  
  if (i>100) {
    i = -100;
    Serial.write("\n");
  }
  else {
    aproach();
    Serial.print(i);
    _printVector(engines.speedL, engines.speedR);
    i++;
  }
}

void SubnorBot::rotate(Side side)
{
  if (side = L)
    setSpeed(-25, 25);
  else
    setSpeed(25, -25);
}

void SubnorBot::pivot(Side side)
{
  //...
}

void SubnorBot::aproach()
{
  setSpeed(25, 25);
}

void SubnorBot::charge()
{
  setSpeed(100, 100);
}

void SubnorBot::evade()
{
  //...
}
