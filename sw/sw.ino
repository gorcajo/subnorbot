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
  static boolean _crono = true;                 //flag que indica si se estan contando las iteraciones del main loop al arrancar
  static unsigned long _time = millis() + 1000; //el instante cuando deben de dejar de contarse
  static unsigned long _i = 1;                  //las iteraciones del main loop contadas
  static char _cmd;                             //el comando de test recibido
  
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
      case '1':
        Serial.println("Siguelineas SW conmutado.");
        bot.switchSniffers(false, false, true, false);
        Serial.println();
      break;
      
      case '3':
        Serial.println("Siguelineas SE conmutado.");
        bot.switchSniffers(false, true, false, false);
        Serial.println();
      break;
      
      case '7':
        Serial.println("Siguelineas NW conmutado.");
        bot.switchSniffers(false, false, false, true);
        Serial.println();
      break;
      
      case '9':
        Serial.println("Siguelineas NE conmutado.");
        bot.switchSniffers(true, false, false, false);
        Serial.println();
      break;
      
      case 'o':
        bot.setDistance(10);
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
        Serial.print(bot.getSpeed(LEFT));
        Serial.println("%");
        Serial.print("* Motor Dch.: ");
        Serial.print(bot.getSpeed(RIGHT));
        Serial.println("%");
        Serial.println("* Estado de los siguelineas: ");
        Serial.println("    --");
        Serial.print("   |");
        if (bot.getSnifferNW()) Serial.print("x"); else Serial.print(" ");
        if (bot.getSnifferNE()) Serial.print("x"); else Serial.print(" ");
        Serial.println("|");
        Serial.print("   |");
        if (bot.getSnifferSW()) Serial.print("x"); else Serial.print(" ");
        if (bot.getSnifferSE()) Serial.print("x"); else Serial.print(" ");
        Serial.println("|");
        Serial.println("    --");
        Serial.println();
      break;
      
      default: break;
    }
    
    Serial.flush();
  }
#endif
}
