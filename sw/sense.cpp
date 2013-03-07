#include "subnorbot.h"

int SubnorBot::sense()
{    
  period = analogRead(3); //aquisición del periodo deseado
  
  return 0;
}
