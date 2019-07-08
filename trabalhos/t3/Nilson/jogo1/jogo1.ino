#include <Adafruit_NeoPixel.h>
#define LED_PIN 1 //D3
#define ROWS 12
#define COLS 12
#define LED_COUNT 144

#define UP  7 //D6
#define DOWN  6 //D5
#define LEFT  5 // D8
#define RIGHT 4 //D7
#define INTERRUPT 2

void setup() {
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
}

Adafruit_NeoPixel jogo(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned int MAT[12][12]{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
                          23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
                          24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                          47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36,
                          48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                          71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60,
                          72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
                          95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,
                          96, 97, 98, 99,100,101,102,103,104,105,106,107,
                         119,118,117,116,115,114,113,112,111,110,109,108,
                         120,121,122,123,124,125,126,127,128,129,130,131,
                         143,142,141,140,139,138,137,136,135,134,133,132,
                     };

bool PAREDE[12][12]{};

int y=7,time_parede=0,time_rand=0,time_tiros=0,z=0;
bool perdeu =false;

struct Tiros{
  int x1=9,y1=6;
  bool bateu = false;
  bool disponivel = true;

};

Tiros tiros[12];

void imprime_parede(){
  for(int m=0;m<12;m++)
   for(int n=1;n<11;n++)
     if(PAREDE[m][n]==true)
       jogo.setPixelColor(MAT[m][n],0xCCB0);
}

void reseta_tiro(int i){
  tiros[i].x1 = 9;
  tiros[i].disponivel=true;

}

void posi_tiros(int i ,int y){
    if(tiros[i].disponivel == true){
      reseta_tiro(i);
        tiros[i].y1 = y;
        tiros[i].disponivel = false;
      }
    }


void desce_parede(){
    for(int i=10;i>0;i--)
     for(int n=1;n<11;n++)
         PAREDE[i][n]=PAREDE[i-1][n];
}

void rand_bloco(){
    PAREDE[0][1+rand()%10] = true;
}

void imprime_carro(int y){
 jogo.setPixelColor(MAT[11][y],0x00FF00);
 jogo.setPixelColor(MAT[10][y],0x00FF00);
 jogo.setPixelColor(MAT[11][y-1],0x00FF00);
 jogo.setPixelColor(MAT[11][y+1],0x00FF00);
}

void loop() {
if(perdeu == false){
  if (digitalRead(LEFT) == HIGH && y>1) y--;
  else if (digitalRead(RIGHT) == HIGH && y<10) y++;

  jogo.clear();

  if(time_parede==0){
    rand_bloco();
    desce_parede();
    time_parede =42
    ;
  }
    time_parede--;

  if(time_tiros==0){
    for(int i=0;i<11;i++){
      posi_tiros(i,y);
    }
    time_tiros =1;
  }
  time_tiros--;

    if(tiros[z].disponivel == false){
        if(tiros[z].x1 < 0){
          tiros[z].disponivel=true;
        }
        else if(PAREDE[tiros[z].x1][tiros[z].y1]==true){
          PAREDE[tiros[z].x1][tiros[z].y1]=false;
          tiros[z].disponivel=true;
          z++;
        }
        else{
          jogo.setPixelColor(MAT[tiros[z].x1][tiros[z].y1],0xFF0000);
          tiros[z].x1--;
        }

    }

    if(z<12)z=0;
    else z++;
    for(int s=1;s<11;s++){
      if(PAREDE[10][s] == true) perdeu =true;
    }
    imprime_carro(y);
    imprime_parede();

jogo.show();

     delay(100);
}
else{
    for(int i=0;i<144;i++){
      jogo.setPixelColor(i,jogo.Color(i+1,i+5,i+20));
      jogo.show();
      if(digitalRead(UP)){
        for(int l=0;l<12;l++){
          tiros[l].x1=9;
          tiros[l].y1=6;
          tiros[l].bateu = false;
          tiros[l].disponivel = true;
        }
        y=7;time_parede=0;time_rand=0;time_tiros=0;z=0;
        perdeu =false;
        for(int i=10;i>0;i--)
         for(int n=1;n<11;n++)
             PAREDE[i][n]=false;
      }
      delay(20);
  }

}
}
