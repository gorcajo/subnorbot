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
