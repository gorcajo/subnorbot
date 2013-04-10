#include "subnorbot.h"

#define SEARCHING_TURNING_TIME 1250
#define SEARCHING_GOING_TIME 250

void SubnorBot::resolve()
{
  //Para almacenar tiempos de REFINDING:
  static unsigned long _startTime = 0;
  static unsigned long _diffTime = 0;
  
  //Para almacenar tiempos de AVOIDING_EDGE:
  unsigned static long _maneuverTime = millis() + 1000;
  static int _phase = 0;
  
  //Maquina de estados finitos, nucleo de la IA:
  switch (state) {
    /**************************************************/
    case SEARCHING:
      if (sniffers.any)
        state = AVOIDING_EDGE;
      else if (sonar.dist == -1) {
        if (_maneuverTime < millis()) {
          _phase++;
          
          #define PHASES 4
          if (_phase%PHASES == 0) {
            rotate(RIGHT);
            _maneuverTime = millis() + SEARCHING_TURNING_TIME;
          }
          else if (_phase%PHASES == 1) {
            forward(100);
            _maneuverTime = millis() + SEARCHING_GOING_TIME;
          }
          else if (_phase%PHASES == 2) {
            rotate(LEFT);
            _maneuverTime = millis() + SEARCHING_TURNING_TIME;
          }
          else {
            _maneuverTime = millis() + SEARCHING_GOING_TIME;
            forward(100);
          }
          #undef PHASES 
        }
      }
      else
        state = CHARGING;
    break;
    /**************************************************/
    case CHARGING:
      if (sniffers.any)
        state = AVOIDING_EDGE;
      else if (sonar.dist != -1) {
        forward(100);
      }
      else {
        _startTime = millis() - SWEEP_TIME/2; //el tiempo de comienzo es la mitad para que del primer barrido haga solo medio cono
        //_startTime = millis() - SWEEP_TIME;
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
        else {
          state = SEARCHING;
          _maneuverTime = millis() + SEARCHING_TURNING_TIME;
        }
      }
      else
        state = CHARGING;
    break;
    /**************************************************/
    case AVOIDING_EDGE:
      if (sniffers.any) {
        switch (sniffers.byte) {
          case 0x01: //solo el sensor frontal izquierdo
            /*sniffers.byte &= 0x03;
            sniffers.bits.pivotingR = true;
            _maneuverTime = millis() + GIVING_SEMIBACK;*/
            reverse(100);
          break;
          
          case 0x02: //solo el sensor frontal derecho
            /*sniffers.byte &= 0x03;
            sniffers.bits.pivotingL = true;
            _maneuverTime = millis() + GIVING_SEMIBACK;*/
            reverse(100);
          break;
          
          case 0x03: //los dos sensores frontales
            /*sniffers.byte &= 0x03;
            sniffers.bits.turning = true;
            _maneuverTime = millis() + TURNING;*/
            reverse(100);
          break;
          
          case 0x04: //solo el sensor trasero
            forward(100);
          break;
          
          case 0x05: //solo los sensores frontal izquierdo y trasero
            /*sniffers.byte &= 0x03;
            sniffers.bits.pivotingR = true;
            _maneuverTime = millis() + GIVING_BACK;*/
            pivot(RIGHT);
          break;
          
          case 0x06: //solo los sensores frontal derecho y trasero
            /*sniffers.byte &= 0x03;
            sniffers.bits.pivotingL = true;
            _maneuverTime = millis() + GIVING_BACK;*/
            pivot(LEFT);
          break;
          
          /*default:
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
          break;*/
        }
      }
      else if (sonar.dist != -1)
        state = CHARGING;
      else {
        state = SEARCHING;
        _maneuverTime = millis() + SEARCHING_TURNING_TIME;
      }
    break;
    /**************************************************/
  }
  
  updateLED();
}

void SubnorBot::rotate(Side _side)
{
  /*if (_side == LEFT)
    setSpeed(-100, 100);
  else
    setSpeed(100, -100);*/
  #define DIFF 12
  #define CENTER_L 79
  #define CENTER_R 81
  if (_side == LEFT)
    setSpeed(CENTER_L + DIFF, CENTER_R + DIFF);
  else
    setSpeed(CENTER_L - DIFF, CENTER_R - DIFF);
  #undef DIFF
  #undef CENTER_L
  #undef CENTER_R
}

void SubnorBot::pivot(Side _side)
{
  /*if (_side == LEFT)
    setSpeed(0, 100);
  else
    setSpeed(100, 0);*/
    
  if (_side == LEFT)
    setSpeed(79, 180);
  else
    setSpeed(0, 81);
}

void SubnorBot::forward(unsigned int _speed)
{
  //setSpeed(_speed, _speed);
  setSpeed(0, 180);
}

void SubnorBot::reverse(unsigned int _speed)
{
  //setSpeed(-_speed, -_speed);
  setSpeed(180, 0);
}

#ifdef TEST
State SubnorBot::getState()
{
  return state;
}
#endif
