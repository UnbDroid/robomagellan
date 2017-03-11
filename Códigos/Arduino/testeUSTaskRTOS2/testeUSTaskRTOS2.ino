#include <PinChangeInt.h>
#include <Arduino_FreeRTOS.h>

#define TRIGGER_1 A13
#define TRIGGER_2 A14
#define ECHO_1 A15

TaskHandle_t USTaskHandle;

volatile int channel_value1 = 0;
volatile int prev_time1 = 0;
uint8_t latest_interrupted_pin1;
volatile int us1 = 0;
volatile int us2 = 0;

void TaskSerialWrite( void *pvParameters ){
  long oldTime = millis();
    for (;;){
      Serial.println(millis()-oldTime);
      oldTime = millis();
      Serial.print("1 : ");
      Serial.println(us1);
      Serial.print("2 : ");
      Serial.println(us2);
      vTaskDelay(30/portTICK_PERIOD_MS);
    }
}

void trigger(int pin){
    digitalWrite(pin,LOW);
    delayMicroseconds(4);
    digitalWrite(pin,HIGH);
    delayMicroseconds(10);    
    digitalWrite(pin,LOW); 
}

static void TaskUS(void* pvParameters){
  for (;;){ 
    trigger(TRIGGER_1);
    vTaskDelay(50/ portTICK_PERIOD_MS);
    us1 = channel_value1/29/2;
    trigger(TRIGGER_2);
    vTaskDelay(50/ portTICK_PERIOD_MS);
    us2 = channel_value1/29/2;
  }
}

void falling1();

void rising1()
{
  //Serial.println("Subiu");
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &falling1, FALLING);
  prev_time1 = micros();
}

void falling1() {
  //Serial.println("Desceu");
  latest_interrupted_pin1=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin1, &rising1, RISING);
  channel_value1 = micros()-prev_time1;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ECHO_1, INPUT); digitalWrite(ECHO_1, HIGH);
  pinMode(TRIGGER_1, OUTPUT);
  pinMode(TRIGGER_2, OUTPUT);
  digitalWrite(TRIGGER_1,LOW);
  digitalWrite(TRIGGER_2,LOW);
  PCintPort::attachInterrupt(ECHO_1, &rising1, RISING);
  xTaskCreate(TaskUS, "TaskUS", 100, NULL, 1, &USTaskHandle);
  xTaskCreate(TaskSerialWrite,(const portCHAR *) "SerialWrite", 128,  NULL,2,  NULL ); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
