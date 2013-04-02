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
  Serial.print("Contando iteraciones del main loop en 1s... ");
#endif
}

void loop()
{
  bot.sense();
  bot.resolve();
  bot.move();
  
#ifdef TEST
  static boolean _crono = true;
  static unsigned long _time = millis() + 1000;
  static unsigned long _i = 1;
  static char _cmd;
  
  if (_crono) {
    if (millis() < _time) {
      _i++;
    }
    else {
      _crono = false;
      Serial.print(_i);
      Serial.println(" iteraciones.");
      Serial.println("Atendiendo a comandos.");
      Serial.println();
    }
  }
  else {
    _cmd = Serial.read();
    switch (_cmd) {
      case 'o':
        bot.setDistance(3);
        Serial.println("Rival detectado!");
        Serial.println();
      break;
      
      case 'x':
        bot.setDistance(-1);
        Serial.println("Rival perdido...");
        Serial.println();
      break;
      
      case 's':
        Serial.print("* Estado: ");
        switch (bot.getState()) {
          case IDLE:          Serial.println("IDLE");          break;
          case SEARCHING:     Serial.println("SEARCHING");     break;
          case CHARGING:      Serial.println("CHARGING");      break;
          case REFINDING:     Serial.println("REFINDING");     break;
          case AVOIDING_EDGE: Serial.println("AVOIDING_EDGE"); break;
          default:            Serial.println("(desconocido)"); 
        }
        Serial.print("* Motor Izq.: ");
        Serial.println(bot.getSpeed(LEFT));
        Serial.print("* Motor Dch.: ");
        Serial.println(bot.getSpeed(RIGHT));
        Serial.println();
      break;
      
      default: break;
    }
    
    Serial.flush();
  }
#endif
}
