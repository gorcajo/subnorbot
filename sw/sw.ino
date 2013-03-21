#include "subnorbot.h"

//Es necesario incluir estas dos librerias aqui porque Arduino
//es una puta mierda y si no no las reconoce en subnorbot.h:
#include <NewPing.h>
#include <Servo.h>

SubnorBot bot = SubnorBot();

void setup()
{
  bot.initialize();
}

void loop()
{
  bot.sense();
  bot.resolve();
  bot.move();
}

/* aqui la rutina de atencion a la interrupcion de los siguelineas,
 * algo asi como...
isr_siguelineas_bla_bla_bla()
{
  bot.setSniffers(sensor_ne, sensor_se, sensor_sw, sensor_nw)
}
 * y a lo mismo se puede meter la ISR dentro de la clase SubnorBot
 */
