/*
 RC PulseIn Serial Read out
 By: Nick Poole
 SparkFun Electronics
 Date: 5
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */

#define PARAR 0
#define FRENTE 1
#define RE 2
#define ESQUERDA 3
#define DIREITA 4

char* direcoes[] = {"Parar", "Frente","Re","Esquerda","Direita"};
int ch1; // Here's where we'll keep our channel values
int ch2;
int ch3;
int direcao = 0;
int ch1vel=0;
int virada = 0;
int ch2vel = 0;

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



void setup() {
  pinMode(IN1_E, OUTPUT);
  pinMode(IN2_E, OUTPUT);
  pinMode(IN1_D, OUTPUT);
  pinMode(IN2_D, OUTPUT);
  pinMode(PWM_E, OUTPUT);
  pinMode(PWM_D, OUTPUT);
  pinMode(22, INPUT); // Set our input pins as such
  pinMode(24, INPUT);
  pinMode(26, INPUT);
  Serial.begin(9600); // Pour a bowl of Serial
}
void loop() {
  ch1 = pulseIn(22, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(24, HIGH, 25000); // each channel
  ch3 = pulseIn(26, HIGH, 25000);
  Serial.print("Channel 1: "); // Print the value of 
  Serial.println(ch1);        // each channel
  Serial.print("Channel 2: ");
  Serial.println(ch2);
  Serial.print("Channel 3: ");
  Serial.println(ch3);

  // Parte que acelera
  if(ch1!=0){
    if(ch1 < 1400){
      direcao = RE;
      ch1vel = (ch1-1400.0)/(950.0-1400.0)*50.0+100.0;
    }else if(ch1 > 1600){
      direcao = FRENTE;
      ch1vel = (float)((ch1-1600.0)/(2100.0-1600.0))*50.0+100.0;
    }else{
      direcao = PARAR;
      ch1vel = 0;
    }
  }
  // Parte que vira
  if(ch2!=0){
    if(ch2 < 1400){
      virada = ESQUERDA;
      ch2vel = (ch2-1400.0)/(900.0-1400.0)*100.0;
    }else if(ch2 > 1600){
      virada = DIREITA;
      ch2vel = (float)((ch2-1600.0)/(2100.0-1600.0))*100.0;
    }else{
      virada = FRENTE;
      ch2vel = 0;
    }
  }
  Serial.print("Direcao :");
  Serial.println(direcoes[direcao]);
  Serial.print("Velocidade ch1 :");
  Serial.println(ch1vel);
  Serial.print("Virada :");
  Serial.println(direcoes[virada]);
  Serial.print("Velocidade ch2 :");
  Serial.println(ch2vel);
  Serial.println("------------------------------");
  if(direcao == FRENTE){
    if(virada == FRENTE){
      frente(ch1vel,ch1vel);
    }else if(virada == DIREITA){
      if(ch2vel < 65){
        frente((1.0+ch2vel/100.0)*ch1vel,ch1vel);
      }
      else{
        direita(ch1vel,ch1vel); 
      }
    }else if(virada == ESQUERDA){
      if(ch2vel < 65){
        frente(ch1vel,(1.0+ch2vel/100.0)*ch1vel);
      }
      else{
        esquerda(ch1vel,ch1vel); 
      }
    }
  }else if(direcao == RE){
    if(virada == FRENTE){
      tras(ch1vel,ch1vel);
    }else if(virada == DIREITA){
      if(ch2vel < 65){
        tras(ch1vel,(1.0+ch2vel/100.0)*ch1vel);
      }
      else{
        esquerda(ch1vel,ch1vel); 
      }
    }else if(virada == ESQUERDA){
      if(ch2vel < 65){
        frente((1.0+ch2vel/100.0)*ch1vel,ch1vel);
      }
      else{
        direita(ch1vel,ch1vel); 
      }
    }    
  }else{
    parar();
  }
  delay(500); // I put this here just to make the terminal 
              // window happier
}
