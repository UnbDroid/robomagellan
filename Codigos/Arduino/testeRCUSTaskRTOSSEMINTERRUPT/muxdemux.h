#ifndef MUXDEMUX_H
#define MUXDEMUX_H

#define MUX_A A3
#define MUX_B A4
#define MUX_C A5
#define DEMUX_A A0
#define DEMUX_B A1
#define DEMUX_C A2

void startMUXDEMUX(){
  pinMode(MUX_A,OUTPUT);
  pinMode(MUX_B,OUTPUT);
  pinMode(MUX_C,OUTPUT);
  pinMode(DEMUX_A,OUTPUT);
  pinMode(DEMUX_B,OUTPUT);
  pinMode(DEMUX_C,OUTPUT);        
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

void chooseMUX8(uint8_t value){
  chooseMUXDEMUX8(value,MUX_A,MUX_B,MUX_C);
}

void chooseDEMUX8(uint8_t value){
  chooseMUXDEMUX8(value,DEMUX_A,DEMUX_B,DEMUX_C);
}
#endif
