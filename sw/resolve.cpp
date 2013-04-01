#include "subnorbot.h"

void SubnorBot::resolve()
{
  //Definicion de los estados de la maquina de estados:
  static enum {
    SEARCHING,    //gira sobre si mismo buscando al rival
    CHARGING,     //se dirige hacia el rival y le empuja a toda velocidad
    REFINDING,    //cuando se pierde de vista al rival, realizara una busqueda barriendo en un cono de accion, durante un tiempo limitado
    AVOIDING_EDGE //corrige la posicion en el caso de encontrar un borde
  } state = SEARCHING;
  
  //Variables para almacenar tiempos:
  static unsigned long _startTime = 0;
  static unsigned long _diffTime = 0;
  
  char sniffersValue;
  
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
        goAhead(100);
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
          case 0x01: //solo el sensor ne
          case 0x08: //solo el sensor nw
          case 0x09: //solo los sensores ne y nw
            goAhead(-100);
          break;
          
          case 0x02: //solo el sensor se
          case 0x04: //solo el sensor sw
          case 0x06: //solo los sensores se y sw
            goAhead(100);
          break;
          
          case 0x03: //solo los sensores ne y se
            pivot(LEFT);
          break;
          
          case 0x0C: //solo los sensores nw y sw
            pivot(RIGHT);
          break;
          
          default: //cualquier otro caso se ignora y se pasa a SEARCHING
            state = SEARCHING;
          break;
        }
      }
      else
        state = SEARCHING;
    break;
    /**************************************************/
  }
}

void SubnorBot::rotate(Side side)
{
  if (side = LEFT)
    setSpeed(-100, 100);
  else
    setSpeed(100, -100);
}

void SubnorBot::pivot(Side side)
{
  if (side = LEFT)
    setSpeed(0, 100);
  else
    setSpeed(100, 0);
}

void SubnorBot::goAhead(int speed)
{
  setSpeed(speed, speed);
}
