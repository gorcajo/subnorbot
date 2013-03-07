#include "subnorbot.h"

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

