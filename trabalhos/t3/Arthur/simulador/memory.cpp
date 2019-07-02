#include "fx.cpp"

#define LED_PIN 6
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


int32_t board[LED_COUNT] = { 0 };
int open[LED_COUNT] = { 0 };
int pooled[LED_COUNT] = { 0 };

int32_t possible_colors[LED_COUNT] = 
{
0xFF0000, 0x00FF00, 0x0000FF,
0xFFFF00, 0x00FFFF, 0xFF00FF, 0xFFA500, 0x0
};

int32_t colors_inc[LED_COUNT] = {
0x190000, 0x001900, 0x000019,
0x191900, 0x001919, 0x190019, 0x191000, 0x0
};

int32_t cursor_color_inc[LED_COUNT+1];

int cursor;
int pick1;
int pairs;
int up;
int32_t cursor_color = 0xFFFFFF;
int32_t default_cursor_color = 0xFFFFFF;

void reset_game() {
	int total_paired = 0;
	cursor = LED_COUNT/2;
	for(int i = 0; i < LED_COUNT; i++) open[i] = pooled[i] = 0;
	for(int i = 0; possible_colors[i]; i++) {
		int pair1 = random(LED_COUNT);
		int pair2 = random(LED_COUNT);
		
		while(pooled[pair1]) pair1 = random(LED_COUNT);
		pooled[pair1] = 1;
		board[pair1] = possible_colors[i];
		cursor_color_inc[pair1] = colors_inc[i];
		if(++total_paired == LED_COUNT) break;
		while(pooled[pair2]) pair2 = random(LED_COUNT);
		pooled[pair2] = 1;
		board[pair2] = possible_colors[i];
		cursor_color_inc[pair2] = colors_inc[i];
		if(++total_paired == LED_COUNT) break;
	}
	
	pick1 = -1;
	pairs = 0;
	up = 0;
	
	cursor_color_inc[LED_COUNT] = 0x191919;
	
	strip.setPixelColor(cursor, cursor_color);
}

void fade_correct() {
	int index = open[cursor]?cursor:LED_COUNT;
	if(++up > 5) {
		cursor_color += cursor_color_inc[index];
		if(up == 10) up = 0;
	} else {
		cursor_color -= cursor_color_inc[index];
	}
}

void show_board() {
	strip.clear();
	for(int i = 0; i < LED_COUNT; i++) {
		if(open[i]) strip.setPixelColor(i, board[i]);
	}
	strip.setPixelColor(cursor, cursor_color);
	fade_correct();
	strip.show();
}

void win_blink() {
	strip.clear();
	strip.show();
	delay(200);
	show_board();
	delay(200);
	strip.clear();
	strip.show();
	delay(200);
	show_board();
	delay(200);
	strip.clear();
	strip.show();
	delay(200);
	show_board();
	delay(200);
}

int is_move = 0;
void move() {
	if(digitalRead(5) == HIGH) {
		if(cursor == 0) cursor = LED_COUNT-1;
		else --cursor;
	} else if(digitalRead(4) == HIGH) {
		if(cursor == LED_COUNT-1) cursor = 0;
		else ++cursor;
	} else if(digitalRead(7) == HIGH) {
		if(!open[cursor]) {
			open[cursor] = 1;
			if(pick1 != -1) {
				if(board[cursor] != board[pick1]) {
					cursor_color = board[cursor];
					show_board();
					strip.show();
					delay(800);
					cursor_color = default_cursor_color;
					open[cursor] = 0;
					open[pick1]  = 0;
				} else {
					pairs += 2;
					if(pairs == LED_COUNT) { cursor_color = board[cursor]; cursor = LED_COUNT;
	strip.show(); delay(200); win_blink(); reset_game(); return; }
				}
				
				pick1 = -1;
				
			} else {
				pick1 = cursor;
			}
		}
	}
	
	if(open[cursor]) cursor_color = board[cursor];
	else cursor_color = default_cursor_color;
	up = 0;
	is_move = 0;
}

void to_move() {
	is_move = 1;
}

void setup() {

	set_num_lines(1);
	attachInterrupt(digitalPinToInterrupt(2), to_move, RISING);
	
	randomSeed(analogRead(0));
	strip.begin();

	reset_game();
	strip.show();
	
}

void loop () {
	show_board();
	if(is_move) move();
	delay(100);
}
