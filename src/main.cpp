#include <Arduino.h>
#define LED_BuildIn 13
#define MAX_BRIGHT 100 // percentage
#define MIN_BRIGHT 0   // percentage
#define start_pin 3
void setup()
{
  for(int i = 0 ; i < 8 ; i++){
    pinMode(i+start_pin, OUTPUT);
  }
}


void loop()
{
    
}


