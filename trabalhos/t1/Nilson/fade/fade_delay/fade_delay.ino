
int led = 2;
int brilho = 0; 
int cont = 15; 

void setup(){
  Serial.begin(9600);  
}

void loop()  {
  
  analogWrite(led,brilho);    
  
  brilho = brilho + cont;

  if (brilho == 0 || brilho == 255) {
    cont = -cont ;
  }    
  //usar delay para gerar um delay    
  delay(31);  
  Serial.println(cont);
  Serial.println(brilho);                        
}
