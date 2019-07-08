/* 	O pino 1 é igual a o numero 7 
	e o pino 8 é o 0
*/

#define    clk      12
#define    latch    11
#define    data     8
//#include <LigaLed.h>

class LIGA_LED{
 public:
  static void liga_o_pino(unsigned int bit){

   digitalWrite(latch,LOW);

   for(int i=0; i < 8 ;i++){

     if(i == bit){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
      }

     else{
         digitalWrite(data,LOW);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
     }
   }

   digitalWrite(latch,HIGH);
 }
  static void liga_o_pino(unsigned int bit1,unsigned int bit2){

   digitalWrite(latch,LOW);

   for(int i=0; i < 8 ;i++){

     if(i == bit1){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
       }

     else if(i == bit2){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
       }

     else{
         digitalWrite(data,LOW);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
     }
   }
   digitalWrite(latch,HIGH);
 }
  static void liga_o_pino(unsigned int bit1,unsigned int bit2,unsigned int bit3){

   digitalWrite(latch,LOW);

   for(int i=0; i < 8 ;i++){

     if(i == bit1){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
       }

       else if(i == bit2){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
       }

       else if(i == bit3){
         digitalWrite(data,HIGH);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
       }

     else{
         digitalWrite(data,LOW);
         digitalWrite(clk ,HIGH);
         digitalWrite(clk ,LOW);
     }
   }
   digitalWrite(latch,HIGH);
 }

};

void testa(){
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, 32);
  digitalWrite(latch,HIGH);
  delay(1000);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, 1);
  digitalWrite(latch,HIGH);
  delay(1000);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, 128);
  digitalWrite(latch,HIGH);
  delay(1000);
  digitalWrite(latch,LOW);
  shiftOut(data, clk, MSBFIRST, rand()%128);
  digitalWrite(latch,HIGH);
  delay(1000);
}

void setup() 
{
  pinMode(clk,   OUTPUT);
  pinMode(data,  OUTPUT);
  pinMode(latch, OUTPUT);
  
  digitalWrite(latch,HIGH);
  digitalWrite(data,LOW);
  
  testa();
  delay(3000);
  LIGA_LED::liga_o_pino(0,4,5);
  delay(3000);
}

void loop() 
{ 
  LIGA_LED::liga_o_pino(rand()%7,rand()%7,rand()%7);
  delay(1000);
  LIGA_LED::liga_o_pino(rand()%7,rand()%7);
  delay(1000);
  LIGA_LED::liga_o_pino(rand()%7);
  delay(1000);
}
