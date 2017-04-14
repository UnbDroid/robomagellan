#ifndef BOTOES_H
#define BOTOES_H

#define pinButtonVerde A4
#define pinButtonPreto A3

int botaoVerde;
int botaoPreto;

void startBotoes(){
  pinMode(pinButtonVerde,INPUT);
  pinMode(pinButtonPreto,INPUT);
}

int lerBotaoVerde(){
  return digitalRead(pinButtonVerde);
}

int lerBotaoPreto(){
  return digitalRead(pinButtonPreto);
}

#endif
