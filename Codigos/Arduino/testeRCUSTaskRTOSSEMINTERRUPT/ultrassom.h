#ifndef ULTRASSOM_H
#define ULTRASSOM_H

#include "basicLibraries.h"
#include "muxdemux.h"

#define TRIGGER1 9 
#define ECHO1 8
#define TRIGGER2 7 
#define ECHO2 6
#define NUM_US 2

TaskHandle_t USTaskHandle;

volatile long tempo_us = 0;
volatile long prev_timeUS = 0;
uint8_t latest_interrupted_pinUS;
volatile int us[NUM_US];
int usTrigger[NUM_US] = {TRIGGER1, TRIGGER2};
int usEcho[NUM_US] = {ECHO1, ECHO2};

void fallingUS();
void risingUS();
void trigger(int pin);
static void TaskUS(void* pvParameters);

void trigger(int pin){
  digitalWrite(pin,LOW);
  delayMicroseconds(4);
  digitalWrite(pin,HIGH);
  delayMicroseconds(10);    
  digitalWrite(pin,LOW); 
}

void startUS(){
  pinMode(ECHO1, INPUT);
  pinMode(TRIGGER1,OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIGGER2,OUTPUT);
  //PCintPort::attachInterrupt(ECHO, &risingUS, RISING);
}

static void TaskUS(void* pvParameters){
  int ordemLeitura[NUM_US] = {0, 1};
  for (;;){ 
    for(int i=0;i<NUM_US;i++){
      trigger(usTrigger[ordemLeitura[i]]);
      while(!digitalRead(usEcho[ordemLeitura[i]])){
        //vTaskDelay(1);
      }
      long tempo1 = micros();
      while(digitalRead(usEcho[ordemLeitura[i]])){
        vTaskDelay(1);
      }
      long tempo_us1 = micros() - tempo1;
      us[i] = tempo_us1/29/2;
      //Serial.println(tempo_us1);
      //Serial.println(i);
      //Serial.println(us[i]);
    }
  }
}


#endif
