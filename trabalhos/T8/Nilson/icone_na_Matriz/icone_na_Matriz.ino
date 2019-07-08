#include <Adafruit_NeoPixel.h>
#define LED_PIN 1 //D3
#define ROWS 12
#define COLS 12
#define LED_COUNT 144

#define UP	7 //D6
#define DOWN	6 //D5
#define LEFT	5 // D8
#define RIGHT	4 //D7
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
////////////////////////////////////////////////////////////////////
//COLE O CODIGO AQUI


                     
/////////////////////////////////////////////////////////////////////////
void print_tela(){
    for(int i=0;i<12;i++)
     for(int j=0;j<12;j++)
            jogo.setPixelColor(MAT[i][j],jogo.Color(r[i][j],g[i][j],b[i][j]));
         
}


void loop() {

  jogo.clear();

  print_tela();

  jogo.show();

  delay(20);
  
}
