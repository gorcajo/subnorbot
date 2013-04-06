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

void SubnorBot::switchSniffers(boolean _fl, boolean _fr, boolean _r)
{
  if (_fl) sniffers.bits.fl = !sniffers.bits.fl;
  if (_fr) sniffers.bits.fr = !sniffers.bits.fr;
  if (_r) sniffers.bits.r = !sniffers.bits.r;
}


boolean SubnorBot::getSnifferFL()
{
  return sniffers.bits.fl;
}

boolean SubnorBot::getSnifferFR()
{
  return sniffers.bits.fr;
}

boolean SubnorBot::getSnifferR()
{
  return sniffers.bits.r;
}
#endif
