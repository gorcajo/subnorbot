#include "subnorbot.h"

/******* depuracion *******/
/*void _printVector(int x, int y)
{
    Serial.write("(");
    Serial.print((int)((float)x*0.9 + 90));
    Serial.write(",");
    Serial.print((int)((float)y*0.9 + 90));
    Serial.write(")\n");
}*/

void SubnorBot::resolve()
{
  //Definicion de los estados de la maquina de estados:
  static enum {
    SEARCHING,
    CHARGING
  } state = SEARCHING;
  
  //Maquina de estados finitos, nucleo de la IA:
  switch (state) {
    case SEARCHING:
      if (sonar.dist == -1)
        rotate(LEFT);
      else
        state = CHARGING;
    break;
    
    case CHARGING:
      if (sonar.dist == -1)
        state = SEARCHING;
      else
        goAhead(100);
    break;
  }
}

void SubnorBot::rotate(Side side)
{
  if (side = LEFT)
    setSpeed(-100, 100);
  else
    setSpeed(100, -100);
}

void SubnorBot::pivot(Side side)
{
  if (side = LEFT)
    setSpeed(0, 100);
  else
    setSpeed(100, 0);
}

void SubnorBot::goAhead(int speed)
{
  setSpeed(speed, speed);
}
