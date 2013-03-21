#include "subnorbot.h"

void SubnorBot::sense()
{    
  //...
}

void SubnorBot::setSniffers(boolean _ne, boolean _se, boolean _sw, boolean _nw)
{    
  sniffers.ne = _ne;
  sniffers.se = _se;
  sniffers.sw = _sw;
  sniffers.nw = _nw;
  sniffers.any = _ne | _se | _sw | _nw;
}
