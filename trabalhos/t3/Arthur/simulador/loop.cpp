#include "fx.cpp"

#define LED_PIN 6
#define MAT_COLS 12
#define	MAT_LINES 12
#define LED_COUNT 144


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int map_px ( int l, int c ) {
	return l *  MAT_COLS + ((l % 2)?MAT_COLS-c-1:c);
}

void set_M(int _r, int _g, int _b) {
	for(int i = 0; i < LED_COUNT; i++) strip.setPixelColor(i, _r, _g, _b);
}
void add_M(int _r, int _g, int _b) {
	uint32_t pcolor;
	int r, g, b;
	for(int i = 0; i < LED_COUNT; i++) { 
		pcolor = strip.getPixelColor(i);
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(i, min(255, _r + r), min(255, _g + g), min(255, _b + b));
		
	}
}
void inv_M() {
	uint32_t pcolor;
	int r, g, b;
	for(int i = 0; i < LED_COUNT; i++) { 
		pcolor = strip.getPixelColor(i);
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(i, 255 - r, 255 - g, 255 - b);
	}
}
void set_pixel_M( int i, int j, int _r, int _g, int _b) {
	strip.setPixelColor(map_px(i, j), _r, _g, _b);
}
void set_line_M( int i, int _r, int _g, int _b ) {
	int l = i * MAT_COLS;
	for (int j = l + MAT_COLS; l < j; l++) 
		strip.setPixelColor(l, _r, _g, _b);
}
void set_col_M( int j, int _r, int _g, int _b ) {
	int i;
	for(i = 0; i < MAT_LINES; i++) {
		strip.setPixelColor(map_px(i, j), _r, _g, _b);
	}
}
void add_pixel_M( int i, int j, int _r, int _g, int _b ) {
	uint32_t pcolor = strip.getPixelColor(map_px(i, j));
	int r = (pcolor & 0xFF0000) >> 16;
	int g = (pcolor & 0x00FF00) >> 8;
	int b = pcolor & 0x0000FF;
	strip.setPixelColor(map_px(i, j), min(255, _r + r), min(255, _g + g), min(255, _b + b));	
}
void add_line_M( int i, int _r, int _g, int _b ) {
	int j = 0;
	int r, g, b;
	uint32_t pcolor;
	for(j = 0; j < MAT_COLS; j++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), min(255, _r + r), min(255, _g + g), min(255, _b + b));
	}
}
void add_col_M( int j, int _r, int _g, int _b ) {
	int i = 0;
	int r, g, b;
	uint32_t pcolor;
	for(i = 0; i < MAT_LINES; i++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), min(255, _r + r), min(255, _g + g), min(255, _b + b));
	}
}
void set_line_range ( int i, int start, int end, int r, int g, int b ) {
	int j = 0;
	if(start > end) {
		j = start;
		start = end;
		end = j;	
	}
	end = min(end, MAT_COLS);
	for(j = start; j < end; j++) {
		strip.setPixelColor(map_px(i, j), r, g, b);
	}

}
void set_col_range ( int j, int start, int end, int r, int g, int b ) {
	int i = 0;	
	if(start > end) {
		j = start;
		start = end;
		end = j;
	}
	end = min(end, MAT_LINES);
	for(i = start; i < end; i++) {
		strip.setPixelColor(map_px(i, j), r, g, b);
	}
	
}
void add_line_range ( int i, int start, int end, int _r, int _g, int _b ) {
	int j = 0;
	int r, g, b;
	uint32_t pcolor;
	if(start > end) {
		j = start;
		start = end;
		end = j;
	}
	end = min(end, MAT_COLS);	
	for(j = start; j < end; j++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), min(255, _r + r), min(255, _g + g), min(255, _b + b));
	}
}
void add_col_range ( int j, int start, int end, int _r, int _g, int _b ) {
	int i = 0;
	int r, g, b;
	uint32_t pcolor;
	if(start > end) {
		j = start;
		start = end;
		end = j;
	}
	end = min(end, MAT_LINES);
	for(i = start; i < end; i++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), min(255, _r + r), min(255, _g + g), min(255, _b + b));
	}
}
void inv_pixel_M( int i, int j ) {
	uint32_t pcolor = strip.getPixelColor(map_px(i, j));
	int r = (pcolor & 0xFF0000) >> 16;
	int g = (pcolor & 0x00FF00) >> 8;
	int b = pcolor & 0x0000FF;
	strip.setPixelColor(map_px(i, j), 255-r, 255-g, 255-b);
}
void inv_line_M ( int i ) {
	int j;
	int r, g, b;
	uint32_t pcolor;
	for(j = 0; j < MAT_COLS; j++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), 255-r, 255-g, 255-b);
	}
}
void inv_col_M (int j ) {
	int i;
	int r, g, b;
	uint32_t pcolor;
	for(i = 0; i < MAT_LINES; i++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), 255-r, 255-g, 255-b);
	}
}
void inv_line_range ( int i, int start, int end ) {
	int j;
	int r, g, b;
	uint32_t pcolor;
	if(start > end) {
		j = start;
		start = end;
		end = j;
	}
	end = min(end, MAT_COLS);
	for(j = start; j < end; j++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), 255-r, 255-g, 255-b);
	}
}
void inv_col_range ( int j, int start, int end ) {
	int i = 0;
	int r, g, b;
	uint32_t pcolor;
	if(start > end) {
		j = start;
		start = end;
		end = j;
	}
	end = min(end, MAT_LINES);
	for(i = start; i < end; i++) {
		pcolor = strip.getPixelColor(map_px(i, j));
		r = (pcolor & 0xFF0000) >> 16;
		g = (pcolor & 0x00FF00) >> 8;
		b = pcolor & 0x0000FF;
		strip.setPixelColor(map_px(i, j), 255-r, 255-g, 255-b);
	}
}
void set_strip ( int n, int r, int g, int b ) {
	strip.setPixelColor(n, r, g, b);
}




void setup () {
	
	attachInterrupt(2, inv_M, RISING);
	strip.begin();
	strip.show ();
	
}

void loop () {
	
	for(int j = 0; j < MAT_COLS; j++) {
		set_col_range(j, 0, j+1, 255, 0, 0);
		strip.show();
		delay(100);
	}
	
	for(int i = 0; i < MAT_LINES; i++) {
		int line  = MAT_LINES - i - 1;
		int start = 0;
		int end   = MAT_LINES - i;
		add_line_range(line, start, end, 0, 255, 0);
		strip.show();
		delay(100);
	}
		
	strip.clear();
	strip.show();
	delay(100);
	
	bool turn = true;
	bool black = false;
	for(int k = 0; k < LED_COUNT; k += 4) {
		int n = LED_COUNT / 2 - k - 3;
		if(k >= LED_COUNT / 4 && turn) { turn = false; black = !black; inv_M(); strip.show(); }
		black = !black;
		for(int i = 0, j = LED_COUNT-1; i < n; i++, j--) {
			if(i > 0) strip.setPixelColor(i-1, 255 * black, 255 * black, 255 * black);
			if(j < LED_COUNT-1) set_strip(j+1, 255 * black, 255 * black, 255 * black);
			strip.setPixelColor(i, 0, 0, 255);
			strip.setPixelColor(j, 255, 0, 0);
			strip.setPixelColor(i+1, 0, 0, 255);
			strip.setPixelColor(j-1, 255, 0, 0);
			strip.setPixelColor(i+2, 0, 0, 255);
			strip.setPixelColor(j-2, 255, 0, 0);
			strip.setPixelColor(i+3, 0, 0, 255);
			strip.setPixelColor(j-3, 255, 0, 0);
			strip.show();
			delay(20);
		}
	}
	
	delay(500);
	set_M(0, 0, 0);
	
}
