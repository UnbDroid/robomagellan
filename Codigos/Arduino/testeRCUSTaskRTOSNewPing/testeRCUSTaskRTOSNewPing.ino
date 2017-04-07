#include "basicLibraries.h"
#include "ultrassom.h"
#include "controlerc.h"
#include "encoder.h"
#include "driver.h"

void TaskEncoder( void *pvParameters ){
  long oldTime = millis();
    for (;;){
      //Serial.println(millis()-oldTime);
      tempo_aux = millis() - tempo;
      tempo = millis();
      
      voltas_esquerda = encoder0Pos/1632.67;
      voltas_direita = encoder1Pos/1632.67;
     
      velocidade_esquerda = 1000*(voltas_esquerda - voltas_esquerda_anterior)/(tempo_aux);
      velocidade_direita = 1000*(voltas_direita - voltas_direita_anterior)/(tempo_aux);
      
      voltas_esquerda_anterior = voltas_esquerda;
      voltas_direita_anterior = voltas_direita;

      //oldTime = millis();
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
      Serial.print("Velocidade esquerda: ");      Serial.println(velocidade_esquerda);
      Serial.print("Velocidade direita: ");       Serial.println(velocidade_direita);
      vTaskDelay(50/portTICK_PERIOD_MS);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  startMUXDEMUX8();
  startRC();
  start_ENCODER();
  start_DRIVER();
  xTaskCreate(TaskEncoder,"TaskEncoder",128,NULL,1,NULL);
  xTaskCreate(TaskUS, "TaskUS", 100, NULL, 2, &USTaskHandle);
  xTaskCreate(TaskSerialWrite,"SerialWrite", 128,  NULL,3,  NULL ); 
  Serial.println("Starting program");
  frente(122,122);
}

void loop() {
  // put your main code here, to run repeatedly:
}
