#include "subnorbot.h"

void SubnorBot::resolve()
{
  //Para almacenar tiempos de REFINDING:
  static unsigned long _startTime = 0;
  static unsigned long _diffTime = 0;
  
  //Para almacenar tiempos de AVOIDING_EDGE:
  unsigned static long _maneuverTime;
  
  //Maquina de estados finitos, nucleo de la IA:
  switch (state) {
    /**************************************************/
    case SEARCHING:
      if (sniffers.any)
        state = AVOIDING_EDGE;
      else if (sonar.dist == -1)
        rotate(LEFT);
      else
        state = CHARGING;
    break;
    /**************************************************/
    case CHARGING:
      if (sonar.dist != -1) {
        forward(100);
      }
      else if (sniffers.any)
        state = AVOIDING_EDGE;
      else {
        _startTime = millis() - SWEEP_TIME/2; //el tiempo de comienzo es la mitad para que del primer barrido haga solo medio cono
        state = REFINDING;
      }
    break;
    /**************************************************/
    case REFINDING:
      if (sniffers.any)
        state = AVOIDING_EDGE;
      else if (sonar.dist == -1) {
        _diffTime = millis() - _startTime;
        
        if (_diffTime < SWEEPS*SWEEP_TIME) {
          if ((_diffTime/SWEEP_TIME)%2 == 0) //por cada intervalo de SWEEP_TIME milisegundos se cambia de direccion
            rotate(LEFT);
          else
            rotate(RIGHT);
        }
        else
          state = SEARCHING;
      }
      else
        state = CHARGING;
    break;
    /**************************************************/
    case AVOIDING_EDGE:
      if (sonar.dist != -1)
        state = CHARGING;
      else if (sniffers.any) {
        switch (sniffers.byte) {
          case 0x01: //solo el sensor frontal izquierdo
            sniffers.byte &= 0x03;
            sniffers.bits.pivotingR = true;
            _maneuverTime = millis() + GIVING_SEMIBACK;
            pivot(RIGHT);
          break;
          
          case 0x02: //solo el sensor frontal derecho
            sniffers.byte &= 0x03;
            sniffers.bits.pivotingL = true;
            _maneuverTime = millis() + GIVING_SEMIBACK;
            pivot(RIGHT);
          break;
          
          case 0x03: //los dos sensores frontales
            sniffers.byte &= 0x03;
            sniffers.bits.turning = true;
            _maneuverTime = millis() + TURNING;
            rotate(RIGHT);
          break;
          
          case 0x04: //solo el sensor trasero
            forward(100);
          break;
          
          case 0x05: //solo los sensores frontal izquierdo y trasero
            sniffers.byte &= 0x03;
            sniffers.bits.pivotingR = true;
            _maneuverTime = millis() + GIVING_BACK;
            pivot(RIGHT);
          break;
          
          case 0x06: //solo los sensores frontal derecho y trasero
            sniffers.byte &= 0x03;
            sniffers.bits.pivotingL = true;
            _maneuverTime = millis() + GIVING_BACK;
            pivot(LEFT);
          break;
          
          default:
            if (sniffers.bits.pivotingL) {
              if (_maneuverTime < millis())
                sniffers.byte &= 0x03;
              else
                pivot(LEFT);
            }
            else if (sniffers.bits.pivotingR) {
              if (_maneuverTime < millis())
                sniffers.byte &= 0x03;
              else
                pivot(RIGHT);
            }
            else if (sniffers.bits.turning) {
              if (_maneuverTime < millis())
                sniffers.byte &= 0x03;
              else
                rotate(RIGHT);
            }
          break;
        }
      }
      else
        state = SEARCHING;
    break;
    /**************************************************/
  }
  
  updateLED();
}

void SubnorBot::rotate(Side _side)
{
  if (_side == LEFT)
    setSpeed(-100, 100);
  else
    setSpeed(100, -100);
}

void SubnorBot::pivot(Side _side)
{
  if (_side == LEFT)
    setSpeed(0, 100);
  else
    setSpeed(100, 0);
}

void SubnorBot::forward(unsigned int _speed)
{
  setSpeed(_speed, _speed);
}

void SubnorBot::reverse(unsigned int _speed)
{
  setSpeed(-_speed, -_speed);
}

#ifdef TEST
State SubnorBot::getState()
{
  return state;
}
#endif
