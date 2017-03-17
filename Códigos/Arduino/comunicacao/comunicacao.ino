float enviar=10.2;
int comeco = 1;
float enviar2=10.2;
long time_out = 0;

union mandar{
  float a;
  byte b[4];  
};

union receber{
  float a;
  byte b[4];  
};

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(4800);
  Serial.begin(9600);
}

void loop() {
  time_out = millis() - time_out;
  receber esq;
  receber dir;
  mandar esquerda;
  mandar direita;

  direita.a = enviar2--;
  esquerda.a = enviar++;
  // put your main code here, to run repeatedly:

  if (comeco == 1 || time_out > 1500){
    Serial.println("Comecei a mandar");
    Serial3.flush();
    Serial3.write("e");
    Serial3.write(esquerda.b,4);
    
    Serial3.write("d");
    Serial3.write(direita.b,4);
    Serial.println("Mandei");
    comeco = 0;
  }

/*  Serial.print(var.b[0]);
  Serial.print(var.b[1]);
  Serial.print(var.b[2]);
  Serial.println(var.b[3]);*/


  if (Serial3.available() > 0) {
    char bytes[4];
    char teste1 = Serial3.read();

    if (teste1 == 'b'){
      Serial3.readBytes(esq.b,4);
      Serial.println(teste1);
      Serial.print("Recebido: ");
      Serial.println(esq.a);
  
      char teste2 = Serial3.read();
      Serial3.readBytes(dir.b,4);
      Serial.println(teste2);
      Serial.print("Recebido dir: ");
      Serial.println(dir.a);
        
      Serial3.write("e");
      Serial3.write(esquerda.b,4);
      
      Serial3.write("d");
      Serial3.write(direita.b,4);
      time_out = millis();
    }
    
  
  }

    delay(100);
}
