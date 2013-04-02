#include "subnorbot.h"

//Es necesario incluir estas dos librerias aqui porque Arduino
//es una puta mierda y si no no las reconoce en subnorbot.h:
#include <NewPing.h>
#include <Servo.h>

SubnorBot bot = SubnorBot();

void setup()
{
#ifdef TEST
  Serial.begin(9600);
  Serial.println("Comenzando...");
#endif

  bot.initialize();
  
#ifdef TEST
  Serial.println("Fin espera de 5s.");
#endif
}

void loop()
{
  bot.sense();
  bot.resolve();
  bot.move();
  
#ifdef TEST
  static unsigned long _time = millis() + 1000;
  static unsigned long i = 1;
  if (millis() < _time)
    Serial.println(i);
  i++;
#endif
}
