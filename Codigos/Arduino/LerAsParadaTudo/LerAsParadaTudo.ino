#include <TaskScheduler.h>

#include "gps.h"
#include "comArduino.h"
#include "roscom.h"
#include "idsros.h"
#include "ultrassom.h"
#include "controlerc.h"
#include "sensortoque.h"
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
  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(channel_value1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(channel_value2);
  Serial.print("Mandei:"); Serial.println(velRef.dir);
  Serial.print("Mandei:"); Serial.println(velRef.esq);
  Serial.print("Channel 3: ");
  Serial.println(channel_value3);
  Serial.print("Toque: ");      Serial.println(sensorToque);
  Serial.print("Vel esq: "); Serial.println(velAtual.esq);
  Serial.print("Vel dir: "); Serial.println(velAtual.dir);
  unsigned long t2 = millis();
  Serial.print("Demorei ");
  Serial.println(t2-t1);
  Serial.println(" ");    
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

void taskBotaoCallback(){
  sensorToque = lerSensorToque();
}
void taskComArduinoCallback(){
  processarControleRC(velRef.dir,velRef.esq);
  
  velRefRaw.dir = vel2Raw(velRef.dir);
  velRefRaw.esq = vel2Raw(velRef.esq);
  
  ET.sendData();
  if(ET2.receiveData()){
    velAtual.dir = velFromRaw(velAtualRaw.dir);
    velAtual.esq = velFromRaw(velAtualRaw.esq);
  }
    
}

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  delay(1000);
  //initializeRosCom();

  start_COMARDUINO();

  start_RC();

  start_TASKS();
  
  startSENSORTOQUE();
  
}

void loop() {

  
  // put your main code here, to run repeatedly:
  //esquerda_eixo(50,50);
  runner.execute();
  //nh.spinOnce();
}
