#include <TaskScheduler.h>

#include <TinyGPS++.h>

#include <NewPing.h>

#include <ros.h>
#include <ros/time.h>
#include <raspberry_msgs/StampedInt64.h>
#include <raspberry_msgs/StampedFloat32.h>
#include <raspberry_msgs/StampedFloat64.h>

#include <math.h>

#define PERIODO 200

// Coisas do ROS ----------------------------------------

ros::NodeHandle  nh;
void sendInt64(int id, int data);
void sendFloat64(int id, double data);
void initializeRosCom();
void messageInt64Cb( const raspberry_msgs::StampedInt64& r_int64_msg);
void messageFloat32Cb( const raspberry_msgs::StampedFloat32& r_float32_msg);
void messageFloat64Cb( const raspberry_msgs::StampedFloat64& r_float64_msg);

// Ids do ROS ------------------*************************

#define US01 555
#define US02 556
#define US03 557
#define US04 558
#define US05 559
#define US06 560
#define US07 561
#define US08 562
#define US09 563
#define US10 564
#define US11 565

#define GPS_LAT 666
#define GPS_LON 667
#define GPS_ALT 668
#define GPS_VALID 669
#define GPS_UPDATED 670

// Coisas do Encoder ------------------------------------

// Encoders esquerda
#define encoder0PinA 18
#define encoder0PinB 19

// Encoders direita
#define encoder1PinA 2
#define encoder1PinB 3

#define PWM_D 8
#define PWM_E 11

// Calculo de velocidade
#define pi 3.14159265359f

// Encoders
volatile long encoder0Pos = 0; //esquerda
volatile long encoder1Pos = 0; //direita
double voltas_esquerda = 0, voltas_esquerda_anterior = 0;
double voltas_direita = 0, voltas_direita_anterior = 0;

// Cálculo de velocidade
float velocidade_esquerda = 0;
float velocidade_direita = 0;
unsigned long tempo;
unsigned long tempo_aux;

void doEncoderA();
void doEncoderB();
void doEncoder1A();
void doEncoder1B();

void start_ENCODER () {

  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT);
  pinMode(encoder1PinA, INPUT); 
  pinMode(encoder1PinB, INPUT); 

// Encoder Esquerda
  attachInterrupt(digitalPinToInterrupt(encoder0PinA), doEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder0PinB), doEncoderB, CHANGE);  

// Encoder Direita
  attachInterrupt(digitalPinToInterrupt(encoder1PinA), doEncoder1A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder1PinB), doEncoder1B, CHANGE);  
}

void doEncoderA(){

  noInterrupts();
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW 
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  interrupts();
}

void doEncoderB(){

  noInterrupts();
  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  interrupts();
}


void doEncoder1A(){

  noInterrupts();
  // look for a low-to-high on channel A
  if (digitalRead(encoder1PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == LOW) {  
      encoder1Pos = encoder1Pos + 1;         // CW 
    } 
    else {
      encoder1Pos = encoder1Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinB) == HIGH) {   
      encoder1Pos = encoder1Pos + 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;          // CCW
    }
  }
  interrupts();
}

void doEncoder1B(){

  noInterrupts();
  // look for a low-to-high on channel B
  if (digitalRead(encoder1PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder1PinA) == HIGH) {  
      encoder1Pos = encoder1Pos + 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinA) == LOW) {   
      encoder1Pos = encoder1Pos + 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos - 1;          // CCW
    }
  }
  interrupts();
}

// Coisas do Driver ------------------------------------

// Driver
#define IN1_D 10
#define IN2_D 9 
#define IN1_E 13
#define IN2_E 12

// Driver
float pot_direita = 0;
float pot_esquerda = 0;

void start_DRIVER (){

  pinMode(IN1_E, OUTPUT);
  pinMode(IN2_E, OUTPUT);
  pinMode(IN1_D, OUTPUT);
  pinMode(IN2_D, OUTPUT);
  pinMode(PWM_E, OUTPUT);
  pinMode(PWM_D, OUTPUT);
}

void direita(int potEsquerda, int potDireita){
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW); 
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);  
}

void esquerda(int potEsquerda, int potDireita){
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW); 
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);  
}


void direita_eixo (int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW); 
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, LOW); 

}

void esquerda_eixo (int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, LOW);
  digitalWrite(IN2_E, HIGH);  
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);

}

void frente(int potEsquerda, int potDireita){
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW); 
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);  
}

void tras(int potEsquerda, int potDireita){
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, LOW);
  digitalWrite(IN2_E, HIGH);
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, LOW); 
}

void parar () {
  digitalWrite(IN1_E, LOW);
  digitalWrite(IN2_E, LOW);  
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, LOW); 
}

void travar (){
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, HIGH);  
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, HIGH); 
}

// Coisas do GPS ----------------------------------------

TinyGPSPlus gps;

double lat,lon,alt;

void displayInfo()
{
  //Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    lat = gps.location.lat();
    lon = gps.location.lng();
    alt = gps.altitude.meters();
    Serial.print(lat,8);
    Serial.print(F("\t"));
    Serial.print(lon,8);
    Serial.print(F("\t"));
    Serial.print(alt,8);
    Serial.println();
  }
  else
  {
   // Serial.print(F("INVALID"));
    lat = 0;
    lon = 0;
  }
} 


void leituraTinyGps(){
  
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read())) {
      displayInfo();
    }
  
}

// Coisas dos ultrassons ---------------------------------------------------------------

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
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

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

int USReadings[SONAR_NUM];

// Coisas do controle remoto ----------------------------
  
#define CHANEL_1 A0
#define CHANEL_2 A1
#define CHANEL_3 A2

int ch1 = 0, ch2 =0, ch3 =0;

void start_RC() {
  
  pinMode(CHANEL_1, INPUT);
  pinMode(CHANEL_2, INPUT);
  pinMode(CHANEL_3, INPUT);

}

// Tasks ------------------------------------------------

void taskGPSCallback();

void taskUSCallback1();
void taskUSCallback2();
void taskUSCallback3();
void taskUSCallback4();
void taskUSCallback5();
void taskUSCallback6();
void taskShowUSReadingCallback();

void taskROSCallback();

void taskENCODERCallback();

void taskRCCallback();

Task taskGPS(PERIODO, TASK_FOREVER, &taskGPSCallback);

Task taskUS1(PERIODO, TASK_FOREVER, &taskUSCallback1);
Task taskUS2(PERIODO, TASK_FOREVER, &taskUSCallback2);
Task taskUS3(PERIODO, TASK_FOREVER, &taskUSCallback3);
Task taskUS4(PERIODO, TASK_FOREVER, &taskUSCallback4);
Task taskUS5(PERIODO, TASK_FOREVER, &taskUSCallback5);
Task taskUS6(PERIODO, TASK_FOREVER, &taskUSCallback6);
Task showUSReadings(PERIODO, TASK_FOREVER, &taskShowUSReadingCallback);

Task taskROS(PERIODO,TASK_FOREVER, &taskROSCallback);

Task taskENCODER (30, TASK_FOREVER, &taskENCODERCallback);

Task taskRC (30, TASK_FOREVER, &taskRCCallback);

Scheduler runner;


void taskGPSCallback(){
  //Serial.print("GPS: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  leituraTinyGps();
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1);
}

void readUS(int us_num){
  USReadings[us_num] = sonar[us_num].ping_cm();
}

void taskUSCallback1(){
  //Serial.print("US 1: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(0);
  readUS(10);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskUSCallback2(){
  //Serial.print("US 2: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(1);
  readUS(9);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskUSCallback3(){
  //Serial.print("US 3: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(2);
  readUS(8);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskUSCallback4(){
  //Serial.print("US 4: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(3);
  readUS(7);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskUSCallback5(){
  //Serial.print("US 5: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(4);
  readUS(6);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
}

void taskUSCallback6(){
  //Serial.print("US 6: ");
  //Serial.println(millis());
  //unsigned long t1 = millis();
  readUS(5);
  //unsigned long t2 = millis();
  //Serial.print("Demorei ");
  //Serial.println(t2-t1); 
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

  noInterrupts();
  ch1 = pulseIn(CHANEL_1, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(CHANEL_2, HIGH, 25000); // each channel
  ch3 = pulseIn(CHANEL_3, HIGH, 25000);
  interrupts();
  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(ch1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(ch2);
  Serial.print("Channel 3: ");
  Serial.println(ch3);
  
}

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  Serial2.begin(4800);
  
  //initializeRosCom();

  start_DRIVER();

  start_ENCODER();

  start_RC();
  
  runner.init();

  runner.addTask(taskENCODER);
  runner.addTask(taskGPS);
  runner.addTask(taskUS1);
  runner.addTask(taskUS2);
  runner.addTask(taskUS3);
  runner.addTask(taskUS4);
  runner.addTask(taskUS5);
  runner.addTask(taskUS6);
  runner.addTask(showUSReadings);
  //runner.addTask(taskROS);
  runner.addTask(taskRC);
  
  taskGPS.enable();
  taskUS1.enable();
  taskUS2.enable();
  taskUS3.enable();
  taskUS4.enable();
  taskUS5.enable();
  taskUS6.enable();
  showUSReadings.enable();
  //taskROS.enable();
  taskENCODER.enable();
  taskRC.enable();
}

void loop() {

  
  // put your main code here, to run repeatedly:
  esquerda_eixo(50,50);
  runner.execute();
  //nh.spinOnce();
}
