float teste=0;
void setup() { 
 Serial.begin(9600);
}
  
/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}
  
void loop() {
  if(Serial.available() > 0) {
    teste = Serial.parseFloat();  
    Serial.print("String recebida: ");Serial.println(teste);
  }
  
  // Se receber algo pela serial
  /*
  if (Serial.available() > 0){
    // Lê toda string recebida
    String recebido = leStringSerial();
    Serial.print("String recebida: ");Serial.println(recebido);
  }*/
}
