#include "basicLibraries.h"
#include "ultrassom.h"

void TaskSerialWrite( void *pvParameters ){
  long oldTime = millis();
    for (;;){
      Serial.println(millis()-oldTime);
      oldTime = millis();
      Serial.print("1 : ");
      Serial.println(us[0]);
      Serial.print("2 : ");
      Serial.println(us[1]);
      vTaskDelay(30/portTICK_PERIOD_MS);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  startUS();
  xTaskCreate(TaskUS, "TaskUS", 100, NULL, 1, &USTaskHandle);
  xTaskCreate(TaskSerialWrite,"SerialWrite", 128,  NULL,2,  NULL ); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
