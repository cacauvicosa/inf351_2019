
int led = 2;
int brilho = 0; 
int cont = 15; 
int aux=2;

void setup(){
  Serial.begin(9600);  
}

void loop()  {
  
  analogWrite(led,brilho);    
  
  brilho = brilho + cont;

  if (brilho == 0 || brilho == 255) {
    cont = -cont ;
  }    

  //usar o for para gerar o dalay    
  for(int i=0 ; i < 1000000;i++)
      aux*=aux/3; 

  aux =2;
  Serial.println(cont);
  Serial.println(brilho);                        
}
