#include "../fx.cpp"

#define LED_PIN 1
#define ROWS 12
#define COLS 12
#define LED_COUNT 144

#define UP	7
#define DOWN	6
#define LEFT	5
#define RIGHT	4
#define CENTER  3

int map_px ( int l, int c ) {
	return l *  COLS + ((l % 2)?COLS-c-1:c);
}

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int apple_x;
int apple_y;
int new_seed = 0;

const uint32_t
wall	 		= 0xA3AEA6,
portal_in 		= 0x00F800,
portal_out	 	= 0x0000F8,
player			= 0x00FFFF,
vazio			= 0x000000,
red			= 0xFF0000,
green			= 0x00FF00,
blue			= 0x0000FF,
gold			= 0xFFDF00,
purple			= 0xFF00FF,
weak_red		= 0x220000,
weak_green		= 0x002200,
weak_blue		= 0x000022,
weak_gold		= 0x524200,
weak_purple		= 0x220022,

purple_switch		= 0xFE00FE,
glider			= 0x00FEFE,

pl_orelha		= 0x8F8F8F,
pl_cabeca		= 0xADADAD,
pl_olho			= 0x000000,
pl_bigode		= 0xE3E3E3,
pl_cenoura_cabo		= 0x098500,
pl_cenoura		= 0xFF8103,
pl_vazio		= 0xFFFFFF;

const uint32_t pernalonga[7][6] = 
{
	{pl_vazio, pl_orelha, pl_vazio, pl_orelha, pl_vazio, pl_vazio },
	{pl_vazio, pl_orelha, pl_vazio, pl_orelha, pl_vazio, pl_vazio },
	{pl_vazio, pl_orelha, pl_vazio, pl_orelha, pl_vazio, pl_vazio },
	{pl_vazio, pl_cabeca, pl_cabeca, pl_cabeca, pl_vazio, pl_cenoura_cabo },
	{pl_vazio, pl_olho, pl_cabeca, pl_olho, pl_vazio, pl_cenoura },
	{pl_bigode, pl_bigode, pl_bigode, pl_bigode, pl_bigode, pl_cenoura },
	{pl_bigode, pl_bigode, pl_bigode, pl_bigode, pl_bigode, pl_cenoura }
};

const uint32_t
jake_cabeca	= 0xFFD21C,
jake_olho	= 0xFFFFFF,
jake_bigode	= 0xD1AC17,
jake_focinho	= 0x000000;

const uint32_t jake[5][5] =
{
	{ jake_cabeca, jake_cabeca, jake_cabeca, jake_cabeca, jake_cabeca },
	{ jake_cabeca, jake_olho, jake_cabeca, jake_olho, jake_cabeca }, 
	{ jake_cabeca, jake_bigode, jake_focinho, jake_bigode, jake_cabeca },
	{ jake_cabeca, jake_bigode, jake_cabeca, jake_bigode, jake_cabeca },
	{ jake_cabeca, jake_cabeca, jake_cabeca, jake_cabeca, jake_cabeca }
};

const uint32_t
tnmt_cabeca		= 0x196606,
tnmt_olho		= 0xFFFFFF,
tnmt_leonardo		= 0x2E00E8,
tnmt_rafael		= 0xE80505,
tnmt_donatello		= 0x82127B,
tnmt_michelangelo	= 0xE8890E,
tnmt_vazio		= 0x000000;

void draw_tnmt(char turtle, int x, int y) {
	uint32_t t_cl;
	switch(turtle) {
		case 'l': t_cl = tnmt_leonardo; break;
		case 'r': t_cl = tnmt_rafael; break;
		case 'd': t_cl = tnmt_donatello; break;
		case 'm': t_cl = tnmt_michelangelo; break;
		default : return;
	}
	
	
	for(int i = x; i < 2; i++) {
		strip.setPixelColor(map_px(i, y), tnmt_vazio); 
	} 
	strip.setPixelColor(map_px(x+2, y), t_cl);
	
	for(int j = y+1; j <= y+5; j++) {
		strip.setPixelColor(map_px(x, j), tnmt_cabeca); 
		strip.setPixelColor(map_px(x+2, j), tnmt_cabeca); 		
	}
	
	
	strip.setPixelColor(map_px(x+1, y+1), t_cl);
	strip.setPixelColor(map_px(x+1, y+2), tnmt_olho);
	strip.setPixelColor(map_px(x+1, y+3), t_cl);
	strip.setPixelColor(map_px(x+1, y+4), tnmt_olho);
	strip.setPixelColor(map_px(x+1, y+5), t_cl);
}

#define MAZE_LINES 39
#define MAZE_COLUMNS 37
uint32_t maze[MAZE_LINES][MAZE_COLUMNS] = 
{ 
	#include "parcial_map"
};

int 
start_l = 37,
start_c = 18,

player_l,
player_c,

top_left_l,
top_left_c,

has_blue,
has_green,
has_red,
has_gold,
has_purple;


int centered;

uint32_t view[ROWS][COLS] = { 0 };

uint32_t menu[ROWS] = 
{ 	
	weak_blue, weak_blue, weak_blue, 
	weak_green, weak_green, weak_green,
	weak_red, weak_red, weak_red,
	weak_gold, weak_gold, weak_gold
};

int line_center = 8;
int col_center  = 5;
void center_screen() {
	if(player_l > MAZE_LINES - (ROWS - line_center)) { 
		top_left_l = MAZE_LINES - ROWS;
	} else if (player_l < line_center) {
		top_left_l = 0;
	} else {
		top_left_l = player_l - line_center;
	}
	if(player_c > MAZE_COLUMNS - (COLS - col_center)) { 
		top_left_c = MAZE_COLUMNS - COLS;
	} else if (player_c < col_center) {
		top_left_c = 0;
	} else {
		top_left_c = player_c - col_center;
	}
}

void change_all(uint32_t c1, uint32_t c2) {
	for(int i = 0; i < MAZE_LINES; i++) {
		for(int j = 0; j < MAZE_COLUMNS; j++) {
			if(maze[i][j] == c1) maze[i][j] = c2;
		}
	}
}

void swap_all(uint32_t c1, uint32_t c2) {
	for(int i = 0; i < MAZE_LINES; i++) {
		for(int j = 0; j < MAZE_COLUMNS; j++) {
			if(maze[i][j] == c1) maze[i][j] = c2;
			else if(maze[i][j] == c2) maze[i][j] = c1;
		}
	}
}

void draw_items() {
	for(int i = 0; i < ROWS; i++) {
		strip.setPixelColor(map_px(i, COLS-1), menu[i]);
	}
}

void set_collectibles() {
	switch(maze[player_l][player_c]) {
		case vazio : return;
		case red : 
			if(has_red) return; 
			has_red = 1; 
			change_all(weak_red, red); 
			menu[6] = menu[7] = menu[8] = red;
			break;
		case green :
			if(has_green) return;
			has_green = 1;
			change_all(weak_green, green);
			menu[3] = menu[4] = menu[5] = green;
			break;
		case blue :
			if(has_blue) return;
			has_blue = 1;
			change_all(weak_blue, blue);
			menu[0] = menu[1] = menu[2] = blue;
			break;
		case gold :
			if(has_gold) return;
			has_gold = 1;
			change_all(weak_gold, gold);
			menu[9] = menu[10] = menu[11] = gold;
			break;
		case purple :
			if(has_purple) return;
			swap_all(weak_purple, purple);
			break;
		case purple_switch :
			if(has_purple) return;
			has_purple = 1;
			change_all(weak_purple, purple);
			break;
	}
	
	draw_items();
}

void update_view() {

	if(centered) center_screen();	
	
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS-1; j++) {
			view[i][j] = maze[i+top_left_l][j+top_left_c];
		}
	}
	
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < COLS-1; j++) {
			strip.setPixelColor(map_px(i, j), view[i][j]);
		}
	}

	if(player_l >= top_left_l && player_l < top_left_l + ROWS 
	&& player_c >= top_left_c && player_c < top_left_c + COLS - 1) {
		strip.setPixelColor(map_px(player_l-top_left_l, player_c-top_left_c), player);
	}
	
	strip.show();
}

void setup () {

	pinMode(UP, INPUT);
	pinMode(DOWN, INPUT);
	pinMode(LEFT, INPUT);
	pinMode(RIGHT, INPUT);
	pinMode(CENTER, INPUT);
	strip.begin();

	centered = 1;	
	player_l = start_l;
	player_c = start_c;

	top_left_l = MAZE_LINES - ROWS;
	top_left_c = 13;
	
	has_blue = has_green = has_red = has_gold = has_purple = 0;
	
	draw_items();
	update_view();
	
	strip.show ();	
}

void reset_game() {
	
	
}

void screen_up() {
	if(top_left_l > 0) --top_left_l;
	update_view();
}

void screen_down() {
	if(top_left_l < MAZE_LINES - ROWS) ++top_left_l;
	update_view();
}
void screen_left() {
	if(top_left_c > 0) --top_left_c;
	update_view();
}
void screen_right() {
	if(top_left_c < MAZE_COLUMNS - COLS) ++top_left_c;
	update_view();
}

void player_up() {
	if(player_l > 0
	&&(maze[player_l-1][player_c] == vazio 
	|| maze[player_l-1][player_c] == blue 
	|| maze[player_l-1][player_c] == green
	|| maze[player_l-1][player_c] == red
	|| maze[player_l-1][player_c] == purple
	|| maze[player_l-1][player_c] == purple_switch
	|| maze[player_l-1][player_c] == gold) )
	{ 
		--player_l;
		set_collectibles();
		update_view();
	}
}
void player_down() {
	if(player_l < MAZE_LINES - 1
	&&(maze[player_l+1][player_c] == vazio 
	|| maze[player_l+1][player_c] == blue 
	|| maze[player_l+1][player_c] == green
	|| maze[player_l+1][player_c] == red
	|| maze[player_l+1][player_c] == purple
	|| maze[player_l+1][player_c] == purple_switch
	|| maze[player_l+1][player_c] == gold) )
	{ 
		++player_l;
		set_collectibles();
		update_view();
	}
}
void player_left() {
	if(player_c > 0
	&&(maze[player_l][player_c-1] == vazio 
	|| maze[player_l][player_c-1] == blue 
	|| maze[player_l][player_c-1] == green
	|| maze[player_l][player_c-1] == red
	|| maze[player_l][player_c-1] == purple
	|| maze[player_l][player_c-1] == purple_switch
	|| maze[player_l][player_c-1] == gold) )
	{
		--player_c;
		set_collectibles();
		update_view();
	}
}
void player_right() {
	if(player_c < MAZE_COLUMNS - 2
	&&(maze[player_l][player_c+1] == vazio 
	|| maze[player_l][player_c+1] == blue 
	|| maze[player_l][player_c+1] == green
	|| maze[player_l][player_c+1] == red
	|| maze[player_l][player_c+1] == purple
	|| maze[player_l][player_c+1] == purple_switch
	|| maze[player_l][player_c+1] == gold) )
	{
		++player_c;
		set_collectibles();
		update_view();
	}
}

void loop () {
	if(digitalRead(UP)) {
//		screen_up();
		player_up();
		delay(100);
	} else if(digitalRead(DOWN)) {
//		screen_down();
		player_down();
		delay(100);
	} else if(digitalRead(LEFT)) {
//		screen_left();
		player_left();
		delay(100);
	} else if(digitalRead(RIGHT)) {
//		screen_right();
		player_right();
		delay(100);
	} else if(digitalRead(CENTER)) {
		centered = 1 - centered;
		update_view();
		delay(100);
	}
//	strip.show();
}
