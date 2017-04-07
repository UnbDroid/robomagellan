#ifndef CONTROLERC_H
#define CONTROLERC_H

#include <PinChangeInt.h>

#define CHANNEL1 A15 // we could choose any pin
#define CHANNEL2 A14
#define CHANNEL3 A13
 
volatile int channel_value1 = 0;
volatile int prev_time1 = 0;
volatile int channel_value2 = 0;
volatile int prev_time2 = 0;
volatile int channel_value3 = 0;
volatile int prev_time3 = 0;
uint8_t latest_interrupted_pin1;
uint8_t latest_interrupted_pin2;
uint8_t latest_interrupted_pin3;

void falling1();
void falling2();
void falling3();
 
void rising1()
{
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &falling1, FALLING);
  prev_time1 = micros();
}

void rising2()
{
  latest_interrupted_pin2=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin2, &falling2, FALLING);
  prev_time2 = micros();
}

void rising3()
{
  latest_interrupted_pin3=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin3, &falling3, FALLING);
  prev_time3 = micros();
}
 
void falling1() {
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &rising1, RISING);
  channel_value1 = micros()-prev_time1;
}

void falling2() {
  latest_interrupted_pin2=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin2, &rising2, RISING);
  channel_value2 = micros()-prev_time2;
}

void falling3() {
  latest_interrupted_pin3=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin3, &rising3, RISING);
  channel_value3 = micros()-prev_time3;
}
 
void start_RC() {
  pinMode(CHANNEL1, INPUT); digitalWrite(CHANNEL1, HIGH);
  pinMode(CHANNEL2, INPUT); digitalWrite(CHANNEL2, HIGH); 
  pinMode(CHANNEL3, INPUT); digitalWrite(CHANNEL3, HIGH);  
  PCintPort::attachInterrupt(CHANNEL1, &rising1, RISING);
  PCintPort::attachInterrupt(CHANNEL2, &rising2, RISING);
  PCintPort::attachInterrupt(CHANNEL3, &rising3, RISING);
}

void processarControleRC(float & velDir, float & velEsq){
  bool controlar = (channel_value1 > 1500);
  if(controlar){
    velDir = (channel_value2-1338.0)/2000.0*10.0;
    velEsq = velDir;
    float guinada = (((channel_value3-1440.0)/(2000.0*0.24)))*2;
    if(abs(velDir) < 0.5){
      velDir = 0;
    }else if(velDir > 0.5){
      velDir += 3;
    }else if(velDir < -0.5){
      velDir -= 3;
    }
    
    if(abs(velEsq) < 0.5){
      velEsq = 0;
    }else if(velEsq > 0.5){
      velEsq += 3;
    }else if(velEsq < -0.5){
      velEsq -= 3;
    }
  
    if(abs(guinada) < 0.10){
      guinada = 0;
    }
    if(guinada > 0){
      velEsq *= (1-guinada);
    }else if(guinada < 0){
      velDir *= (1+guinada);
    }    
  }
}

#endif
