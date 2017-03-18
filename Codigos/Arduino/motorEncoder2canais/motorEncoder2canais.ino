/* read a rotary encoder with interrupts
   Encoder hooked up with common to GROUND,
   encoder0PinA to pin 2, encoder0PinB to pin 4 (or pin 3 see below)
   it doesn't matter which encoder pin you use for A or B  

   uses Arduino pullups on A & B channel outputs
   turning on the pullups saves having to hook up resistors 
   to the A & B channel outputs 

*/ 

// Variáveis encoder

#define encoder0PinA 2
#define encoder0PinB 3

volatile long encoder0Pos = 0;
double voltas = 0;

//Variáveis driver

#define IN1_D 4 //laranjas
#define IN2_D 5 
#define IN1_E 6 //amarelos
#define IN2_E 7

#define PWM_D 10 //azul
#define PWM_E 11 //roxo

#define pot 50



void doEncoderA(){

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
  //Serial.println (encoder0Pos, DEC);          
  // use for debugging - remember to comment out
}

void doEncoderB(){

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
}


//Funções driver

void direita (int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW); 
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, LOW); 

}

void esquerda (int potEsquerda, int potDireita) {
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

void setup(){

pinMode(IN1_E, OUTPUT);
pinMode(IN2_E, OUTPUT);
pinMode(IN1_D, OUTPUT);
pinMode(IN2_D, OUTPUT);
pinMode(PWM_E, OUTPUT);
pinMode(PWM_D, OUTPUT);

pinMode(encoder0PinA, INPUT); 
pinMode(encoder0PinB, INPUT); 

// encoder pin on interrupt 0 (pin 2)
 attachInterrupt(0, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 3)
 attachInterrupt(1, doEncoderB, CHANGE);  
 
 Serial.begin (9600);
 Serial.println("Start");

}

void loop(){

delay(1000);
frente(pot,pot);
//delay(500);
delay(2000);
parar();
delay(3000);

voltas = encoder0Pos/1632.67;
Serial.println (encoder0Pos, DEC);
Serial.print ("VOLTAS: "); Serial.println (voltas); 
delay(400);

//delay(500);
//tras(pot,pot);
//delay(3000);
//parar();
//delay(500);
//direita(pot,pot);
//delay(3000);
//parar();
//delay(500);
//esquerda(pot,pot);
//delay(3000);
//parar();
//delay(500);


}



//Funções Encoder



