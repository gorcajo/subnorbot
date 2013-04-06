#include "subnorbot.h"

boolean _IRmeasure(int IR_sensor_num);

void SubnorBot::sense()
{
#ifndef TEST
  sonar.dist = (sonar.obj->ping_median(NUM_OF_SHOTS) / US_ROUNDTRIP_CM) - 1;
  sniffers.bits.fl = _IRmeasure(PIN_SNIFFER_FL);
  sniffers.bits.fr = _IRmeasure(PIN_SNIFFER_FR);
  sniffers.bits.r  = _IRmeasure(PIN_SNIFFER_R);
#endif
}

boolean _IRmeasure(int IR_sensor_num)
{
 
   int i=0;
   int measure = 0;
   boolean edge=0;
  
   for (i=0; i<4; i++){
    measure+=analogRead(IR_sensor_num);
   }
  
   measure=measure/4; //mathematic mean of 4 measures
  
   if (measure<= IR_THRESHOLD)//if white detected
   {
     #ifdef WHITEFLOOR
     edge=NOEDGE;//NOEDGE=0
     #endif
    
     #ifndef WHITEFLOOR
     edge=EDGE;//EDGE=1
     #endif
    
   }
    else   //black detected
    {      //measure>IR_THRESHOLD

     #ifdef WHITEFLOOR
     edge=EDGE;//EDGE=1
     #endif
    
     #ifndef WHITEFLOOR
     edge=NOEDGE;//NOEDGE=0
     #endif
         
    }
   
    return(edge);
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
