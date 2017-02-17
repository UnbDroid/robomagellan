 /* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
   it doesn't matter which encoder pin you use for A or B  
   uses Arduino pullups on A & B channel outputs
   turning on the pullups saves having to hook up resistors 
   to the A & B channel outputs 
*/ 

// Includes ------------------------------------------------------------------------------------------------

// SD card
#include <SD.h>

// Cálculos
#include <Math.h>

// Defines -------------------------------------------------------------------------------------------------

// SD card
#define CS 53

// Encoders esquerda
#define encoder0PinA 2
#define encoder0PinB 3

// Encoders direita
#define encoder1PinA 20
#define encoder1PinB 21

// Calculo de velocidade
#define pi 3.14159265359f

// Controle de velocidade
#define limiar_erro_velocidade 0.07f
#define POT_MAX_ESQUERDA 150
#define POT_MAX_DIREITA 120
#define POT_MIN_ESQUERDA 40
#define POT_MIN_DIREITA 40
#define Kp_esquerda 6.5f
#define Ki_esquerda 0.05f
#define Kd_esquerda 0.1f
#define Kp_direita 6.5f
#define Ki_direita 0.05f
#define Kd_direita 0.1f

// Controle remoto
#define CHANEL1 22
#define CHANEL2 24
#define CHANEL3 26

// Driver
#define IN1_D 4 //laranjas
#define IN2_D 5 
#define IN1_E 6 //amarelos
#define IN2_E 7

#define PWM_D 10 //azul
#define PWM_E 11 //roxo

// Variáveis ----------------------------------------------------------4-----------------------------------

// SD card
const int chipSelect = CS;
int dataString = 0;
bool abriu = true;
char nomearquivo[] = "datalog1.txt";

// Encoders
volatile long encoder0Pos = 0; //esquerda
volatile long encoder1Pos = 0; //direita
double voltas_esquerda = 0, voltas_esquerda_anterior = 0;
double voltas_direita = 0, voltas_direita_anterior = 0;

// Cálculo de velocidade
float velocidade_esquerda = 0;
float velocidade_direita = 0;
double tempo;
double tempo_aux;

// Controle de velocidade
float velocidade_Controlada = 0;
float erro_esquerda, erro_direita;
float erro_esquerda_int, erro_direita_int;
float erro_esquerda_deriv, erro_direita_deriv;
float pot_esquerda_erro = 0;
float pot_direita_erro = 0;
float velocidade_Referencia = 3;
float velocidade_Referencia_nova = 0;
double tempoint_esquerda = 0;
double tempoint_direita = 0;
double tempoderiv_esquerda = 0;
double tempoderiv_direita =0;
bool trocar_sentido = false;
bool foward = true;
bool back = false;
bool left = false;
bool right = false;
bool left_eixo = false;
bool right_eixo = false;

// Driver
int pot_direita = 0;
int pot_esquerda = 0;

// Ler int do buffer serial
float valor = 0;

// Usar o controle remoto
int ch1;
int ch2;
int ch3;

//Funcoes de setup dos módulos --------------------------------------------------------------------------------------------------------------

// Driver

void start_DRIVER (){

  pinMode(IN1_E, OUTPUT);
  pinMode(IN2_E, OUTPUT);
  pinMode(IN1_D, OUTPUT);
  pinMode(IN2_D, OUTPUT);
  pinMode(PWM_E, OUTPUT);
  pinMode(PWM_D, OUTPUT);
}

// Encoders

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

// SD card

void start_SD () {
  
  pinMode (CS,OUTPUT); 
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}

// Controle remoto

void start_RC(){
  
  pinMode(CHANEL1, INPUT);
  pinMode(CHANEL2, INPUT);
  pinMode(CHANEL3, INPUT);
  
}

//Funções driver--------------------------------------------------------------------------------------------------------------------------

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

//Funções Encoder -------------------------------------------------------------------------------------------------------------

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

// Funcoes Controle de Velocidade -----------------------------------------------------------------------------------------

void controlePIVelocidade (){

  if(velocidade_Referencia == 0){
    parar();
    return;  
  }
  
  erro_esquerda = (velocidade_Referencia)-(velocidade_esquerda);
  erro_esquerda_int += (erro_esquerda*(millis()-tempoint_esquerda)/1000);
  tempoint_esquerda = millis();
  erro_esquerda_deriv += (erro_esquerda/((millis()-tempoderiv_esquerda)/1000));
  tempoderiv_esquerda = millis();
  
  erro_direita = (velocidade_Referencia)-(velocidade_direita);
  erro_direita_int += (erro_direita*(millis()-tempoint_direita)/1000);
  tempoint_direita = millis();
  erro_direita_deriv += (erro_direita/((millis()-tempoderiv_direita)/1000));
  tempoderiv_direita = millis();
  
  pot_esquerda_erro = (erro_esquerda*Kp_esquerda + erro_esquerda_int*Ki_esquerda + erro_esquerda_deriv*Kd_esquerda);
  pot_direita_erro = (erro_direita*Kp_direita + erro_direita_int*Ki_direita + erro_direita_deriv*Kd_direita);
  
  if ((abs(erro_esquerda) < limiar_erro_velocidade)){
    erro_esquerda = 0;
    erro_esquerda_int = 0;
    erro_esquerda_deriv = 0;
    if (trocar_sentido){
      velocidade_Referencia = velocidade_Referencia_nova;
      trocar_sentido = false; 
    }
  }
  if ((abs(erro_direita) < limiar_erro_velocidade)){
    erro_direita = 0;
    erro_direita_int = 0;
    erro_direita_deriv = 0;
    if (trocar_sentido){
      velocidade_Referencia = velocidade_Referencia_nova;
      trocar_sentido = false;
    } 
  }
  if(abs(pot_esquerda_erro) > 5){
    if (pot_esquerda_erro > 5){
      pot_esquerda_erro = 5;
    }else if (pot_esquerda < -5) {
      pot_esquerda_erro = -5;
    }
  }
  if(abs(pot_direita_erro) > 5){
    if (pot_direita_erro > 5){
      pot_direita_erro = 5;
    }else if (pot_direita < -5) {
      pot_direita_erro = -5;
    }
  }
 
  pot_esquerda = pot_esquerda + pot_esquerda_erro;
  pot_direita = pot_direita + pot_direita_erro;
  
  if (abs(pot_esquerda) > POT_MAX_ESQUERDA){
    pot_esquerda = POT_MAX_ESQUERDA;
  }else if (abs(pot_esquerda) < POT_MIN_ESQUERDA){
    pot_esquerda = POT_MIN_ESQUERDA;  
  }
  if (abs(pot_direita) > POT_MAX_DIREITA){
    pot_direita = POT_MAX_DIREITA;
  }else if (abs(pot_direita) < POT_MIN_DIREITA){
    pot_direita = POT_MIN_DIREITA;  
  }

  if (foward){
    frente(pot_esquerda,pot_direita);  
  }
  
  Serial.print("Potência controlada esquerda:");Serial.println(pot_esquerda);
  Serial.print("Potência de erro esquerda: ");  Serial.println(pot_esquerda_erro);
  Serial.print("Erro esquerda: ");              Serial.println(erro_esquerda);
  Serial.print("Erro_int esquerda: ");          Serial.println(erro_esquerda_int);
  Serial.print("Erro_deriv esquerda: ");        Serial.println(erro_esquerda_deriv);
  Serial.print("Potência controlada direita: ");Serial.println(pot_direita);
  Serial.print("Potência de erro direita: ");   Serial.println(pot_direita_erro);
  Serial.print("Erro direita: ");               Serial.println(erro_direita);
  Serial.print("Erro_int direita: ");           Serial.println(erro_direita_int); 
  Serial.print("Erro_deriv direita: ");         Serial.println(erro_direita_deriv);   
  Serial.println(" ");

}


// Setup e Loop principais
//-----------------------------------------------------------------------------------------------------------

void setup(){
  
  tempo = millis();
  
  start_DRIVER();

  start_ENCODER();
  
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Start");
 
  start_SD();

  start_RC();
}

void loop(){

if ((millis()/1000) > 5){

  if ((millis()/1000) > 30){
    velocidade_Referencia = 0;  
  }
  File dataFile = SD.open(nomearquivo, FILE_WRITE);

  if(!dataFile) {
    nomearquivo[14] = "datalog2.txt"; 
    dataFile = SD.open(nomearquivo, FILE_WRITE);
  }
  if (abriu && dataFile){
    dataFile.println("----------------------------------------------------------");   
    dataFile.close();
    abriu = false;
  }
  
  if (millis() - tempo > 50){
    
    tempo_aux = (millis()- tempo);
    tempo = millis();
    
    voltas_esquerda = encoder0Pos/1632.67;
    voltas_direita = encoder1Pos/1632.67;
   
    velocidade_esquerda = 1000*(voltas_esquerda - voltas_esquerda_anterior)/(tempo_aux);
    velocidade_direita = 1000*(voltas_direita - voltas_direita_anterior)/(tempo_aux);
    
    voltas_esquerda_anterior = voltas_esquerda;
    voltas_direita_anterior = voltas_direita;
 
    Serial.print("Velocidade esquerda: ");      Serial.println(velocidade_esquerda);
    Serial.print("Velocidade direita: ");       Serial.println(velocidade_direita);
    Serial.println(" ");
  }

  controlePIVelocidade();  

  if(Serial.available() > 0) {
    velocidade_Referencia_nova = Serial.parseFloat();  
    Serial.print("Velocidade recebida: ");      Serial.println(velocidade_Referencia_nova);

    if (velocidade_Referencia*velocidade_Referencia_nova < 0){
      velocidade_Referencia = 0;
      trocar_sentido = true;
    }else if (velocidade_Referencia*velocidade_Referencia_nova >= 0){
      velocidade_Referencia = velocidade_Referencia_nova; 
    }
  }

  // Ler a velocidade de Referencia pelo controle remoto
  
  ch1 = pulseIn(CHANEL1, HIGH, 25000);  
  ch2 = pulseIn(CHANEL2, HIGH, 25000); 
  ch3 = pulseIn(CHANEL3, HIGH, 25000);
  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(ch1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(ch2);
  Serial.print("Channel 3: ");
  Serial.println(ch3);
  Serial.println();

  /*
   * Usar o controle para pegar a velocidade_Referencia!!
   * if (ch2 != 0){
    
    if (ch2 < 1200){
      velocidade_Referencia = 3;
      Serial.print("Velocidade recebida: ");      Serial.println(velocidade_Referencia);
    }else if (ch2 > 1600){
      velocidade_Referencia = 3.5;  
      Serial.print("Velocidade recebida: ");      Serial.println(velocidade_Referencia);
    }
  }
  if ((ch1 < 1500) && (ch1 != 0)){
    velocidade_Referencia = 0;
    Serial.print("Velocidade recebida: ");      Serial.println(velocidade_Referencia);
  }*/
  Serial.print("Contador encoder esquerdo: ");  Serial.println (encoder0Pos, DEC);
  Serial.print("Contador encoder direito: ");   Serial.println (encoder1Pos, DEC);
  Serial.print("Potencia direita: ");           Serial.println(pot_direita);
  Serial.print("Potencia esquerda: ");          Serial.println(pot_esquerda); 
  Serial.println(" ");
  
  if (dataFile) {
    dataFile.print(millis());dataFile.print(" ");dataFile.print(velocidade_esquerda);
    dataFile.print(" ");dataFile.print(velocidade_direita);
    dataFile.print(" ");dataFile.println(velocidade_Referencia);   
    dataFile.close();
  }
}
}

