#ifndef SUBNORBOT_H
#define SUBNORBOT_H

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

/** Clase SubnorBot
 *
 * Manejo completo del robot. Su unica instancia se realiza como variable
 * global en el fichero fuente principal (sw.ino).
 *
 * Esta clase no tiene constructor (el compilador le asignara un
 * constructor por defecto, vacio) ni destructor.
 *
 */
class SubnorBot
{
  public:
    //Realiza todas las configuraciones iniciales (se ejecuta solo antes de entrar en el main loop):
    void initialize();
    
    //Main loop:
    void sense();   //Encargado de realizar todas las adquisiciones del exterior y ofrecer informacion util.
    void resolve(); //Procesa la informacion de sense() y toma decisiones.
    void move();    //Segun las decisiones de resolve() realiza el manejo de los motores.
    
    //Almacena el estado de los siguelineas (implementada en sense.cpp):
    void setSniffers(boolean _ne, boolean _se, boolean _sw, boolean _nw);

  private:
    struct {        //bitfield que ocupa un byte
      char ne  : 1; //bit correspondiente al sensor frontal derecho (1 = borde detectado)
      char se  : 1; //bit correspondiente al sensor trasero derecho (1 = borde detectado)
      char sw  : 1; //bit correspondiente al sensor trasero izquierdo (1 = borde detectado)
      char nw  : 1; //bit correspondiente al sensor frontal izquierdo (1 = borde detectado)
      char any : 1; //la OR de los dems bits
    } sniffers;
    
    struct {
      NewPing *obj; //puntero al objeto que controla el sonar (es un puntero porque la clase NewPing tiene un constructor de mierda)
      int dist;     //la ultima distancia leida con el sonar
    } sonar;
    
    struct {
      Servo right(); //objeto que controla el motor derecho
      Servo left();  //objeto que controla el motor izquierdo
      int speedR;    //velocidad DESEADA del motor derecho, va desde -100 a +100
      int speedL;    //velocidad DESEADA del motor derecho, va desde -100 a +100
    } engines;
    
    int error; //codigo de error para cualquier operacion de SubnorBot
};

#endif //SUBNORBOT_H
