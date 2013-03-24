#include "subnorbot.h"

void SubnorBot::initialize()
{
  //Captura del tiempo actual:
  unsigned long _startTime = millis();
  
  //Inicializacion del estado de los siguelineas:
  sniffers.ne = 0;
  sniffers.se = 0;
  sniffers.sw = 0;
  sniffers.nw = 0;
  sniffers.any = 0;
  
  //Inicializacion del sonar:
  sonar.obj = new NewPing(PIN_SONAR_TRIGGER, PIN_SONAR_ECHO, DOJO_DIAMMETER);
  sonar.dist = -1;
  
  //Inicializacion de las velocidades deseadas de los motores:
  engines.speedR = 0;
  engines.speedL = 0;
  
  //Codigo de error:
  error = 0;
  
  //Espera de 5s menos el tiempo que ha llevado ejecutar este metodo:
  delay(5000 - (millis() - _startTime));
}
