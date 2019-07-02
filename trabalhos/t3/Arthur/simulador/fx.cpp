#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#define M_MAX 300

int screenW = 600;
int screenH = 480;
float M[M_MAX][M_MAX][3] = { 0 };
float RM[M_MAX][M_MAX][3] = { 0 };

int MAT_COLS_FX = 12;
int MAT_LINES_FX = 12;
int LED_COUNT_FX = 144;

int orthoX;
int orthoY;

int lineL = 10;
int colL  = 10;

int min(int a, int b) { return a<b?a:b; }
int max(int a, int b) { return a>b?a:b; }
float minf(float a, float b) { return a<b?a:b; }
float maxf(float a, float b) { return a>b?a:b; }

void show() { int i, j, k; for(i = 0; i < MAT_LINES_FX; i++) for(j = 0; j < MAT_COLS_FX; j++) for(k = 0; k < 3; k++) RM[i][j][k] = M[i][j][k]; }

void delay(int t) { usleep(t * 1000); }
void begin() { }

void paint( int i, int j, float _r, float _g, float _b ) {

	int geo_i = i * lineL;
	int geo_j = j * colL;
	
	glColor3f(_r, _g, _b);
	glBegin(GL_TRIANGLES);	
		glVertex2d(geo_i, geo_j);
		glVertex2d(geo_i, geo_j + colL);
		glVertex2d(geo_i + lineL, geo_j + colL);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2d(geo_i + lineL, geo_j + colL);
		glVertex2d(geo_i + lineL, geo_j);
		glVertex2d(geo_i, geo_j);
	glEnd();
	
	glLineWidth(1);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(geo_i, geo_j);
		glVertex2d(geo_i, geo_j + colL);
		glVertex2d(geo_i + lineL, geo_j + colL);
		glVertex2d(geo_i + lineL, geo_j);
	glEnd();
	
	glFlush();
}

void draw_matrix ()  { 

	int i, j;

	for(i = 0; i < MAT_LINES_FX; i++)
		for(j = 0; j < MAT_COLS_FX; j++)
			paint(j, i, RM[i][j][0], RM[i][j][1], RM[i][j][2]);

}


void refresh_screen(void) {

	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	
	draw_matrix();
	
	glColor3f(0.0f,0.0f,0.0f);
	glutSwapBuffers();
	
	glutPostRedisplay();
}

void setup();
void loop ();

void * fx_loop (void *p) {
//	sleep(1);
//	setup();

	while( 1 ) loop();
	
	return NULL;
}

#define LOW 0
#define HIGH 1

int keys_fx[255] = { 0 };
int n_pins_fx[255] = { 0 };
int keys_to_pins_fx[255][500];

int interrupt_pins_fx[500];
int n_interrupt_pins_fx;

void *rising_interrupt_func_fx[255] = { NULL };

int digitalRead(int c) { return keys_fx[c] > 0; }
void digitalWrite(int c, int VAL) { if(VAL) ++keys_fx[c]; else keys_fx[c] = LOW; }

void key_handler( unsigned char c, int x, int y ) {
	int i;
	
	n_interrupt_pins_fx = 0;
	for(i = 0; i < n_pins_fx[c]; i++) {
		if(rising_interrupt_func_fx[keys_to_pins_fx[c][i]] != NULL && keys_fx[keys_to_pins_fx[c][i]] == 0) { interrupt_pins_fx[n_interrupt_pins_fx++] = keys_to_pins_fx[c][i]; }
		++keys_fx[keys_to_pins_fx[c][i]];
	}
	
	for(i = 0; i < n_interrupt_pins_fx; i++) {
		(*((void (*)(void))rising_interrupt_func_fx[interrupt_pins_fx[i]]))();
	}
	
}

void up_key_handler( unsigned char c, int x, int y) {
	for(int i = 0; i < n_pins_fx[c]; i++) {
		--keys_fx[keys_to_pins_fx[c][i]];
	}
}

#define INPUT_PULLDOW 0
#define INPUT_PULLUP 0
#define INPUT 0
#define OUTPUT 0
void pinMode(int a, int b) { };

int digitalPinToInterrupt(int pin) { return pin; }

#define RISING 0
#define FALLING 0
#define CHANGE 0
void attachInterrupt(int pin, void (*callback) (void), int mode) {
	rising_interrupt_func_fx[pin] = (void *) callback;
}

void init_pins() {
	FILE *f;
	f = fopen("digital_input.config", "r");
	char line[200];
	unsigned char key;
	int pin;
	
	if(f == NULL) {
		printf("No input!\n");
		return;
	}
	
	while(fgets(line, 200, f)) {
		unsigned int read_offset;
		unsigned int bytes_read = 0;
		sscanf(line, "%c%n", &key, &bytes_read);
		read_offset = bytes_read;
		while(sscanf(line + read_offset, "%d%n", &pin, &bytes_read) == 1) {
			read_offset += bytes_read;
			keys_to_pins_fx[key][n_pins_fx[key]++] = pin;
		}
	}
	
	for(int i = 0; i < 255; i++) {
		if(n_pins_fx[i]) {
			printf("%c ->", i);
			for(int j = 0; j < n_pins_fx[i]; j++)
				printf(" %d", keys_to_pins_fx[i][j]);
			printf("\n");
		}
	}
}

void init_grid()
{
	FILE *f;
	f = fopen("grid_dim.config", "r");
	
	int lines, cols;
	if(f != NULL)
	{
		if(fscanf(f, "%dx%d", &lines, &cols) == 2)
		{
			if(lines && cols)
			{
				MAT_LINES_FX = lines;
				MAT_COLS_FX  = cols;
			}
		}
	}
}

int main (int argc, char *argv[]) {
	
	
	init_pins();
	init_grid();
	setup();
	orthoX = 10 * MAT_COLS_FX;
	orthoY = 10 * MAT_LINES_FX;
	LED_COUNT_FX = MAT_COLS_FX * MAT_LINES_FX;
	
	glutInit(&argc, argv);
	
	pthread_t fx_thread;
	pthread_create(&fx_thread, NULL, fx_loop, NULL);

	// Dois buffers, janela 600x450
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenW, screenH);
	glutInitWindowPosition(10,10);
	glutCreateWindow("SpecialFX");
	
	glMatrixMode(GL_PROJECTION);
	glViewport (0, 0, orthoX, orthoY);
	gluOrtho2D (0, orthoX, orthoY, 0 );
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	
	glutDisplayFunc(refresh_screen);
	glutKeyboardFunc(key_handler);
	glutKeyboardUpFunc(up_key_handler);
	
	glutMainLoop();

	return 0;
	
}

int analogRead(int a) { return a; }

void randomSeed(int a) { srand(time(NULL)); }

int random(int n) { return rand() % n; }

#define NEO_KHZ800 0
#define NEO_KHZ400 0
#define NEO_GRB 0
#define NEO_RGB 0
#define NEO_RGBW 0

void set_grid_dims(int lines, int cols) { MAT_LINES_FX = lines; MAT_COLS_FX = cols; LED_COUNT_FX = lines * cols; }
void set_num_cols(int cols) { MAT_COLS_FX = cols; MAT_LINES_FX = LED_COUNT_FX / cols; }
void set_num_lines(int lines) { MAT_LINES_FX = lines; MAT_COLS_FX = LED_COUNT_FX / lines; }


class Adafruit_NeoPixel { 

	private :
		
		float stripMAT[M_MAX][M_MAX][3] = { 0 };

	public :
	
		Adafruit_NeoPixel() { /* LED_COUNT_FX = 144; MAT_LINES_FX = 12; MAT_COLS_FX = 12; */}
	
		Adafruit_NeoPixel(int led_count, int led_pin, int garbage) {
		/*	int t_lines;
			int t_cols;
			int closest = 0x7FFFFFFF;
			MAT_LINES_FX = 12;
			MAT_COLS_FX = 12;
			
			LED_COUNT_FX = led_count;
			
			for(t_lines = 1; t_lines < LED_COUNT_FX; t_lines++) {
				if(led_count % t_lines) continue;
				t_cols = led_count / t_lines;
				if(abs(t_lines - t_cols) < closest) {
					MAT_LINES_FX = t_lines;
					MAT_COLS_FX = t_cols;
					closest = abs(t_lines - t_cols);
				}
			}
		*/
		}
	
		Adafruit_NeoPixel(const Adafruit_NeoPixel &p) {
			for(int i = 0; i < LED_COUNT_FX; i++) {
				int l = i / MAT_COLS_FX;
				int c = (l%2)?(MAT_COLS_FX - (i % MAT_COLS_FX) - 1):(i % MAT_COLS_FX);
				for(int k = 0; k < 3; k++) stripMAT[l][c][k] = p.stripMAT[l][c][k];
			}
		}
	
		Adafruit_NeoPixel & operator=(const Adafruit_NeoPixel &p) {
			for(int i = 0; i < LED_COUNT_FX; i++) {
				int l = i / MAT_COLS_FX;
				int c = (l%2)?(MAT_COLS_FX - (i % MAT_COLS_FX) - 1):(i % MAT_COLS_FX);
				for(int k = 0; k < 3; k++) stripMAT[l][c][k] = p.stripMAT[l][c][k];
			}
			
			return *this;
		}
	
		void begin() { }
		void clear() { int i, j, k; for(i = 0; i < MAT_LINES_FX; i++) for(j = 0; j < MAT_COLS_FX; j++) for(k = 0; k < 3; k++) stripMAT[i][j][k] = 0; }
		void show()  { int i, j, k; for(i = 0; i < MAT_LINES_FX; i++) for(j = 0; j < MAT_COLS_FX; j++) for(k = 0; k < 3; k++) RM[i][j][k] = stripMAT[i][j][k]; }
		
		void setPixelColor( int n, int r, int g, int b ) { 
		
			int i, j;
	
			i = n / MAT_COLS_FX;
			j = (i%2)?(MAT_COLS_FX - (n % MAT_COLS_FX) - 1):(n % MAT_COLS_FX);
			
			stripMAT[i][j][0] = (float) r / 255.0;
			stripMAT[i][j][1] = (float) g / 255.0;
			stripMAT[i][j][2] = (float) b / 255.0;
		
		}
		
		void setPixelColor( int n, int color ) { 
		
			int i, j;
			int r = (color & 0xFF0000) >> 16;
			int g = (color & 0x00FF00) >> 8;
			int b = color & 0x0000FF;
	
			i = n / MAT_COLS_FX;
			j = (i%2)?(MAT_COLS_FX - (n % MAT_COLS_FX) - 1):(n % MAT_COLS_FX);
			
			stripMAT[i][j][0] = (float) r / 255.0;
			stripMAT[i][j][1] = (float) g / 255.0;
			stripMAT[i][j][2] = (float) b / 255.0;
		
		}
		
		int getPixelColor( int n ) {
			int i, j;
			
			i = n / MAT_COLS_FX;
			j = (i%2)?(MAT_COLS_FX - (n % MAT_COLS_FX) - 1):(n % MAT_COLS_FX);
			
			return (((int) (stripMAT[i][j][0] * 255)) << 16) + (((int) (stripMAT[i][j][1] * 255)) << 8) + (int) (stripMAT[i][j][2] * 255);
		}
		
		int Color( int r, int g, int b) {
			return (r << 16) | (g << 8) | b;
		}
		
		void fill(int r, int g, int b) { 
			int i, j, k; 
			for(i = 0; i < MAT_LINES_FX; i++) 
				for(j = 0; j < MAT_COLS_FX; j++) 
					for(k = 0; k < 3; k++) { 
						stripMAT[i][j][0] = (float) r / 255.0;
						stripMAT[i][j][1] = (float) g / 255.0;
						stripMAT[i][j][2] = (float) b / 255.0;
					} 
		}
		
		void fill(int color) { 
			int i, j, k;
			
			int r = (color & 0xFF0000) >> 16;
			int g = (color & 0x00FF00) >> 8;
			int b = color & 0x0000FF;
			
			for(i = 0; i < MAT_LINES_FX; i++) 
				for(j = 0; j < MAT_COLS_FX; j++) 
					for(k = 0; k < 3; k++) { 
						stripMAT[i][j][0] = (float) r / 255.0;
						stripMAT[i][j][1] = (float) g / 255.0;
						stripMAT[i][j][2] = (float) b / 255.0;
					}
		}

};
