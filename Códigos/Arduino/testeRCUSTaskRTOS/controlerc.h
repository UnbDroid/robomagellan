#ifndef CONTROLERC_H
#define CONTROLERC_H

#include "basicLibraries.h"

#define CHANNEL1 10//A13 // we could choose any pin
#define CHANNEL2 11//A14
#define CHANNEL3 12// A15

#define MAX_TIME_RC 2000
 
volatile long channel_value1 = 0;
volatile long prev_time1 = 0;
volatile long channel_value2 = 0;
volatile long prev_time2 = 0;
volatile long channel_value3 = 0;
volatile long prev_time3 = 0;
uint8_t latest_interrupted_pin1;
uint8_t latest_interrupted_pin2;
uint8_t latest_interrupted_pin3;

void falling1();
void falling2();
void falling3();
 
void rising1(){
  latest_interrupted_pin1=PCintPort::arduinoPin;
  if(latest_interrupted_pin1 == CHANNEL1){
    PCintPort::attachInterrupt(latest_interrupted_pin1, &falling1, FALLING);
    prev_time1 = micros();
  }

}

void rising2(){
  latest_interrupted_pin2=PCintPort::arduinoPin;
  if(latest_interrupted_pin2 == CHANNEL2){
    PCintPort::attachInterrupt(latest_interrupted_pin2, &falling2, FALLING);
    prev_time2 = micros();    
  }
}

void rising3(){
  latest_interrupted_pin3=PCintPort::arduinoPin;
  if(latest_interrupted_pin3 == CHANNEL3){
    PCintPort::attachInterrupt(latest_interrupted_pin3, &falling3, FALLING);
    prev_time3 = micros(); 
  }
}
 
void falling1() {
  latest_interrupted_pin1=PCintPort::arduinoPin;
  if(latest_interrupted_pin1 == CHANNEL1){
    PCintPort::attachInterrupt(latest_interrupted_pin1, &rising1, RISING);
    long temp = micros()-prev_time1;
    if(temp < MAX_TIME_RC){
      channel_value1 = temp;
    }
  }
}

void falling2() {
  latest_interrupted_pin2=PCintPort::arduinoPin;
  if(latest_interrupted_pin2 == CHANNEL2){
    PCintPort::attachInterrupt(latest_interrupted_pin2, &rising2, RISING);
    long temp = micros()-prev_time2;
    if(temp < MAX_TIME_RC){
      channel_value2 = temp;
    }
  }
}

void falling3() {
  latest_interrupted_pin3=PCintPort::arduinoPin;
  if(latest_interrupted_pin3 == CHANNEL3){
    PCintPort::attachInterrupt(latest_interrupted_pin3, &rising3, RISING);
    long temp = micros()-prev_time3;
    if(temp < MAX_TIME_RC){
      channel_value3 = temp;
    } 
  }
}
 
void startRC() {
  pinMode(CHANNEL1, INPUT); digitalWrite(CHANNEL1, HIGH);
  pinMode(CHANNEL2, INPUT); digitalWrite(CHANNEL2, HIGH); 
  pinMode(CHANNEL3, INPUT); digitalWrite(CHANNEL3, HIGH);  
  PCintPort::attachInterrupt(CHANNEL1, &rising1, RISING);
  PCintPort::attachInterrupt(CHANNEL2, &rising2, RISING);
  PCintPort::attachInterrupt(CHANNEL3, &rising3, RISING);
}

#endif
