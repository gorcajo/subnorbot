#include "subnorbot.h"

void SubnorBot::move()
{
  engines.left.write(engines.speedL);
  engines.right.write(engines.speedR);
}

void SubnorBot::setSpeed(int _l, int _r)
{
  engines.speedL = (_l * LEFT_SPEED_CORRECTION)*0.9 + 90;
  engines.speedR = (_r * RIGHT_SPEED_CORRECTION)*0.9 + 90;
}

void SubnorBot::setLED()
{
  switch (state) {
    case IDLE: //blanco
      digitalWrite(PIN_LED_R, HIGH);
      digitalWrite(PIN_LED_G, HIGH);
      digitalWrite(PIN_LED_B, HIGH);
    break;
    
    case SEARCHING: //verde
      digitalWrite(PIN_LED_R, LOW);
      digitalWrite(PIN_LED_G, HIGH);
      digitalWrite(PIN_LED_B, LOW);
    break;
    
    case CHARGING: //rojo
      digitalWrite(PIN_LED_R, HIGH);
      digitalWrite(PIN_LED_G, LOW);
      digitalWrite(PIN_LED_B, LOW);
    break;
    
    case REFINDING: //amarillo
      digitalWrite(PIN_LED_R, LOW);
      digitalWrite(PIN_LED_G, HIGH);
      digitalWrite(PIN_LED_B, HIGH);
    break;
    
    case AVOIDING_EDGE: //azul
      digitalWrite(PIN_LED_R, LOW);
      digitalWrite(PIN_LED_G, LOW);
      digitalWrite(PIN_LED_B, HIGH);
    break;
    
    default: //"negro"
      digitalWrite(PIN_LED_R, LOW);
      digitalWrite(PIN_LED_G, LOW);
      digitalWrite(PIN_LED_B, LOW);
  }
}

#ifdef TEST
int SubnorBot::getSpeed(Side _side)
{
  if (_side == LEFT)
    return (engines.speedL - 90)/0.9;
  else
    return (engines.speedR - 90)/0.9;
}
#endif
