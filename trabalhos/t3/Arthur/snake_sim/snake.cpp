
char dir = 's';
char last_dir = 's';

#include "snakefx.cpp"

#define ROWS 12
#define COLS 12

int map_px ( int l, int c ) {
	return l *  COLS + ((l % 2)?COLS-c-1:c);
}

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int snake_x = ROWS / 2;
int snake_y = COLS / 2;

int growing = 2;
int snake_size = 3;

int apple_x;
int apple_y;
int new_seed = 0;

uint32_t apple_color = 0xFF0000;
uint32_t snake_color = 0x00FF00;
uint32_t death_color = 0x0000FF;

#define MAX_SNAKE_SIZE 500
int snake[MAX_SNAKE_SIZE][2] = { 0 };
//int board[ROWS][COLS] = { 0 };

void setup () {
	
	MAT_COLS = COLS; // width
	MAT_LINES = ROWS; // height

	randomSeed(analogRead(0));
	
	apple_x = random(ROWS);
	apple_y = random(COLS);
	if(apple_x == snake_x) while(apple_y == snake_y) apple_y = random(COLS);
	
	for(int i = 0; i < snake_size; i++) {
		snake[i][0] = snake_x;
		snake[i][1] = snake_y;
	}

	strip.begin();

	strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);
	
	strip.show ();
	
}

void reset_game() {
	
	strip.setPixelColor(map_px(snake_x, snake_y), death_color);
	strip.show();
	
	delay(1000);
	
	dir = 's';
	last_dir = 's';
	
	snake_x = ROWS / 2;
	snake_y = COLS / 2;
	snake_size = 3;
	growing = 2;
	
	apple_x = random(ROWS);
	apple_y = random(COLS);
	new_seed = 0;
	if(apple_x == snake_x) while(apple_y == snake_y) apple_y = random(COLS);
	
	for(int i = 0; i < snake_size; i++) {
		snake[i][0] = snake_x;
		snake[i][1] = snake_y;
	}
	
	strip.clear();
	
	strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);
	
	strip.show();
	
}

void seed_apple() {
	apple_x = random(ROWS);
	apple_y = random(COLS);
	for(int i = 0; i < snake_size; i++) {
		if(apple_x == snake[i][0] && apple_y == snake[i][1]) {
			apple_x = random(ROWS);
			apple_y = random(COLS);
			i = 0;
		}
	}
	strip.setPixelColor(map_px(apple_x, apple_y), apple_color);
}

void move_snake(char c) {

	if(c == 'u' && last_dir == 'd') last_dir = 'd';
	else if(c == 'd' && last_dir == 'u') last_dir = 'u';
	else if(c == 'r' && last_dir == 'l') last_dir = 'l';
	else if(c == 'l' && last_dir == 'r') last_dir = 'r';
	else last_dir = c;
	
	switch(last_dir) { 
		case 'u' :
			snake_x = snake[0][0] - 1;
			snake_y = snake[0][1];
			if(snake_x == -1) snake_x = ROWS-1;
			break;
		case 'd' :
			snake_x = snake[0][0] + 1;
			snake_y = snake[0][1];
			if(snake_x == ROWS) snake_x = 0;
			break;
		case 'l' :
			snake_x = snake[0][0];
			snake_y = snake[0][1] - 1;
			if(snake_y == -1) snake_y = COLS-1;
			break;
		case 'r' :
			snake_x = snake[0][0];
			snake_y = snake[0][1] + 1;
			if(snake_y == COLS) snake_y = 0;
			break;
			
	}
	
	if(!growing) strip.setPixelColor(map_px(snake[snake_size-1][0], snake[snake_size-1][1]), 0);
	else --growing;
	
	if(snake_x == apple_x && snake_y == apple_y) {
		++growing;
		++snake_size;
		new_seed = 1;
	}
	
	for(int i = snake_size - 1; i > 0; i--) { 
		snake[i][0] = snake[i-1][0];
		snake[i][1] = snake[i-1][1];
		if(snake_x == snake[i][0] && snake_y == snake[i][1]) { reset_game(); return; }
	}
	
	snake[0][0] = snake_x;
	snake[0][1] = snake_y;
	
	
	if(new_seed) { seed_apple(); new_seed = 0; }
	
	strip.setPixelColor(map_px(snake_x, snake_y), snake_color);
}

void loop () {
	if(dir != 's') move_snake(dir);
	strip.show();
	delay(100 - snake_size / 5);
}
