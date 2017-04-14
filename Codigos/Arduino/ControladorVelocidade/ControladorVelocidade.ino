/* read a rotary encoder with interrupts
  Encoder hooked up with common to GROUND,
  encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
  it doesn't matter which encoder pin you use for A or B
  uses Arduino pullups on A & B channel outputs
  turning on the pullups saves having to hook up resistors
  to the A & B channel outputs
*/

// SD card

/*#include <SD.h>

#define CS 53

const int chipSelect = CS;
int dataString = 0;
bool abriu = true;
char nomearquivo[] = "datalog1.txt";

void startSD () {
  
  pinMode (CS,OUTPUT); 
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}*/

// Includes ------------------------------------------------------------------------------------------------

#include <math.h>
#include<PinChangeInt.h>
#include <EasyTransfer.h>

#include "driver.h"

// Defines -------------------------------------------------------------------------------------------------

// Encoders esquerda
#define encoder0PinA 19
#define encoder0PinB 18

// Encoders direita
#define encoder1PinA 3
#define encoder1PinB 2

// Calculo de velocidade
#define pi 3.14159265359f

// Controle de velocidade
#define limiar_erro_velocidade 0.07f
#define Kp_esquerda 6.5f
#define Ki_esquerda 0.05f
#define Kd_esquerda 0.1f
#define Kp_direita 6.5f
#define Ki_direita 0.05f
#define Kd_direita 0.1f

#define VELOCIDADE_MAXIMA 5.5f
#define VELOCIDADE_LIMITE 8.0f

// Variáveis -----------------------------------------------------------------------------------------------


// Encoders
volatile long encoder0Pos = 0; //esquerda
volatile long encoder1Pos = 0; //direita
double voltas_esquerda = 0, voltas_esquerda_anterior = 0;
double voltas_direita = 0, voltas_direita_anterior = 0;

// Cálculo de velocidade
float velocidade_esquerda = 0;
float velocidade_direita = 0;
int velocidade_esquerda_aux = 0;
int velocidade_direita_aux = 0;
double tempo;
double tempo_aux;

// Controle de velocidade
float velocidade_ReferenciaDireita_anterior = 0;
float velocidade_ReferenciaEsquerda_anterior = 0;

float theta1_esquerda = 0.40;
float theta2_esquerda = 0.15;//0.25;
float yTv_esquerda = 0.08;

float theta1_direita = 0.40;
float theta2_direita = 0.15;
float yTv_direita = 0.07;

float velocidade_esquerda_modelo = 0;
float velocidade_direita_modelo = 0;
float tensaomotor_esquerda = 0;
float tensaomotor_direita = 0;
float tensao_bateria = 14.8;

//desacelerar
float potencia_aux_esquerda = 0;
float potencia_aux_direita = 0;
float aceleracao_Esquerda =0;
float aceleracao_Direita = 0;

//Comunicacao Arduino
EasyTransfer ETin; 
EasyTransfer ETout;

struct VELOCIDADES_REFERENCIA_RAW{
  int16_t dir;
  int16_t esq;
};

struct VELOCIDADES_ATUAIS_RAW{
  int16_t dir;
  int16_t esq;
};

VELOCIDADES_REFERENCIA_RAW velocidade_recebida;
VELOCIDADES_ATUAIS_RAW velocidade_enviada;

//Funcoes -----------------------------------------------------------------------------------------------------------------------------------

void doEncoderA();
void doEncoderB();
void doEncoder1A();
void doEncoder1B();

//Funcoes de setup dos módulos --------------------------------------------------------------------------------------------------------------

void startEncoder () {

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

//Comunicacao arduino

void startComunicacao(){
  Serial2.begin(9600);
  ETin.begin(details(velocidade_recebida), &Serial2);
  ETout.begin(details(velocidade_enviada), &Serial2);
  
}

//Funções Encoder -------------------------------------------------------------------------------------------------------------

void doEncoderA() {

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

void doEncoderB() {

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


void doEncoder1A() {

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

void doEncoder1B() {

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
void desacelerar (){

  aceleracao_Esquerda = (-potencia_aux_esquerda)/0.2; 
  aceleracao_Direita = (-potencia_aux_direita)/0.2;
  
  pot_esquerda = potencia_aux_esquerda + (aceleracao_Esquerda*millis()/1000);
  pot_direita = potencia_aux_direita + (aceleracao_Direita*millis()/1000); 
  
  if ((potencia_aux_esquerda > 0 && pot_esquerda < 0) || (potencia_aux_esquerda < 0 && pot_esquerda > 0) || (abs(pot_esquerda) < POT_MIN_ESQUERDA)){
    parar();
    pot_esquerda = 0;
    pot_direita = 0;  
  }
  else{
    setVelocidade();  
  }
 
}
void controleAdaptativoVelocidade() {

  if (velocidade_ReferenciaEsquerda == 0 && velocidade_ReferenciaDireita == 0) {

    velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;
    velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;
    
    theta1_esquerda = 0.40;
    theta2_esquerda = 0.15;
    yTv_esquerda = 0.08;

    theta1_direita = 0.40;
    theta2_direita = 0.15;
    yTv_direita = 0.07;

    //parar();
    desacelerar();
    return;
  }

  theta1_esquerda = theta1_esquerda - (yTv_esquerda * velocidade_ReferenciaEsquerda * (velocidade_esquerda - velocidade_esquerda_modelo));
  theta2_esquerda = theta2_esquerda + (yTv_esquerda * velocidade_esquerda * (velocidade_esquerda - velocidade_esquerda_modelo));

  theta1_direita = theta1_direita - (yTv_direita * velocidade_ReferenciaDireita * (velocidade_direita - velocidade_direita_modelo));
  theta2_direita = theta2_direita + (yTv_direita * velocidade_direita * (velocidade_direita - velocidade_direita_modelo));

  tensaomotor_esquerda = (theta1_esquerda * velocidade_ReferenciaEsquerda) - (theta2_esquerda * velocidade_esquerda);

  tensaomotor_direita = (theta1_direita * velocidade_ReferenciaDireita) - (theta2_direita * velocidade_direita);

  velocidade_esquerda_modelo = (0.00248 * velocidade_esquerda_modelo) + (0.99752 * velocidade_ReferenciaEsquerda_anterior);

  velocidade_direita_modelo = (0.00248 * velocidade_direita_modelo) + (0.99752 * velocidade_ReferenciaDireita_anterior);

  velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;
  
  velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;

  pot_esquerda = 100 * tensaomotor_esquerda / (tensao_bateria);
  
  
  //TODO compensar a deadzone
  pot_direita = 100 * tensaomotor_direita / (tensao_bateria);
  
  potencia_aux_esquerda = pot_esquerda;
  potencia_aux_direita = pot_direita;

  setVelocidade();
  /*Serial.print("Potência esquerda antes limitador:");  Serial.println(pot_esquerda);

  
  Serial.print("Potência controlada esquerda:"); Serial.println(pot_esquerda);
  Serial.print("Theta1_esquerda: ");            Serial.println(theta1_esquerda);
  Serial.print("Theta2_esquerda: ");            Serial.println(theta2_esquerda);
  Serial.print("Potencia esquerda: ");          Serial.println(pot_esquerda);
  Serial.print("Velocidade esquerda modelo: "); Serial.println(velocidade_esquerda_modelo);
  Serial.println(" ");
  */
  return;
}


// Setup e Loop principais----------------------------------------------------------------------------------------

void setup() {

  tempo = millis();
  
  Serial.begin(115200);
  //startSD();
  
  startDriver();

  startEncoder();

  startComunicacao();

}

void loop() {

    /*File dataFile = SD.open(nomearquivo, FILE_WRITE);

    if(!dataFile) {
      nomearquivo[14] = "datalog2.txt"; 
      dataFile = SD.open(nomearquivo, FILE_WRITE);
    }*/
    
   if (millis() - tempo > 50) {
      
      tempo_aux = (millis() - tempo);
      tempo = millis();
    
      voltas_esquerda = encoder0Pos / 1632.67;
      voltas_direita = encoder1Pos / 1632.67;
    
      velocidade_esquerda = 1000 * (voltas_esquerda - voltas_esquerda_anterior) / (tempo_aux);
      velocidade_direita = 1000 * (voltas_direita - voltas_direita_anterior) / (tempo_aux);
    
      voltas_esquerda_anterior = voltas_esquerda;
      voltas_direita_anterior = voltas_direita;
    
      /*Serial.print("Velocidade esquerda: ");      Serial.println(velocidade_esquerda);
      Serial.print("Velocidade direita: ");       Serial.println(velocidade_direita);
      Serial.println(" ");
      */    
      velocidade_enviada.esq = velocidade_esquerda * 100;
      velocidade_enviada.dir = velocidade_direita * 100;
      ETout.sendData();
      
  }
  controleAdaptativoVelocidade();
  
  /*if (Serial.available() > 0) {
    velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;
    velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;
    velocidade_ReferenciaDireita = Serial.parseFloat();
    velocidade_ReferenciaEsquerda = velocidade_ReferenciaDireita;
    Serial.print("Velocidade recebida: ");      Serial.println(velocidade_ReferenciaDireita);
  }*/
  
  if(ETin.receiveData()){
    if (abs(((float)velocidade_recebida.dir/100.0)) < VELOCIDADE_LIMITE && abs((float)velocidade_recebida.esq/100.0) < VELOCIDADE_LIMITE){
      if (abs((float)velocidade_recebida.dir/100.0) < VELOCIDADE_MAXIMA){
        velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;
        velocidade_ReferenciaDireita = (float)velocidade_recebida.dir/100.0;
      }
      else if (((float)velocidade_recebida.dir/100) < 0){
        velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;
        velocidade_ReferenciaDireita = -VELOCIDADE_MAXIMA;      
      }
      else if (((float)velocidade_recebida.dir/100) > 0){
        velocidade_ReferenciaDireita_anterior = velocidade_ReferenciaDireita;
        velocidade_ReferenciaDireita = VELOCIDADE_MAXIMA;      
      }
      if (abs((float)velocidade_recebida.esq/100.0) < VELOCIDADE_MAXIMA){
        velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;      
        velocidade_ReferenciaEsquerda = (float)velocidade_recebida.esq/100.0;
      }
      else if (((float)velocidade_recebida.esq/100) < 0){
        velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;
        velocidade_ReferenciaEsquerda = -VELOCIDADE_MAXIMA;      
      }
      else if (((float)velocidade_recebida.dir/100) > 0){
        velocidade_ReferenciaEsquerda_anterior = velocidade_ReferenciaEsquerda;
        velocidade_ReferenciaEsquerda = VELOCIDADE_MAXIMA;      
      }
     
      Serial.print("Esquerda: "); Serial.println((float)velocidade_recebida.esq/100.0);
      Serial.print("Direita: "); Serial.println((float)velocidade_recebida.dir/100.0);
    }
  }
  /*if (dataFile) {
    dataFile.print(millis());dataFile.print(" ");dataFile.print(velocidade_esquerda);
    dataFile.print(" ");dataFile.print(velocidade_direita);
    dataFile.print(" ");dataFile.print(velocidade_ReferenciaEsquerda);
    dataFile.print(" ");dataFile.print(velocidade_ReferenciaDireita);
    dataFile.print(" ");dataFile.print(pot_esquerda);
    dataFile.print(" ");dataFile.println(pot_direita);   
    dataFile.close();
  }*/
  
  Serial.print("Contador encoder esquerdo: ");  Serial.println (encoder0Pos, DEC);
  Serial.print("Contador encoder direito: ");   Serial.println (encoder1Pos, DEC);
  Serial.print("Potencia direita: ");           Serial.println(pot_direita);
  Serial.print("Potencia esquerda: ");          Serial.println(pot_esquerda);
  Serial.println(" ");
 
  //delay(100);
  
}
