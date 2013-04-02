#include "subnorbot.h"

void SubnorBot::sense()
{
#ifndef TEST
  //todo el codigo de este metodo debe ir dentro de este #ifndef
  
  //mirate los #defines en subnorbot.h que algunos te serviran, si necesitas mas los pones alli
  
  /*Para los siguelineas, haz algo asi:
  //true = borde detectado, independientemente de blanco o negro:
  sniffers.bits.ne = _ne;
  sniffers.bits.se = _se;
  sniffers.bits.sw = _sw;
  sniffers.bits.nw = _nw;*/
  
#endif
}

#ifdef TEST
void SubnorBot::setDistance(int _d)
{
  sonar.dist = _d;
}

void SubnorBot::switchSniffers(boolean _ne, boolean _se, boolean _sw, boolean _nw)
{
  if (_ne) sniffers.bits.ne = !sniffers.bits.ne;
  if (_se) sniffers.bits.se = !sniffers.bits.se;
  if (_sw) sniffers.bits.sw = !sniffers.bits.sw;
  if (_nw) sniffers.bits.nw = !sniffers.bits.nw;
}


boolean SubnorBot::getSnifferNE()
{
  return sniffers.bits.ne;
}

boolean SubnorBot::getSnifferSE()
{
  return sniffers.bits.se;
}

boolean SubnorBot::getSnifferSW()
{
  return sniffers.bits.sw;
}

boolean SubnorBot::getSnifferNW()
{
  return sniffers.bits.nw;
}


#endif
