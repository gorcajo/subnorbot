#include "subnorbot.h"

int SubnorBot::move()
{    
  //Generación del PWM:
  digitalWrite(13, HIGH);
  delayMicroseconds(period/2);
  digitalWrite(13, LOW);
  delayMicroseconds(period/2);
  
  return 0;
}
