const int botao =13;
const int vermelho_car =12;
const int amarelo =11;
const int verde_car =10;
const int verde_pes =8;
const int vermelho_pes=9;

void setup()
{
  pinMode(botao, INPUT);
  pinMode(vermelho_car,OUTPUT);
  pinMode(amarelo,OUTPUT);
  pinMode(verde_car,OUTPUT);
  pinMode(verde_pes,OUTPUT);
  pinMode(vermelho_pes,OUTPUT);
  
  Serial.begin(9600);
  digitalWrite(verde_car,HIGH);
  digitalWrite(vermelho_pes,HIGH);
}

void loop()
{ 
  if(digitalRead(botao) == HIGH){
    Serial.println(digitalRead(botao));
    //tempo para mudar o sinal verde dos carros
    delay(2000);
    digitalWrite(verde_car,LOW);
    digitalWrite(amarelo, HIGH);
    delay(2000);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho_car,HIGH);
    
    //apos ter passado pelo amarelo e o vermelho, fica verde para os pedestres
    digitalWrite(vermelho_pes,LOW);
  	digitalWrite(verde_pes,HIGH);
 	
    //tempo para os pedestres passarem
    delay(5000);
    digitalWrite(verde_pes,LOW);
  	digitalWrite(vermelho_pes,HIGH);
    
    //liberando o sinal para os carros
    digitalWrite(vermelho_car,LOW);
    digitalWrite(verde_car,HIGH);
  	//cooldown para poder solicitar a passagen novamente
    delay(15000);
  }
}