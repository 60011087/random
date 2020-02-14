#include <Arduino.h>
#define start_pin 2
#define delayMode3 500
#define delaymode3 100
const uint32_t totalTime = 10000; // ms
// const uint32_t step = 8;
const uint32_t TimePerStep1 = totalTime / 14;
const uint32_t TimePerStep2 = totalTime / 12;

const uint32_t TimePerStep = totalTime / 10;

typedef struct L
{
  int32_t pin;
  int32_t brightness = 255;
  int32_t startTime = 0;
  int32_t currentTime = 0;
  int32_t direction = 1;
  int32_t en = 1;
} LED;

LED l1, l2;

uint8_t mode = 0;

void(* resetFunc)(void) = 0;

void setup()
{
  // Serial.begin(9600);
  for (int i = 0; i < 8; i++)
  {
    pinMode(i + start_pin, OUTPUT);
    digitalWrite(i + start_pin, 255);
  }

  pinMode(A8, OUTPUT);
  pinMode(A9, OUTPUT);
  analogWrite(A8, 255);
  analogWrite(A9, 255);
  pinMode(A7, INPUT);
  pinMode(A6, INPUT);

  // delay(100);
  mode |= (digitalRead(A7) & 0x01) << 1 | (digitalRead(A6) & 0x01);

  Serial.print(mode,HEX);

  if (mode == 0)
  {
    l1.pin = 0;
    l1.brightness = 50;
    l2.pin = 2;
    l2.brightness = 200;

    analogWrite(0 + start_pin, 200);
    delay(TimePerStep2);
    analogWrite(0 + start_pin, 255);
    analogWrite(1 + start_pin, 200);
    delay(TimePerStep2);
    analogWrite(0 + start_pin, 50);
    analogWrite(1 + start_pin, 255);
    analogWrite(2 + start_pin, 200);
    delay(TimePerStep2);
  }
  else if (mode == 1)
  {
    l1.pin = 0;
    l1.brightness = 50;
    l1.direction = -1;
    l2.pin = 7;
    l2.direction = 1;
    l2.brightness = 200;
  }
  else
  {
    l1.pin = 0;
    l1.brightness = 255;
    // l1.direction = -1;
    // l2.pin = 7;
    // l2.direction = 1;
    // l2.brightness = 200;
  }
}

void loop()
{

  if (mode == 0)
  {
    if (l1.en && millis() - l1.startTime >= TimePerStep1)
    {
      if (l1.direction == -1 && l1.pin == 0)
      {
        l1.en = 0;
      }
      analogWrite(l1.pin + start_pin, 255);
      if (l1.pin == 7)
        l1.direction *= -1;
      l1.pin += l1.direction;
      l1.startTime = millis();
    }
    if (l2.en && millis() - l2.startTime >= TimePerStep2)
    {
      if (l2.direction == -1 && l2.pin == 0)
      {
        l2.en = 0;
      }
      analogWrite(l2.pin + start_pin, 255);
      if (l2.pin == 7)
        l2.direction *= -1;
      l2.pin += l2.direction;
      l2.startTime = millis();
    }

    if (l2.pin == l1.pin)
    {
      analogWrite(l2.pin + start_pin, 125); 
    }
    else
    {
      analogWrite(l2.pin + start_pin, l2.brightness * l2.en);
      analogWrite(l1.pin + start_pin, l1.brightness * l1.en);
    }

    if(l2.en == 0 && l2.en == 0){
      resetFunc();
    }
  }
  else if (mode == 1)
  {
    if (millis() - l1.startTime >= TimePerStep)
    {
      analogWrite(l1.pin + start_pin, 255);
      if (l1.pin == 7 || l1.pin == 0)
        l1.direction *= -1;
      l1.pin += l1.direction;
      l1.startTime = millis();
    }
    if (millis() - l2.startTime >= TimePerStep)
    {
      analogWrite(l2.pin + start_pin, 255);
      if (l2.pin == 7 || l2.pin == 0)
        l2.direction *= -1;
      l2.pin += l2.direction;
      l2.startTime = millis();
    }

    if (l2.pin == l1.pin)
    {
      analogWrite(l2.pin + start_pin, 125);
    }
    else
    {
      analogWrite(l2.pin + start_pin, l2.brightness * l2.en);
      analogWrite(l1.pin + start_pin, l1.brightness * l1.en);
    }
  }
  else
  {
    for(int8_t i = 0; i < 8 ;i++){
      analogWrite(i + start_pin,227 - (28*i));
      delay(delaymode3);
    }
    delay(delayMode3);
    for(int8_t i = 0; i < 8 ;i++){
      analogWrite(i + start_pin,255);
      delay(delaymode3);
    }
    delay(delayMode3);
    for(int8_t i = 7; i >= 0 ;i--){
      analogWrite(i + start_pin,227 - (28*(7-i)));
      delay(delaymode3);
    }
    delay(delayMode3);
    for(int8_t i = 7; i >= 0 ;i--){
      analogWrite(i + start_pin,255);
      delay(delaymode3);
    }
    delay(delayMode3);
    int8_t i,j;
    for(i = 0 ,j = 7; i <= 3 ;i++,j--){
      analogWrite(i + start_pin,204 - (i*51));
      analogWrite(j + start_pin,204 - (i*51));
      delay(delaymode3);
    }
    delay(delayMode3);
    for(i = 0 ,j = 7; i <= 3 ;i++,j--){
      analogWrite(i + start_pin,255);
      analogWrite(j + start_pin,255);
      delay(delaymode3);
    }
    delay(delayMode3);
    for(i = 3 ,j = 4; i >= 0 ;i--,j++){
      analogWrite(i + start_pin,204 - ((3-i)*51));
      analogWrite(j + start_pin,204 - ((j-4)*51));
      delay(delaymode3);
    }
    delay(delayMode3);
    for(i = 3 ,j = 4; i >= 0 ;i--,j++){
      analogWrite(i + start_pin,255);
      analogWrite(j + start_pin,255);
      delay(delaymode3);
    }
    delay(delayMode3);
  }
}
