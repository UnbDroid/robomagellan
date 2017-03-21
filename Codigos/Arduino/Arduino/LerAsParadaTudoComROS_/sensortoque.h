#ifndef SENSORDETOQUE_H
#define SENSORDETOQUE_H

#define pinST A5

int sensorToque;

void startSENSORTOQUE(){
  pinMode(pinST,INPUT);
}

int lerSensorToque(){
  return digitalRead(pinST);
}

#endif
