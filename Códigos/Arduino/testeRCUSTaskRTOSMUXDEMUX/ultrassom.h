#ifndef ULTRASSOM_H
#define ULTRASSOM_H

#include "basicLibraries.h"
#include "muxdemux.h"

#define TRIGGER 14
#define ECHO 15
#define NUM_US 2

TaskHandle_t USTaskHandle;

volatile long tempo_us = 0;
volatile long prev_timeUS = 0;
uint8_t latest_interrupted_pinUS;
volatile int us[NUM_US];
int usTrigger[NUM_US] = {0, 1};

void fallingUS();
void risingUS();
void trigger(int pin);
static void TaskUS(void* pvParameters);

void trigger(int pin){
  noInterrupts();
  chooseMUX8(pin);
  chooseDEMUX8(pin);
  //Serial.println("T");
  digitalWrite(TRIGGER,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIGGER,HIGH);
  delayMicroseconds(10);    
  digitalWrite(TRIGGER,LOW); 
  interrupts();
}

void startUS(){
  pinMode(ECHO, INPUT);
  digitalWrite(ECHO, HIGH);
  
  pinMode(TRIGGER,OUTPUT);
  digitalWrite(TRIGGER,LOW);
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
  //Serial.println("R");
  latest_interrupted_pinUS=PCintPort::arduinoPin;
  if(latest_interrupted_pinUS==ECHO){
    PCintPort::attachInterrupt(latest_interrupted_pinUS, &fallingUS, FALLING);
    tempo_us = 0;
    prev_timeUS = micros();
  }
}

void fallingUS() {
  //Serial.println("F");
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
