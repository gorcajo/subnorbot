#ifndef SUBNORBOT_H
#define SUBNORBOT_H

#include <Arduino.h>

/** Clase SubnorBot
 * Manejo completo del robot. Su unica instancia se realiza como variable global en el fichero fuente principal (sw.ino).
 * Esta clase no tiene constructor (el compilador le asignara un constructor por defecto, vacio) ni destructor.
 */
class SubnorBot
{
  public:
    int initialize(); //Realiza todas las configuraciones iniciales (se ejecuta solo antes de entrar en el main loop).
    
    int sense();   //Encargado de realizar todas las adquisiciones del exterior y ofrecer informacion util.
    int resolve(); //Procesa la informacion de sense() y toma decisiones.
    int move();    //Segun las decisiones de resolve() realiza el manejo de los motores.
      
  private:
    int period;
};

#endif //SUBNORBOT_H
