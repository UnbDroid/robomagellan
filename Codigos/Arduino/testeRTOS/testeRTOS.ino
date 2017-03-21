#include <PinChangeInt.h>
//#include <Arduino_FreeRTOS.h>

#define TRIGGER_1 A13
#define TRIGGER_2 A14
#define ECHO_1 A15

/*TaskHandle_t USTaskHandle;

static void TaskUS(void* pvParameters)
{        
    Serial.println(F("Task2, Deleting itself"));
    vTaskDelete(NULL);     //Delete own task by passing NULL(TaskHandle_2 can also be used)
}*/

volatile int channel_value1 = 0;
volatile int prev_time1 = 0;
uint8_t latest_interrupted_pin1;

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
  //xTaskCreate(TaskUS, "TaskUS", 100, NULL, 2, &USTaskHandle); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER_2,LOW);
  digitalWrite(TRIGGER_1,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIGGER_1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_1,LOW);
  delay(50);
  Serial.print("1 : ");
  Serial.println(channel_value1/29/2);
  delay(50);
  digitalWrite(TRIGGER_1,LOW);
  digitalWrite(TRIGGER_2,LOW);
  delayMicroseconds(4);
  digitalWrite(TRIGGER_2,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_2,LOW);
  delay(50);
  Serial.print("2 : ");
  Serial.println(channel_value1/29/2);
  
}
