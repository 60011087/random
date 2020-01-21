#include <Arduino.h>
#define LED_BuildIn 13
#define MAX_BRIGHT 100 // percentage
#define MIN_BRIGHT 0   // percentage

uint32_t start_time[8] = {};
uint32_t max_time = 10000;                             // us
uint32_t bright[8] = {10, 20, 15, 40, 65, 60, 70, 100}; // percentage

uint32_t start_ = 0;    // us
uint32_t time_ = 20000; // us
int8_t di[8] = {1, -1, 1, -1, 1, -1, 1, 1};

void LED8_setup()
{
  Serial.begin(9600);
  pinMode(LED_BuildIn, OUTPUT);
  for (uint8_t i = 3; i <= 10; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void LED8_loop()
{
  // uint32_t uptime = ;
  for (uint8_t i = 0; i < 8; i++)
  {
    if (micros() - start_time[i] <= max_time * bright[i] / 100)
    {
      digitalWrite(i + 3, HIGH);
    }
    else
    {
      digitalWrite(i + 3, LOW);
    }
    if (micros() - start_time[i] >= max_time)
    {
      start_time[i] = micros();
    }
  }

  if (micros() - start_ > time_)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      if (bright[i] == MAX_BRIGHT || bright[i] == MIN_BRIGHT)
      {
        di[i] *= -1;
      }
      bright[i] += di[i];
    }
    start_ = micros();
  }
}

void setup()
{
  LED8_setup();
}

void loop()
{
  LED8_loop();
}