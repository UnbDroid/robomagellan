#ifndef ENCODER_H
#define ENCODER_H

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 
EasyTransfer ET2; 

struct VELOCIDADES_REFERENCIA_RAW{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t dir;
  int16_t esq;
};

struct VELOCIDADES_ATUAIS_RAW{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t dir;
  int16_t esq;
};

struct VELOCIDADES_REFERENCIA{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float dir;
  float esq;
};

struct VELOCIDADES_ATUAIS{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  float dir;
  float esq;
};


VELOCIDADES_REFERENCIA_RAW velRefRaw;
VELOCIDADES_ATUAIS_RAW velAtualRaw;
VELOCIDADES_REFERENCIA velRef;
VELOCIDADES_ATUAIS velAtual;

int16_t vel2Raw(float vel){
  return (int16_t)(vel* 100);
}

float velFromRaw(int16_t vel){
  return ((float)vel)/100.0; 
}

void start_ENCODER () {
  Serial3.begin(9600);
  velRef.dir = 1.2;
  velRef.esq = 1.2;
  velAtual.dir = 0;
  velAtual.esq = 0;
  ET.begin(details(velRefRaw), &Serial3);
  ET2.begin(details(velAtualRaw), &Serial3);
}

#endif
