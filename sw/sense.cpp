#include "subnorbot.h"

void SubnorBot::sense()
{
#ifndef TEST
  //todo el codigo de este metodo debe ir dentro de este #ifndef
  
  /* Para los siguelineas, algo asi:
  sniffers.bits.ne = _ne;
  sniffers.bits.se = _se;
  sniffers.bits.sw = _sw;
  sniffers.bits.nw = _nw;*/
#endif
}

#ifdef TEST
void SubnorBot::setDistance(int d)
{
  sonar.dist = d;
}
#endif
