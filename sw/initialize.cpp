#include "subnorbot.h"

void SubnorBot::initialize()
{
  //Captura del tiempo actual:
  unsigned long _startTime = millis();
  
  //Inicializacion del estado de los siguelineas:
  sniffers.bits.ne = 0;
  sniffers.bits.se = 0;
  sniffers.bits.sw = 0;
  sniffers.bits.nw = 0;
  
  //Inicializacion del sonar:
  sonar.obj = new NewPing(PIN_SONAR_TRIGGER, PIN_SONAR_ECHO, DOJO_DIAMMETER);
  sonar.dist = -1;
  
  //Inicializacion de las velocidades deseadas de los motores:
  engines.speedL = 0;
  engines.speedR = 0;
  if (!engines.left.attached())
    engines.left.attach(PIN_ENGINE_L);
  if (!engines.right.attached())
    engines.right.attach(PIN_ENGINE_R);
  
  //Codigo de error:
  error = 0;
  
  //Espera de 5s menos el tiempo que ha llevado ejecutar este metodo:
  delay(IDLE_TIME - (millis() - _startTime));
}
