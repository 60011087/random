#include <Arduino.h>
#define LED_BuildIn 13

uint32_t time_slot = 1000;    // us 500 = max speed 
uint32_t start_time = 0;      // us
uint32_t brightness = 100;    // percentage
uint32_t start_time_ch = 0;
uint32_t time_to_charge = 50000 ; //us
int32_t charge_direction = 1; // 1 = up , -1 = down

uint8_t current_led;
void LED8_setup()
{
  Serial.begin(9600);
  pinMode(LED_BuildIn, OUTPUT);

  for (uint8_t i = 4; i <= 10; i++)
  {
    pinMode(i, OUTPUT);
  }
  current_led = 0;

  start_time = micros();
}

void LED8_loop()
{
  if (micros() - start_time_ch > time_to_charge)
  {
    if (brightness == 0 || brightness == 100)
    {
      charge_direction *= -1;
    }
    brightness += charge_direction;
    // Serial.println(brightness);
    start_time_ch = micros();
    // digitalWrite(LED_BuildIn, !digitalRead(LED_BuildIn));
  }

  if (micros() - start_time > time_slot * brightness / 100)
  {
    digitalWrite(current_led + 4, LOW);
  }

  if (micros() - start_time > time_slot)
  {
    digitalWrite(current_led + 4, LOW);
    current_led++;
    current_led %= 7;
    digitalWrite(current_led + 4, HIGH);
    start_time = micros();
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