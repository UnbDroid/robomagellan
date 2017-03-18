#ifndef MUXDEMUX_H
#define MUXDEMUX_H

#define MUX_A A3
#define MUX_B A4
#define MUX_C A5
#define MUX_A1 A6
#define MUX_B1 A7
#define MUX_C1 A8

#define DEMUX_A A0
#define DEMUX_B A1
#define DEMUX_C A2
#define DEMUX_A1 A10
#define DEMUX_B1 A11
#define DEMUX_C1 A12


void startMUXDEMUX8(){
  pinMode(MUX_A,OUTPUT);
  pinMode(MUX_B,OUTPUT);
  pinMode(MUX_C,OUTPUT);
  pinMode(DEMUX_A,OUTPUT);
  pinMode(DEMUX_B,OUTPUT);
  pinMode(DEMUX_C,OUTPUT);        
}

void startMUXDEMUX15(){
  pinMode(MUX_A,OUTPUT);
  pinMode(MUX_B,OUTPUT);
  pinMode(MUX_C,OUTPUT);
  pinMode(DEMUX_A,OUTPUT);
  pinMode(DEMUX_B,OUTPUT);
  pinMode(DEMUX_C,OUTPUT);
  pinMode(MUX_A1,OUTPUT);
  pinMode(MUX_B1,OUTPUT);
  pinMode(MUX_C1,OUTPUT);
  pinMode(DEMUX_A1,OUTPUT);
  pinMode(DEMUX_B1,OUTPUT);
  pinMode(DEMUX_C1,OUTPUT);        
}

void chooseMUXDEMUX8(uint8_t value, uint8_t port1, uint8_t port2, uint8_t port3){
  switch(value){
    case 0:
      digitalWrite(port1,LOW);
      digitalWrite(port2,LOW);
      digitalWrite(port3,LOW);
    break;
    case 1:
      digitalWrite(port1,HIGH);
      digitalWrite(port2,LOW);
      digitalWrite(port3,LOW);
    break;
    case 2:
      digitalWrite(port1,LOW);
      digitalWrite(port2,HIGH);
      digitalWrite(port3,LOW);
    break;
    case 3:
      digitalWrite(port1,HIGH);
      digitalWrite(port2,HIGH);
      digitalWrite(port3,LOW);
    break;
    case 4:
      digitalWrite(port1,LOW);
      digitalWrite(port2,LOW);
      digitalWrite(port3,HIGH);
    break;
    case 5:
      digitalWrite(port1,HIGH);
      digitalWrite(port2,LOW);
      digitalWrite(port3,HIGH);
    break;
    case 6:
      digitalWrite(port1,LOW);
      digitalWrite(port2,HIGH);
      digitalWrite(port3,HIGH);
    break;
    case 7:
      digitalWrite(port1,HIGH);
      digitalWrite(port2,HIGH);
      digitalWrite(port3,HIGH);
    break;
    default:
    break; 
  }  
}

void chooseMUXDEMUX15(uint8_t value, uint8_t port1, uint8_t port2, uint8_t port3, uint8_t port4, uint8_t port5, uint8_t port6){
  switch(value){
    case 0:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 1:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 2:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 3:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 4:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 5:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 6:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 7:
      chooseMUXDEMUX8(value,port1,port2,port3);
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 8:
      digitalWrite(port4,LOW);
      digitalWrite(port5,LOW);
      digitalWrite(port6,LOW);
    break;
    case 9:
      digitalWrite(port4,HIGH);
      digitalWrite(port5,LOW);
      digitalWrite(port6,LOW);
    break;
    case 10:
      digitalWrite(port4,LOW);
      digitalWrite(port5,HIGH);
      digitalWrite(port6,LOW);
    break;
    case 11:
      digitalWrite(port4,HIGH);
      digitalWrite(port5,HIGH);
      digitalWrite(port6,LOW);
    break;
    case 12:
      digitalWrite(port4,HIGH);
      digitalWrite(port5,LOW);
      digitalWrite(port6,HIGH);
    break;
    case 13:
      digitalWrite(port4,LOW);
      digitalWrite(port5,HIGH);
      digitalWrite(port6,HIGH);
    break;
    case 14:
      digitalWrite(port4,HIGH);
      digitalWrite(port5,HIGH);
      digitalWrite(port6,HIGH);
    break;
    default:
    break; 
  }  
}

void chooseMUX8(uint8_t value){
  chooseMUXDEMUX8(value,MUX_A,MUX_B,MUX_C);
}

void chooseMUX15(uint8_t value){
  chooseMUXDEMUX15(value,MUX_A,MUX_B,MUX_C,MUX_A1,MUX_B1,MUX_C1);
}

void chooseDEMUX8(uint8_t value){
  chooseMUXDEMUX8(value,DEMUX_A,DEMUX_B,DEMUX_C);
}

void chooseDEMUX15(uint8_t value){
  chooseMUXDEMUX15(value,DEMUX_A,DEMUX_B,DEMUX_C,DEMUX_A1,DEMUX_B1,DEMUX_C1);
}

#endif
