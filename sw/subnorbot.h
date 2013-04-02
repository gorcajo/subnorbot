#ifndef SUBNORBOT_H
#define SUBNORBOT_H

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

/** Constantes, centralizadas aqui */
//Para realizar pruebas
#define TEST
//Tiempo, en milisegundos, de la espera inicial al arranque:
#define IDLE_TIME 5000
//Pines de los siguelineas:
#define PIN_SNIFFER_NE  2
#define PIN_SNIFFER_SE  3
#define PIN_SNIFFER_SW  4
#define PIN_SNIFFER_NW  5
//Pines del sonar:
#define PIN_SONAR_TRIGGER 11
#define PIN_SONAR_ECHO    12
//Diametro del ring:
#define DOJO_DIAMMETER    75
//Bara los barridos del estado REFINDING, de la maquina de estados en SubnorBot.resolve()
#define SWEEPS 6        //numero de barridos en el estado REFINDING
#define SWEEP_TIME 2000 //tiempo de cada barrido, en milisegundos
//Pines de los PWMs de los motores:
#define PIN_ENGINE_R 9
#define PIN_ENGINE_L 10
//Pines del LED RGB indicador de estado:
#define PIN_LED_R 6
#define PIN_LED_G 7
#define PIN_LED_B 8
//Correcion de la diferencia de velocidad de los motores, para todos los movimientos (avanzar, girar, etc)
//(numero entre 0 y 1 que multiplica a la velocidad de ambos motores):
#define LEFT_SPEED_CORRECTION 1
#define RIGHT_SPEED_CORRECTION 1

/** Tipo Side
 *
 * Para definir los laterales.
 *
 */
typedef enum {
  LEFT,
  RIGHT
} Side;

/** Tipo State
 *
 * Para definir los estados de la maquina de estados correspondiente a la IA
 *
 */
typedef enum {
  IDLE,         //estado de reposo, cuando aun no se ha ejecutado ninguna vez la maquina de estados
  SEARCHING,    //gira sobre si mismo buscando al rival
  CHARGING,     //se dirige hacia el rival y le empuja a toda velocidad
  REFINDING,    //cuando se pierde de vista al rival, realizara una busqueda barriendo en un cono de accion, durante un tiempo limitado
  AVOIDING_EDGE //corrige la posicion en el caso de encontrar un borde
} State;

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
    
    //Metodos relacionados con la IA (implementados en resolve.cpp):
    void rotate(Side side);  //rotacion sobre si mismo, destinado a buscar al rival
    void pivot(Side side);   //pivotar hacia la derecha (sobre una rueda), destinado a maniobrar en contacto con el rival
    void goAhead(int speed); //carga y empuje contra el rival a toda velocidad
    
    //Metodos relacionados con los motores y actuadores (implementados en move.cpp):
    void setSpeed(int l, int r); //Establece una velocidad DESEADA, en ambos motores, los parametros -100 a +100
    void setLED();               //Establece un color de 3 bits de profundidad en el LED RGB, segun el estado de la maquina de estados de la IA

  private:
  union {
    struct {        //bitfield que ocupa un byte (1 = borde detectado)
      char ne : 1; //bit (LSB) correspondiente al sensor frontal derecho
      char se : 1; //bit correspondiente al sensor trasero derecho
      char sw : 1; //bit correspondiente al sensor trasero izquierdo
      char nw : 1; //bit correspondiente al sensor frontal izquierdo
    } bits;
    char byte; //para acceder al byte entero del bitfield
    char any;  //la misma forma de acceder al bitfield pero con otro nombre, por legibilidad del codigo
  } sniffers;
    
    struct {
      NewPing *obj; //puntero al objeto que controla el sonar (es un puntero porque la clase NewPing tiene un constructor de mierda)
      int dist;     //la ultima distancia leida con el sonar
    } sonar;
    
    struct {
      Servo left;  //objeto que controla el motor izquierdo
      Servo right; //objeto que controla el motor derecho
      int speedL;  //velocidad DESEADA del motor izquierdo, va desde 0 a 180
      int speedR;  //velocidad DESEADA del motor derecho, va desde 0 a 180
    } engines;
    
    State state; //el estado de la maquina de estados de la IA
    int error;   //codigo de error para cualquier operacion de SubnorBot
};

#endif //SUBNORBOT_H
