#define IR_THRESHOLD 100
#define EDGE 1
#define NOEDGE 0

//#define WHITEFLOOR

boolean _IRmeasure(int IR_sensor_num);

void setup()
{
  Serial.begin(115200);// Open serial monitor at 115200 baud to see results.
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}
void loop()
{
  int numSensor=0;
  boolean borde=0;
    
  borde= _IRmeasure(numSensor);
  
  Serial.print("Valor del sensor: ");
  Serial.print(analogRead(numSensor));
  Serial.print("\t");
  
  Serial.print("Borde?: ");
  Serial.println(borde);
  
  
}

boolean _IRmeasure(int IR_sensor_num)
{
  
   int i=0;
   int measure = 0;
   boolean edge=0;
   
   delay(3000);
   
   digitalWrite(8, HIGH);
   delay(10);
   
   
   for (i=0; i<4; i++){
    measure+=analogRead(IR_sensor_num);
   }
   
   measure=measure/4; //mathematic mean of 4 measures
   
   if (measure<= IR_THRESHOLD)//if white detected
   {
     #ifdef WHITEFLOOR
     edge=NOEDGE;//NOEDGE=0
     #endif
     
     #ifndef WHITEFLOOR
     edge=EDGE;//EDGE=1
     #endif
     
   }
    else   //black detected
    {      //measure>IR_THRESHOLD

     #ifdef WHITEFLOOR
     edge=EDGE;//EDGE=1
     #endif
     
     #ifndef WHITEFLOOR
     edge=NOEDGE;//NOEDGE=0
     #endif
          
    }
    
    delay(1000);

    digitalWrite(8, LOW);
        
    return(edge);
}
