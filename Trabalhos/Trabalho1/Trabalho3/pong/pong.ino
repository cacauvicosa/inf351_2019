#include <Adafruit_NeoPixel.h>


#define PIN 5

/*
  Ping Pong game
  NeoPixel adapt is used to play Ping Pong
  .
*/

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);


int pot1Pin = A4;                               // declaring the pin for player 1's potentiometer
int pot2Pin = A5;                               // declaring the pin for player 2's potentiometer

int image[12][12] = {                            // clear
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int death[12][12] = {                            // all on
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


int blank[12][12] = {                            // all off
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

long theTimer;                                           // timer variable

int gameState = 0;                                       // storing the game status
int animations = 300;                                    // storing the duration of the images between the games

float ballXSpeed = 1;                                    // storing the x acceleration
float ballXPosition = 6;                                 // storing the ball position as number

float ballYSpeed = 0;                                    // storing the y acceleration
float ballYPosition = 6;                                 // storing the ball position as number

int imageYPosition;                                      // storing the image position as number
int imageXPosition;                                      // storing the image position as number

int player1Position = 3;                                 // storing the paddle positoin of player 1
int player2Position = 3;                                 // storing the paddle positoin of player 2

int gameSpeed;                                           // storing the current game speed

void setup() {
  digitalWrite(PIN5, OUTPUT);
  strip.begin();
  strip.clear();
}

void draw() {
  for (int y = 0; y < 12; y++) {                          
    for (int x = 0; x < 12; x++) {                       
      if (image[x][y] == 1) {                            
        strip.setPixelColor(y*12+x, strip.Color(128, 0, 0));

      } else                                        
        strip.setPixelColor(y*12+x, strip.Color(0, 0, 0));
    }

  }
  strip.show();
}

void update() {
  switch (gameState) {                                   // switching game mode (called state machine)
    case 0:                                                // new game
      memcpy(image, blank, sizeof(blank));                 // clear screen
      gameSpeed = 300;                                     // set the game speed
      ballXPosition = 3;                                   // set ball position
      ballYPosition = 3;                                   // set ball position
      ballYSpeed = 0;                                      // ball should fly straight
      if (random(0, 2) > 0) {                              // but randomly left or right
        ballXSpeed = 1;
      } else {
        ballXSpeed = -1;
      }
      theTimer = millis();
      gameState = 1;
      break;
    case 1:                                                // game active
      image[player1Position][0] = 0;                       // paddle player 1 clear old position
      image[player1Position + 1][0] = 0;                   // paddle player 1 clear old position
      image[player2Position][11] = 0;                       // paddle player 2 clear old position
      image[player2Position + 1][11] = 0;                   // paddle player 2 clear old position

      player1Position = map(analogRead(pot1Pin), 0, 1023, 0, 10); // reading the position of player 1
      player2Position = map(analogRead(pot2Pin), 0, 1023, 0, 10); // reading the position of player 2

      image[player1Position][0] = 1;                       // paddle player 1 display
      image[player1Position + 1][0] = 1;                   // paddle player 1 display
      image[player2Position][11] = 1;                       // paddle player 2 display
      image[player2Position + 1][11] = 1;                   // paddle player 2 display

      if (millis() > theTimer + gameSpeed) {               // timer for game speed
        if (gameSpeed > 50) gameSpeed -= 3;                // accelerate game
        theTimer = millis();                               // set new timer
        image[imageYPosition][imageXPosition] = 0;         // overwrite old position
        ballXPosition += ballXSpeed;                       // update position
        ballYPosition += ballYSpeed;                       // update position

        if (ballYPosition >= 11) ballYSpeed *= -1;          // collision bottom border
        if (ballYPosition <= 0) ballYSpeed *= -1;          // collision top border

        ballYPosition = constrain(ballYPosition, 0, 11);    // constrain values between 0 and 7
        ballXPosition = constrain(ballXPosition, 0, 11);    // constrain values between 0 and 7
        imageYPosition = round(ballYPosition);
        imageXPosition = round(ballXPosition);

        if ((ballXPosition >= 10) && (image[imageYPosition][11] == 1)) { // if ball hits a paddle
          ballXSpeed *= -1;                                  // reflect the ball
          ballYSpeed = random(-2, 3);                        // random reflection angle
        }
        if ((ballXPosition <= 1) && (image[imageYPosition][0] == 1)) { // if ball hits a paddle
          ballXSpeed *= -1;                                  // reflect the ball
          ballYSpeed = random(-2, 3);                        // random reflection angle
        }
        if (ballXPosition >= 11) {                            // ball out
          gameState = 2;                                     // change status to lost game
          theTimer = millis();                               // new timer is set
        }

        if (ballXPosition <= 0) {                            // ball out
          gameState = 2;                                     // change status to lost game
          theTimer = millis();                               // new timer is set
        }

        image[imageYPosition][imageXPosition] = 1;           // set new image position

      }
      break;
    case 2:                                                  // game was lost
      if (millis() > theTimer + gameSpeed) {                 // wait for a short time
        theTimer = millis();
        gameState = 3;                                       // game state to lost game display
      }
      break;
    case 3:                                                  // lost game display
      memcpy(image, death, sizeof(death));                   // show image of lost game, memcpy is a function copying one array to another
      if (millis() > theTimer + animations) {                // wait again
        gameState = 0;                                       // game state change to »start a game«
      }
      break;
  }
}

void loop() {
  update();                                                // all calculations are in the update method
  draw();                                                  // all display methods are in here
}
