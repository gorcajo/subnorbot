#ifndef SUBNORBOT_H
#define SUBNORBOT_H

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

/** Constantes */
//Siguelineas:
#define PIN_SNIFFER_NE  4
#define PIN_SNIFFER_SE  5
#define PIN_SNIFFER_SW  6
#define PIN_SNIFFER_NW  7
#define PIN_SNIFFER_INT 8
//Ultrasonidos:
#define PIN_SONAR_TRIGGER 2
#define PIN_SONAR_ECHO    3
#define DOJO_DIAMMETER    75
//Motores:
#define PIN_ENGINE_R 9
#define PIN_ENGINE_L 10

/** Tipos */
typedef enum {RIGHT, LEFT} Side;

/** Clase SubnorBot
 *
 * Manejo completo del robot. Su unica instancia se realiza como variable
 * global en el fichero fuente principal (sw.ino).
 *
 * Esta clase no tiene constructor (el compilador le asignara un
 * constructor por defecto, vacio) ni destructor.
 *
 */
class SubnorBot {
  public:
    //Housekeeping (metodos ejecutados en el setup() de Arduino):
    void initialize(); //realiza todas las configuraciones iniciales
    
    //Main loop (metodos ejecutados en el loop() de Arduino):
    void sense();   //Encargado de realizar todas las adquisiciones del exterior y ofrecer informacion util
    void resolve(); //Procesa la informacion de sense() y toma decisiones
    void move();    //Segun las decisiones de resolve() realiza el manejo de los motores
    
    //Metodos relacionados con los sensores (implementados en sense.cpp):
    void setSniffers(boolean _ne, boolean _se, boolean _sw, boolean _nw); //almacena el estado de los siguelineas
    
    //Metodos relacionados con la IA (implementados en resolve.cpp):
    void rotate(Side side); //rotacion sobre si mismo
    void pivot(Side side);  //pivotar hacia la derecha (sobre una rueda)
    void approach();         //acercamiento a baja velocidad al rival
    void charge();          //carga y empuje contra el rival a toda velocidad
    
    //Metodos relacionados con los motores (implementados en move.cpp):
    void setSpeed(int l, int r); //Establece una velocidad en ambos motores

  private:
    struct {        //bitfield que ocupa un byte (1 = borde detectado)
      char ne  : 1; //bit correspondiente al sensor frontal derecho
      char se  : 1; //bit correspondiente al sensor trasero derecho
      char sw  : 1; //bit correspondiente al sensor trasero izquierdo
      char nw  : 1; //bit correspondiente al sensor frontal izquierdo
      char any : 1; //la OR de los demas bits
    } sniffers;
    
    struct {
      NewPing *obj; //puntero al objeto que controla el sonar (es un puntero porque la clase NewPing tiene un constructor de mierda)
      int dist;     //la ultima distancia leida con el sonar
    } sonar;
    
    struct {
      Servo left;  //objeto que controla el motor izquierdo
      Servo right; //objeto que controla el motor derecho
      int speedL;  //velocidad DESEADA del motor izquierdo, va desde -100 a +100
      int speedR;  //velocidad DESEADA del motor derecho, va desde -100 a +100
    } engines;
    
    int error; //codigo de error para cualquier operacion de SubnorBot
};

#endif //SUBNORBOT_H
