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

#define dutyT 10000
#define limit_duty_count 17
uint32_t start[8] = {};
uint32_t dutyTime = dutyT; // us
uint32_t dutyTime_divied = dutyT/100;
uint32_t b = 5;
uint32_t direction = 1;
uint8_t count = 0;

uint8_t status[8] = {};

void loop()
{
    for(uint8_t i = 0; i < 8; i++){
      if(micros() <= start[i] + dutyTime){
        if( micros() <= dutyTime_divied * b + start[i]){
          if(status[i] == 0){
            digitalWrite(i+start_pin,LOW);
            status[i] = 1;
          }
          
        }
        else{
          if(status[i] == 1){
            digitalWrite(i+start_pin,HIGH);
            status[i] = 0;
          }
        }
      }
      else{
        count++;
        if(count == limit_duty_count){
          if(b == MAX_BRIGHT || b == MIN_BRIGHT){
            direction *= -1;
          }
          b += direction;
          count = 0;
        }
        start[i] = micros();
      }
    }
}


// int steplight[11] = {0,0,0,0,0,0,0,0,0,0,0} ,statuslight[11] = {0,0,0,0,0,0,0,0,0,0,0} ,stepfix = 101;
// float speedlight = 70;
// unsigned long time_now[11] = {0,0,0,0,0,0,0,0,0,0,0} ,timedutycircle = 1010000/speedlight ,n = timedutycircle/stepfix;
// void led(int pinout){
//   if(micros() >= time_now[pinout] + timedutycircle){
//         time_now[pinout] += timedutycircle;
//         if(statuslight[pinout]==0) 
//           digitalWrite(pinout,LOW);
//         else 
//           digitalWrite(pinout,HIGH);
//         steplight[pinout]++;
//         if(steplight[pinout]==stepfix+1){
//           if(statuslight[pinout]==0) 
//             statuslight[pinout] = 1;
//           else 
//             statuslight[pinout] = 0;
//          steplight[pinout] = 0;
//         }
//   }
//   if(micros() >= time_now[pinout] + n*steplight[pinout]){
//         if(statuslight[pinout]==0) digitalWrite(pinout,HIGH);
//         else digitalWrite(pinout,LOW);
//   }
// }

// void setup() {
//   for(int i=2;i<=10;i++)  pinMode(i, OUTPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   for(int i=2;i<=10;i++)  led(i);
// }