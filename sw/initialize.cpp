#include "subnorbot.h"

int SubnorBot::initialize()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    
    return 0;
}
