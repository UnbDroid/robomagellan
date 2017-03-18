

// Defines ----------------------------------------------------------------------------------------------------------
#define IN1_D 10
#define IN2_D 9
#define IN1_E 13
#define IN2_E 12

#define PWM_D 8
#define PWM_E 11

#define POT_MAX_ESQUERDA 150
#define POT_MAX_DIREITA 150
#define POT_MIN_ESQUERDA 10
#define POT_MIN_DIREITA 10

// Variaveis --------------------------------------------------------------------------------------------------------

float pot_direita = 0;
float pot_esquerda = 0;

float velocidade_ReferenciaEsquerda = 0;
float velocidade_ReferenciaDireita = 0;

bool forward_esquerda = true;
bool forward_direita = true;

// Funcoes -----------------------------------------------------------------------------------------------------------

void startDriver () {

  pinMode(IN1_E, OUTPUT);
  pinMode(IN2_E, OUTPUT);
  pinMode(IN1_D, OUTPUT);
  pinMode(IN2_D, OUTPUT);
  pinMode(PWM_E, OUTPUT);
  pinMode(PWM_D, OUTPUT);
}

void direitaEixo (int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW);
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, LOW);

}

void esquerdaEixo (int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, LOW);
  digitalWrite(IN2_E, HIGH);
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);

}

void frente(int potEsquerda, int potDireita) {
  analogWrite(PWM_E, potEsquerda);
  analogWrite(PWM_D, potDireita);
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, LOW);
  digitalWrite(IN1_D, LOW);
  digitalWrite(IN2_D, HIGH);
}

void tras(int potEsquerda, int potDireita) {
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

void travar () {
  digitalWrite(IN1_E, HIGH);
  digitalWrite(IN2_E, HIGH);
  digitalWrite(IN1_D, HIGH);
  digitalWrite(IN2_D, HIGH);
}

void setVelocidade() {
  
  if ((pot_esquerda > POT_MAX_ESQUERDA) && (velocidade_ReferenciaEsquerda > 0)) {
    pot_esquerda = POT_MAX_ESQUERDA;
    forward_esquerda = true;
  } 
  else if ((pot_esquerda < POT_MIN_ESQUERDA) && (velocidade_ReferenciaEsquerda > 0)) {
    pot_esquerda = POT_MIN_ESQUERDA;
    forward_esquerda = true;
  }
  else if ((-pot_esquerda > POT_MAX_ESQUERDA) && (velocidade_ReferenciaEsquerda < 0)) {
    pot_esquerda = POT_MAX_ESQUERDA;
    forward_esquerda = false;
  } 
  else if ((pot_esquerda < POT_MIN_ESQUERDA) && (velocidade_ReferenciaEsquerda < 0)) {
    if (abs(pot_esquerda) < POT_MIN_ESQUERDA){
      pot_esquerda = POT_MIN_ESQUERDA;
    }    
    forward_esquerda = false;
  }
  else if ((pot_esquerda > 0) && (velocidade_ReferenciaEsquerda < 0)) {
    pot_esquerda = POT_MIN_ESQUERDA;
    forward_esquerda = false;
  }

  if (pot_esquerda < 0 && velocidade_ReferenciaEsquerda < 0) {
    forward_esquerda = false;
    pot_esquerda = abs(pot_esquerda);
  }
  else if(pot_esquerda > 0 && velocidade_ReferenciaEsquerda > 0) {
    forward_esquerda = true;
  }

  
  if ((pot_direita > POT_MAX_DIREITA) && (velocidade_ReferenciaDireita > 0)) {
    pot_direita= POT_MAX_DIREITA;
    forward_direita = true;
  } 
  else if ((pot_direita < POT_MIN_DIREITA) && (velocidade_ReferenciaDireita > 0)) {
    pot_direita = POT_MIN_DIREITA;
    forward_direita = true;
  }
  else if ((-pot_direita > POT_MAX_DIREITA) && (velocidade_ReferenciaDireita < 0)) {
    pot_direita= POT_MAX_DIREITA;
    forward_direita = false;
  } 
  else if ((pot_direita < POT_MIN_DIREITA) && (velocidade_ReferenciaDireita < 0)) {
    if (abs(pot_direita) < POT_MIN_DIREITA){
      pot_direita = POT_MIN_DIREITA;
    }    
    forward_direita = false;
  }
  else if ((pot_direita > 0) && (velocidade_ReferenciaDireita < 0)) {
    pot_direita = POT_MIN_DIREITA;
    forward_direita = false;
  }
  
  if (pot_direita < 0 && velocidade_ReferenciaDireita < 0){
    forward_direita = false;
    pot_direita = abs(pot_direita);
  }
  else if (pot_direita > 0 && velocidade_ReferenciaDireita > 0){
    forward_direita = true;
  }
  
  if (forward_direita && forward_esquerda) {
    frente(pot_esquerda, pot_direita);
  }
  else if (!forward_direita && !forward_esquerda){
    tras(pot_esquerda, pot_direita);
  }
  else if(forward_direita && !forward_esquerda){
    esquerdaEixo(pot_esquerda, pot_direita);
  }
  else if  (!forward_direita && forward_esquerda){
    direitaEixo(pot_esquerda, pot_direita);  
  }
}
