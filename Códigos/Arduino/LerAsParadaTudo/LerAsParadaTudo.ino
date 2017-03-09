#include <TaskScheduler.h>

#include "gps.h"
#include "driver.h"
#include "encoder.h"
#include "roscom.h"
#include "idsros.h"
#include "ultrassom.h"
#include "controlerc.h"
#include "tasksdeclarations.h"

// Aqui chegam as mensagens vindas do ROS -------------------

void messageInt64Cb( const raspberry_msgs::StampedInt64& r_int64_msg){

}

void messageFloat32Cb( const raspberry_msgs::StampedFloat32& r_float32_msg){
}

void messageFloat64Cb( const raspberry_msgs::StampedFloat64& r_float64_msg){
}

void taskGPSCallback(){
  leituraTinyGps();
}

void taskUSCallback1(){
  readUS(0);
  readUS(10);
}

void taskUSCallback2(){
  readUS(1);
  readUS(9);
}

void taskUSCallback3(){
  readUS(2);
  readUS(8);
}

void taskUSCallback4(){
  readUS(3);
  readUS(7);
}

void taskUSCallback5(){
  readUS(4);
  readUS(6);
}

void taskUSCallback6(){
  readUS(5);
}

void taskShowUSReadingCallback(){
  Serial.print("US Readings: ");
  Serial.println(millis());
  unsigned long t1 = millis();
  for(unsigned i=0; i<SONAR_NUM;i++){
    Serial.print("US ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(USReadings[i]);
    Serial.println("cm");
  }
  unsigned long t2 = millis();
  Serial.print("Demorei ");
  Serial.println(t2-t1); 
}

void taskROSCallback(){
  sendInt64(US01, USReadings[0]);
  sendInt64(US02, USReadings[1]);
  sendInt64(US03, USReadings[2]);
  sendInt64(US04, USReadings[3]);
  sendInt64(US05, USReadings[4]);
  sendInt64(US06, USReadings[5]);
  sendInt64(US07, USReadings[6]);
  sendInt64(US08, USReadings[7]);
  sendInt64(US09, USReadings[8]);
  sendInt64(US10, USReadings[9]);
  sendInt64(US11, USReadings[10]);

  sendFloat64(GPS_LAT,lat);
  sendFloat64(GPS_LON,lon);
  sendFloat64(GPS_ALT,alt);
  
}

void taskENCODERCallback(){
  //Serial.print("ENCODER: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  
  tempo_aux = millis() - tempo;
  tempo = millis();
  
  voltas_esquerda = encoder0Pos/1632.67;
  voltas_direita = encoder1Pos/1632.67;
 
  velocidade_esquerda = 1000*(voltas_esquerda - voltas_esquerda_anterior)/(tempo_aux);
  velocidade_direita = 1000*(voltas_direita - voltas_direita_anterior)/(tempo_aux);
  
  voltas_esquerda_anterior = voltas_esquerda;
  voltas_direita_anterior = voltas_direita;
  
  //Serial.print("tempo: ");                    Serial.println(tempo_aux);
  //Serial.print("Contador encoder esquerdo: "); Serial.println(encoder0Pos);
  //Serial.print("Contador encoder direito: ");  Serial.println(encoder1Pos);
  Serial.print("Velocidade esquerda: ");      Serial.println(velocidade_esquerda);
  Serial.print("Velocidade direita: ");       Serial.println(velocidade_direita);
  Serial.println(" ");
 // unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskRCCallback(){

  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(channel_value1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(channel_value2);
  Serial.print("Channel 3: ");
  Serial.println(channel_value3);
  
}

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  
  //initializeRosCom();

  start_DRIVER();

  start_ENCODER();

  start_RC();

  start_TASKS();
  
}

void loop() {

  
  // put your main code here, to run repeatedly:
  esquerda_eixo(50,50);
  runner.execute();
  //nh.spinOnce();
}
