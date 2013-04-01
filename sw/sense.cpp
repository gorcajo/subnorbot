#include "subnorbot.h"

void SubnorBot::sense()
{    
  //...
}

void SubnorBot::setSniffers(boolean _ne, boolean _se, boolean _sw, boolean _nw)
{    
  sniffers.bits.ne = _ne;
  sniffers.bits.se = _se;
  sniffers.bits.sw = _sw;
  sniffers.bits.nw = _nw;
}
