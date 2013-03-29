#include "subnorbot.h"

void SubnorBot::resolve()
{
  //Definicion de los estados de la maquina de estados:
  static enum {
    SEARCHING, //gira sobre si mismo buscando al rival
    CHARGING,  //se dirige hacia el rival y le empuja a toda velocidad
    REFINDING  //cuando se pierde de vista al rival, realizara una busqueda barriendo en un cono de accion, durante un tiempo limitado
  } state = SEARCHING;
  
  //Variables para almacenar tiempos:
  static unsigned long _startTime = 0;
  static unsigned long _diffTime = 0;
  
  //Maquina de estados finitos, nucleo de la IA:
  switch (state) {
    /**************************************************/
    case SEARCHING:
      if (sonar.dist == -1)
        rotate(LEFT);
      else
        state = CHARGING;
    break;
    /**************************************************/
    case CHARGING:
      if (sonar.dist == -1) {
        _startTime = millis() - SWEEP_TIME/2; //el tiempo de comienzo es la mitad para que del primer barrido haga solo medio cono
        state = REFINDING;
      }
      else
        goAhead(100);
    break;
    /**************************************************/
    case REFINDING:
      if (sonar.dist == -1) {
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
