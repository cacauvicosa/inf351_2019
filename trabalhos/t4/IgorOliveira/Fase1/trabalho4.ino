#include <Adafruit_NeoPixel.h>


#define PIN 2	 // input pin Neopixel is attached to
#define N 5
#define M 4
#define NUMPIXELS      30 // number of neopixels in Table





Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // timing delay
int redColor = 255;
int greenColor = 20;
int blueColor = 47;
void setup()
{
  pixels.begin();
  Serial.begin(9600);
 
}



void verifica_par(int *a,int i){
  if(a[i] == 1){
    	pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(delayval); // Delay for a period of time (in milliseconds).

    }else{
      pixels.setPixelColor(i, pixels.Color(0, 0,0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(delayval); // Delay for a period of time (in milliseconds).
    
    }
}

void verifica_impar(int *a,int j ,int i){
    
    if(a[j] == 1){
          pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor)); // Moderately bright green color.

          pixels.show(); // This sends the updated pixel color to the hardware.

          delay(delayval); // Delay for a period of time (in milliseconds).

      }else{
        pixels.setPixelColor(i, pixels.Color(0, 0,0)); // Moderately bright green color.

          pixels.show(); // This sends the updated pixel color to the hardware.

          delay(delayval); // Delay for a period of time (in milliseconds).
    }

  

}
  

  
  


void acende(int *a){
  int j = 0;
  int count = 0;
  for(int i = 0; i < N; i++){
    if(i%2 == 0){
      j = i*M;
      for (;j<= ((i*M) +(M -1)); j++){
        count++;

        verifica_par(a,j);
      }
    }
    else if (i%2 == 1){
      j = ((i*M)+(M-1));
      for (;j >= i * M; j--)
      {
            Serial.println(j);

           verifica_impar(a,j,count);
                count++;

      }
    }
      
    
  }
  delay(6000);
  apaga();
}
void apaga(){
  for(int i = 0; i < NUMPIXELS; i++){
  		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(delayval); // Delay for a period of time (in milliseconds).
  }
  
}


  

int f[20] = {0,1,1,1,
             0,1,0,0,
             0,1,1,0,
             0,1,0,0,
             0,1,0,0,
             };

int g[20] = {0,1,1,1,
             1,0,0,0,
             1,0,1,1,
             1,0,0,1,
             0,1,1,1};

int h[20] = {1,0,0,1,
             1,0,0,1,
             1,1,1,1,
             1,0,0,1,
             1,0,0,1};

int i[20] = {0,1,1,1,
             0,0,1,0,
             0,0,1,0,
             0,0,1,0,
             0,1,1,1};

int j[20] = { 0,1,1,1,
              0,0,0,1,
              0,0,0,1,
              1,0,0,1,
              0,1,1,0};

void print(char l){
    switch (l){
      case 'f': acende(f);
      case 'g': acende(g);
      case 'h': acende(h);
      case 'i': acende(i);
      case 'j': acende(j);
    }
  
}

void loop()
{
  
  print('f');
  delay(2000);
  
  print('g');
  delay(2000);

  print('h');
  delay(2000);

  print('i');
  delay(2000);

  print('j');
  delay(2000);



}