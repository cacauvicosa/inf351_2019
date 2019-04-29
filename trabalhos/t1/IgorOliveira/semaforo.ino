  int ESTADO_BOTAO = 0;
bool APERTOU = false;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  //pinMode(,OUTPUT);
 pinMode(3, INPUT); //Pino com botão será entrada

antes_apertar();
}
void antes_apertar(){
  APERTOU = false;
  	digitalWrite(13,LOW);
  	digitalWrite(9,LOW);
	digitalWrite(11,HIGH);
  	digitalWrite(12,HIGH);
  	
  
}
void pisca_semaforo(){
  for(int i=0;i<3;i++){
   digitalWrite(13,LOW);
   digitalWrite(9,LOW);

   delay(800);
   digitalWrite(13,HIGH);
   digitalWrite(9,HIGH);

   delay(800);
  }
}

void solicitar_passagem(){
  if(APERTOU){
    delay(5000);
    digitalWrite(11,LOW);
  	delay(200);
  	digitalWrite(10,HIGH);
	delay(2500);
  	digitalWrite(10,LOW);
  	delay(200);
  	digitalWrite(9,HIGH);
  	delay(500);
    digitalWrite(12,LOW);
		
  	digitalWrite(13,HIGH);
  	
  	delay(5000);
  	pisca_semaforo();
  	antes_apertar();
  }
    
  
  
}
void loop()
{
  //pisca_pedestre();
  ESTADO_BOTAO = digitalRead(3); //Armazena o Estado do botão.

if (ESTADO_BOTAO == HIGH && APERTOU == false) //Se botão estiver pressionado (LOW)
 {
 APERTOU = true;
 solicitar_passagem(); //Acende o led conectado ao pino 13
 }
 
  /*
  digitalWrite(13, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Wait for 1000 millisecond(s)*/
}