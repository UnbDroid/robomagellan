#include <TaskScheduler.h>
#include <TinyGPS++.h>
#include <NewPing.h>

#define PERIODO 100

// Coisas do GPS ----------------------------------------

TinyGPSPlus gps;

double lat,lng,alt;

void displayInfo()
{
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    lat = gps.location.lat();
    lng = gps.location.lng();
    alt = gps.altitude.meters();
    Serial.print(lat,8);
    Serial.print(F("\t"));
    Serial.print(lng,8);
    Serial.print(F("\t"));
    Serial.print(alt,8);
    Serial.println();
  }
  else
  {
    Serial.print(F("INVALID"));
    lat = 0;
    lng = 0;
  }
} 


void leituraTinyGps(){
  
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read())) {
      displayInfo();
    }
  
}

// Coisas dos ultrassons

#define TRIGGER_1 39 
#define ECHO_1 41 
#define TRIGGER_2 38
#define ECHO_2 40
#define TRIGGER_3 26
#define ECHO_3 28
#define TRIGGER_4 30
#define ECHO_4 32
#define TRIGGER_5 46
#define ECHO_5 48
#define TRIGGER_6 34
#define ECHO_6 36
#define TRIGGER_7 27 
#define ECHO_7 29 
#define TRIGGER_8 35 
#define ECHO_8 37 
#define TRIGGER_9 42
#define ECHO_9 44
#define TRIGGER_10 24 
#define ECHO_10 22 
#define TRIGGER_11 23 
#define ECHO_11 25 
#define TRIGGER_12 37
#define ECHO_12 35
#define TRIGGER_13 25
#define ECHO_13 23
#define TRIGGER_14 22
#define ECHO_14 24
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SONAR_NUM     11 // Number of sensors.

NewPing sonar[SONAR_NUM] = {     // Sensor object array.
  NewPing(TRIGGER_1, ECHO_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIGGER_2, ECHO_2, MAX_DISTANCE),
  NewPing(TRIGGER_3, ECHO_3, MAX_DISTANCE),
  NewPing(TRIGGER_4, ECHO_4, MAX_DISTANCE),
  NewPing(TRIGGER_5, ECHO_5, MAX_DISTANCE),
  NewPing(TRIGGER_6, ECHO_6, MAX_DISTANCE), 
  NewPing(TRIGGER_7, ECHO_7, MAX_DISTANCE),
  NewPing(TRIGGER_8, ECHO_8, MAX_DISTANCE),
  NewPing(TRIGGER_9, ECHO_9, MAX_DISTANCE),
  NewPing(TRIGGER_10, ECHO_10, MAX_DISTANCE),
  NewPing(TRIGGER_11, ECHO_11, MAX_DISTANCE)
};
int USReadOrder[SONAR_NUM] = {0,11,1,10,2,9,3,8,4,7,5};
int USReadings[SONAR_NUM];

// Tasks ------------------------------------------------

void taskGPSCallback();
void taskUSCallback();

Task taskGPS(PERIODO, TASK_FOREVER, &taskGPSCallback);
Task taskUS(PERIODO, TASK_FOREVER, &taskUSCallback);

Scheduler runner;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(4800);
  runner.init();


  runner.addTask(taskGPS);
  runner.addTask(taskUS);

  taskGPS.enable();
  taskUS.enable();
}

void taskGPSCallback(){
  taskUS.delay(10);
  Serial.print("GPS: ");
  Serial.println(millis());
  unsigned long t1 = millis();
  leituraTinyGps();
  unsigned long t2 = millis();
  Serial.print("Demorei ");
  Serial.println(t2-t1);
}

void readUS(int us_num){
  USReadings[us_num] = sonar[us_num].ping_cm();
}

void taskUSCallback(){
  Serial.print("US: ");
  Serial.println(millis());
  unsigned long t1 = millis();
  for(unsigned i=0; i<SONAR_NUM;i++){
    readUS(USReadOrder[i]); 
  }
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

void loop() {
  // put your main code here, to run repeatedly:
  runner.execute();
}
