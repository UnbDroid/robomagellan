#ifndef ULTRASSOM_H
#define ULTRASSOM_H

#include "basicLibraries.h"

#define TRIGGER_1 A10
#define TRIGGER_2 A11
#define ECHO_1 A12
#define NUM_US 2

TaskHandle_t USTaskHandle;
volatile int tempo_us = 0;
volatile int prev_time = 0;
uint8_t latest_interrupted_pin1;
volatile int us[NUM_US];
int usTrigger[NUM_US] = {TRIGGER_1, TRIGGER_2};

void falling1();
void rising1();
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
  pinMode(ECHO_1, INPUT);
  digitalWrite(ECHO_1, HIGH);
  for(int i = 0;i<NUM_US;i++){
    pinMode(usTrigger[i],OUTPUT);
    digitalWrite(usTrigger[i],LOW);
  }
  PCintPort::attachInterrupt(ECHO_1, &rising1, RISING);
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

void rising1(){
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &falling1, FALLING);
  prev_time = micros();
}

void falling1() {
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &rising1, RISING);
  tempo_us = micros()-prev_time;
}

#endif
