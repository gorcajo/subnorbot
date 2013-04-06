#include "subnorbot.h"

void SubnorBot::initialize()
{
  //Captura del tiempo actual:
  unsigned long _startTime = millis();
  
  //Estado inicial de la maquina de estados:
  state = IDLE;
  updateLED();
  
  //Inicializacion del estado de los siguelineas:
  sniffers.byte = 0;
  
  //Inicializacion del sonar:
  sonar.obj = new NewPing(PIN_SONAR_TRIGGER, PIN_SONAR_ECHO, DOYO_DIAMMETER);
  sonar.dist = -1;
  
  //Inicializacion de las velocidades deseadas de los motores:
  setSpeed(0, 0);
  if (!engines.left.attached())
    engines.left.attach(PIN_ENGINE_L);
  if (!engines.right.attached())
    engines.right.attach(PIN_ENGINE_R);
  
  //Configuracion de los pines del LED RGB:
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  
  //Codigo de error:
  error = 0;
  
  //Espera de 5s menos el tiempo que ha llevado ejecutar este metodo:
  delay(IDLE_TIME - (millis() - _startTime));
  
  //Estado actual de la maquina de estados:
  state = SEARCHING;
  updateLED();
}
