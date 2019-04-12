

void setup()
{
  pinMode(7, INPUT_PULLUP); // pino do botão
  pinMode(8, OUTPUT);       // led verde dos carros
  pinMode(9,OUTPUT);        // led vemelho dos carros  
  pinMode(10,OUTPUT);       // led amarelo dos carros  
  pinMode(11,OUTPUT);       // led vemelho dos pedestres
  pinMode(12,OUTPUT);       //  led verde dos pedestres  
  
 
}

void loop()
{
  
  if(digitalRead(7) == LOW) {
      delay(7000);			// tempo de transição para led amarelo
      digitalWrite(8,LOW);  // apaga o led verde
      digitalWrite(10,HIGH);// liga o led amerelo  
      delay(3000);          // tempo de transição para led  
      digitalWrite(10,LOW); // diesliga o led amarelo
      digitalWrite(11,LOW); // desliga o led vemelho dos pedestres  
      digitalWrite(9, HIGH); // liga o led vemelho dos carros
      digitalWrite(12,HIGH); // liga o led verdes dos pedestres
      delay(5000);		     // tempo de transiçãp para led		
      digitalWrite(12,LOW);
      digitalWrite(9, LOW);
 
   }
 
  else {
    digitalWrite(8, HIGH);
    digitalWrite(11, HIGH);
  }
}