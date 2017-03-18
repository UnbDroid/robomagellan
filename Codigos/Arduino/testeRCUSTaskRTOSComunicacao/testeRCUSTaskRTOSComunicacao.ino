#include "basicLibraries.h"
#include "ultrassom.h"
#include "controlerc.h"
#include "encoder.h"
#include "driver.h"

void TaskEncoder( void *pvParameters ){
  long oldTime = millis();
    for (;;){
      Serial.print("T Encoder: ");
      Serial.println(millis()-oldTime);
      velRefRaw.dir = vel2Raw(velRef.dir);
      velRefRaw.esq = vel2Raw(velRef.esq);
      
      ET.sendData();
      if(ET2.receiveData()){
        velAtual.dir = velFromRaw(velAtualRaw.dir);
        velAtual.esq = velFromRaw(velAtualRaw.esq);
      }
      vTaskDelay(30/portTICK_PERIOD_MS);
    }
}

void TaskSerialWrite( void *pvParameters ){
  long oldTime = millis();
    for (;;){
      Serial.println(millis()-oldTime);
      oldTime = millis();
      Serial.print("1 : ");
      Serial.println(USReadings[0]);
      Serial.print("2 : ");
      Serial.println(USReadings[1]);
      Serial.print("3 : ");
      Serial.println(USReadings[2]);
      Serial.print("4 : ");
      Serial.println(USReadings[3]);      
      Serial.print("5 : ");
      Serial.println(USReadings[4]);
      Serial.print("6 : ");
      Serial.println(USReadings[5]);
      Serial.print("7 : ");
      Serial.println(USReadings[6]);
      Serial.print("8 : ");
      Serial.println(USReadings[7]);
      Serial.print("9 : ");
      Serial.println(USReadings[8]);
      Serial.print("10 : ");
      Serial.println(USReadings[9]);
      Serial.print("11 : ");
      Serial.println(USReadings[10]);         
      Serial.print("Channel 1 : ");
      Serial.println(channel_value1);
      Serial.print("Channel 2 : ");
      Serial.println(channel_value2);
      Serial.print("Channel 3: ");
      Serial.println(channel_value3);
      Serial.print("Vel esq: "); Serial.println(velAtual.esq);
      Serial.print("Vel dir: "); Serial.println(velAtual.dir);
      velRef.dir = (channel_value2-1300.0)/2000.0*5;
      velRef.esq = velRef.dir;      
      vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //startMUXDEMUX8();
  startRC();
  start_ENCODER();
  //start_DRIVER();
  xTaskCreate(TaskEncoder,"TaskEncoder",128,NULL,1,NULL);
  xTaskCreate(TaskUS, "TaskUS", 100, NULL, 2, &USTaskHandle);
  xTaskCreate(TaskSerialWrite,"SerialWrite", 128,  NULL,3,  NULL ); 
  Serial.println("Starting program");
  //frente(122,122);
}

void loop() {
  // put your main code here, to run repeatedly:
}
