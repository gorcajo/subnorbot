#ifndef SUBNORBOT_H
#define SUBNORBOT_H

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

/** Constantes, centralizadas aqui */
//Para realizar pruebas
//#define TEST
//Tiempo, en milisegundos, de la espera inicial al arranque:
#ifdef TEST
  #define IDLE_TIME 500
#else
  #define IDLE_TIME 5000
#endif
//Pines de los siguelineas:
#define PIN_SNIFFER_FL 2
#define PIN_SNIFFER_FR 1
#define PIN_SNIFFER_R  0
//Mas sobre los sniffers:
//#define WHITEFLOOR //invierte suelo/borde negro/blanco, si no esta definido el suelo es negro y el blorde blanco
#define IR_THRESHOLD 100
#define EDGE   1
#define NOEDGE 0
//Pines del sonar:
#define PIN_SONAR_TRIGGER 6
#define PIN_SONAR_ECHO    11
//Diametro del ring:
#define DOYO_DIAMMETER 76
//Mas sobre el sonar:
#define NUM_OF_SHOTS 5
//Bara los barridos del estado REFINDING, de la maquina de estados en SubnorBot.resolve():
#define SWEEPS 6        //numero de barridos en el estado REFINDING
#define SWEEP_TIME 500  //tiempo de cada barrido, en milisegundos
//Bara las maniobras de reposicionamiento al encontrar un borde, en la maquina de estados en SubnorBot.resolve():
#define GIVING_BACK     1500 //tiempo de pivotaje para dar la espalda al borde
#define GIVING_SEMIBACK 1000 //tiempo de pivotaje para dar la espalda al borde parcialmente (mas que nada porque no sabemos la posicion actual)
#define TURNING         750  //tiempo de rotacin para dar la espalda al borde
//Pines de los PWMs de los motores:
#define PIN_ENGINE_L 9
#define PIN_ENGINE_R 10
//Pines del LED RGB indicador de estado:
#define PIN_LED_R 2
#define PIN_LED_G 3
#define PIN_LED_B 4
//Correcion de la diferencia de velocidad de los motores, para todos los movimientos (avanzar, girar, etc),
//tambien vale para corregir el sentido de giro de los motores, segun el montaje fisico de los mismos
//(numero entre -1 y 1 que multiplica a la velocidad de ambos motores):
#define LEFT_SPEED_CORRECTION -0.95
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
  SEARCHING,    //estado inicial, gira sobre si mismo buscando al rival
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
    void rotate(Side _side);           //rotacion sobre si mismo, destinado a buscar al rival
    void pivot(Side _side);            //pivotar hacia la derecha (sobre una rueda), destinado a maniobrar en contacto con el rival
    void forward(unsigned int _speed); //avance
    void reverse(unsigned int _speed); //retroceso
    
    //Metodos relacionados con los motores y actuadores (implementados en move.cpp):
    void setSpeed(int _l, int _r); //Establece una velocidad DESEADA, en ambos motores, los parametros -100 a +100
    void updateLED();               //Establece un color de 3 bits de profundidad en el LED RGB, segun el estado de la maquina de estados de la IA
    
#ifdef TEST
    //Metodos unicamente para el modo test:
    void setDistance(int _d);  //fuerza una distancia determinada al rival en el sonar
    void switchSniffers(boolean _fl, boolean _fr, boolean _r);  //fuerza una conmutacion en el estado de los siguelineas
    boolean getSnifferFL();   //devuelve el estado del siguelineas frontal izquierdo
    boolean getSnifferFR();   //devuelve el estado del siguelineas frontal derecho
    boolean getSnifferR();    //devuelve el estado del siguelineas trasero
    State getState();         //devuelve el estado de la maquina de estados de la IA
    int getSpeed(Side _side); //devuelve la velocidad, entre -100 y 100, de uno de los motores
    int getAngle(Side _side); //devuelve la velocidad, entre 0 y 180, de uno de los motores
#endif

  private:
  union {
    struct { //bitfield que ocupa un byte (1 = borde detectado)
      char fl : 1; //bit (LSB) correspondiente al sensor frontal derecho
      char fr : 1; //bit correspondiente al sensor frontal izquierdo
      char r  : 1; //bit correspondiente al sensor trasero
      char pivotingL : 1; //bit que indica que se esta realizando un pivotaje a izquierdas para alejarse del borde
      char pivotingR : 1; //bit que indica que se esta realizando un pivotaje a derechas para alejarse del borde
      char turning   : 1; //bit que indica que se esta realizando una rotacion sobre el eje para alejarse del borde
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
