#ifndef ULTRASSOM_H
#define ULTRASSOM_H

#include "basicLibraries.h"

#define TRIGGER_1 A10
#define TRIGGER_2 A11
#define ECHO A12
#define NUM_US 2

TaskHandle_t USTaskHandle;

volatile long tempo_us = 0;
volatile long prev_timeUS = 0;
uint8_t latest_interrupted_pinUS;
volatile int us[NUM_US];
int usTrigger[NUM_US] = {TRIGGER_1, TRIGGER_2};

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
  pinMode(ECHO, INPUT);
  digitalWrite(ECHO, HIGH);
  for(int i = 0;i<NUM_US;i++){
    pinMode(usTrigger[i],OUTPUT);
    digitalWrite(usTrigger[i],LOW);
  }
  PCintPort::attachInterrupt(ECHO, &risingUS, RISING);
}

static void TaskUS(void* pvParameters){
  int ordemLeitura[NUM_US] = {0, 1};
  for (;;){ 
    for(int i=0;i<NUM_US;i++){
      trigger(usTrigger[ordemLeitura[i]]);
      vTaskDelay(50/ portTICK_PERIOD_MS);
      us[i] = tempo_us/29/2;
    }
  }
}

void risingUS(){
  latest_interrupted_pinUS=PCintPort::arduinoPin;
  if(latest_interrupted_pinUS==ECHO){
    PCintPort::attachInterrupt(latest_interrupted_pinUS, &fallingUS, FALLING);
    prev_timeUS = micros();
  }
}

void fallingUS() {
  latest_interrupted_pinUS=PCintPort::arduinoPin;
  if(latest_interrupted_pinUS==ECHO){
    PCintPort::attachInterrupt(latest_interrupted_pinUS, &risingUS, RISING);
    long temp = micros()-prev_timeUS;
    if(temp < 30000){
      tempo_us = temp;
    }
  }
}

#endif
