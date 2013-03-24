#include "subnorbot.h"

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
    break;
    
    case CHARGING:
    break;
  }
}

void SubnorBot::rotate(Side side)
{
  if (side = LEFT)
    setSpeed(-50, 50);
  else
    setSpeed(50, -50);
}

void SubnorBot::pivot(Side side)
{
  if (side = LEFT)
    setSpeed(0, 100);
  else
    setSpeed(100, 0);
}

void SubnorBot::approach()
{
  setSpeed(25, 25);
}

void SubnorBot::charge()
{
  setSpeed(100, 100);
}

/******* depuracion *******/
void _printVector(int x, int y)
{
    Serial.write("(");
    Serial.print((int)((float)x*0.9 + 90));
    Serial.write(",");
    Serial.print((int)((float)y*0.9 + 90));
    Serial.write(")\n");
}
