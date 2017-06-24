#ifndef SINALLUMINOSO_H
#define SINALLUMINOSO_H

#define pinSINAL_LUMINOSO 3

void startSINALLUMINOSO(){
  pinMode(pinSINAL_LUMINOSO,OUTPUT);
}

void acenderSinalLuminoso(){
  digitalWrite(pinSINAL_LUMINOSO,HIGH);
}

void apagarSinalLuminoso(){
  return digitalWrite(pinSINAL_LUMINOSO,LOW);
}

#endif
