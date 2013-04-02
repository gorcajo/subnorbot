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
  static char cmd;
  
  if (millis() < _time) {
    Serial.println(i);
    i++;
  }
  else {
    cmd = Serial.read();
    switch (cmd) {
      case 'e':
        Serial.print("Motores: [L = ");
        Serial.print(bot.getSpeed(LEFT));
        Serial.print("] [R = ");
        Serial.print(bot.getSpeed(RIGHT));
        Serial.println("]");
      break;
      
      case 's':
        Serial.print("Estado: ");
        switch (bot.getState()) {
          case IDLE:          Serial.print("IDLE");          break;
          case SEARCHING:     Serial.print("SEARCHING");     break;
          case CHARGING:      Serial.print("CHARGING");      break;
          case REFINDING:     Serial.print("REFINDING");     break;
          case AVOIDING_EDGE: Serial.print("AVOIDING_EDGE"); break;
          default:            Serial.print("(desconocido)"); 
        }
      break;
      
      default:
      break;
    }
    Serial.flush();
  }
#endif
}
