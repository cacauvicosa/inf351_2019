#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#define M_MAX 1000

int screenW = 600;
int screenH = 480;
float M[M_MAX][M_MAX][3] = { 0 };
float RM[M_MAX][M_MAX][3] = { 0 };

int MAT_COLS = 12;
int MAT_LINES = 12;
int LED_COUNT;

int orthoX;
int orthoY;

int lineL = 10;
int colL  = 10;

int min(int a, int b) { return a<b?a:b; }
int max(int a, int b) { return a>b?a:b; }
float minf(float a, float b) { return a<b?a:b; }
float maxf(float a, float b) { return a>b?a:b; }

void show() { int i, j, k; for(i = 0; i < MAT_LINES; i++) for(j = 0; j < MAT_COLS; j++) for(k = 0; k < 3; k++) RM[i][j][k] = M[i][j][k]; }

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

	for(i = 0; i < MAT_LINES; i++)
		for(j = 0; j < MAT_COLS; j++)
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

void add_M (int _r, int _g, int _b) {
	for(int i = 0; i < MAT_LINES; i++) {
		for(int j = 0; j < MAT_COLS; j++) {
			M[i][j][0] = minf(1.0, M[i][j][0] + (float) _r / 255.0);
			M[i][j][1] = minf(1.0, M[i][j][1] + (float) _g / 255.0);
			M[i][j][2] = minf(1.0, M[i][j][2] + (float) _b / 255.0);
		}	
	}
}

void set_M (int _r, int _g, int _b) {
	for(int i = 0; i < MAT_LINES; i++) {
		for(int j = 0; j < MAT_COLS; j++) {
			M[i][j][0] = (float) _r / 255.0;
			M[i][j][1] = (float) _g / 255.0;
			M[i][j][2] = (float) _b / 255.0;
		}	
	}
}

void inv_M () {
	for(int i = 0; i < MAT_LINES; i++) {
		for(int j = 0; j < MAT_COLS; j++) {
			M[i][j][0] = 1.0 - M[i][j][0];
			M[i][j][1] = 1.0 - M[i][j][1];
			M[i][j][2] = 1.0 - M[i][j][2];
		}	
	}

}

void inv_pixel_M( int i, int j ) {
	M[i][j][0] = 1.0 - M[i][j][0];
	M[i][j][1] = 1.0 - M[i][j][1];
	M[i][j][2] = 1.0 - M[i][j][2];
}

void inv_line_M ( int i ) {
	int j;
	for(j = 0; j < MAT_COLS; j++) {
		M[i][j][0] = 1.0 - M[i][j][0];
		M[i][j][1] = 1.0 - M[i][j][1];
		M[i][j][2] = 1.0 - M[i][j][2];
	}
}

void inv_col_M (int j ) {
	int i;
	for(i = 0; i < MAT_LINES; i++) {
		M[i][j][0] = 1.0 - M[i][j][0];
		M[i][j][1] = 1.0 - M[i][j][1];
		M[i][j][2] = 1.0 - M[i][j][2];
	}
}


void set_pixel_Mf( int i, int j, float _r, float _g, float _b) {
	
	M[i][j][0] = _r;
	M[i][j][1] = _g;
	M[i][j][2] = _b;
	
}

void set_line_Mf( int i, float _r, float _g, float _b ) {
	int j;
	for(j = 0; j < MAT_COLS; j++) {
		M[i][j][0] = _r;
		M[i][j][1] = _g;
		M[i][j][2] = _b;
	}
}

void set_col_Mf( int j, float _r, float _g, float _b ) {
	int i;
	for(i = 0; i < MAT_LINES; i++) {
		M[i][j][0] = _r;
		M[i][j][1] = _g;
		M[i][j][2] = _b;
	}		
}

void add_pixel_Mf( int i, int j, float _r, float _g, float _b ) {
	M[i][j][0] = minf(1.0, M[i][j][0] + _r);
	M[i][j][1] = minf(1.0, M[i][j][1] + _g);
	M[i][j][2] = minf(1.0, M[i][j][2] + _b);
}

void add_line_Mf( int i, float _r, float _g, float _b ) {
	int j = 0;
	for(j = 0; j < MAT_COLS; j++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + _r);
		M[i][j][1] = minf(1.0, M[i][j][1] + _g);
		M[i][j][2] = minf(1.0, M[i][j][2] + _b);
	}
}

void add_col_Mf( int j, float _r, float _g, float _b ) {
	int i = 0;
	for(i = 0; i < MAT_LINES; i++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + _r);
		M[i][j][1] = minf(1.0, M[i][j][1] + _g);
		M[i][j][2] = minf(1.0, M[i][j][2] + _b);
	}
}

void clear () { int i; for (i = 0; i < MAT_LINES; i++) set_line_Mf(i, 0, 0, 0); }

void set_pixel_M( int i, int j, int _r, int _g, int _b ) {
	
	M[i][j][0] = (float) _r / 255.0;
	M[i][j][1] = (float) _g / 255.0;
	M[i][j][2] = (float) _b / 255.0;
	
}

void set_line_M( int i, int _r, int _g, int _b ) {
	int j;
	for(j = 0; j < MAT_COLS; j++) {
		M[i][j][0] = (float) _r / 255.0;
		M[i][j][1] = (float) _g / 255.0;
		M[i][j][2] = (float) _b / 255.0;
	}
}

void set_col_M( int j, int _r, int _g, int _b ) {
	int i;
	for(i = 0; i < MAT_LINES; i++) {
		M[i][j][0] = (float) _r / 255.0;
		M[i][j][1] = (float) _g / 255.0;
		M[i][j][2] = (float) _b / 255.0;
	}		
}

void add_pixel_M( int i, int j, int _r, int _g, int _b ) {
	M[i][j][0] = minf(1.0, M[i][j][0] + (float) _r / 255.0);
	M[i][j][1] = minf(1.0, M[i][j][1] + (float) _g / 255.0);
	M[i][j][2] = minf(1.0, M[i][j][2] + (float) _b / 255.0);
}

void add_line_M( int i, int _r, int _g, int _b ) {
	int j = 0;
	for(j = 0; j < MAT_COLS; j++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + (float) _r / 255.0);
		M[i][j][1] = minf(1.0, M[i][j][1] + (float) _g / 255.0);
		M[i][j][2] = minf(1.0, M[i][j][2] + (float) _b / 255.0);
	}
}

void add_col_M( int j, int _r, int _g, int _b ) {
	int i = 0;
	for(i = 0; i < MAT_LINES; i++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + (float) _r / 255.0);
		M[i][j][1] = minf(1.0, M[i][j][1] + (float) _g / 255.0);
		M[i][j][2] = minf(1.0, M[i][j][2] + (float) _b / 255.0);
	}
}

int toint(char *s) {
	int i = 0;
	int r = 0;
	
	for(i = 0; s[i] != '\0'; i++) {
		if(s[i] < '0' || s[i] > '9') return -1;
		r *= 10;
		r += s[i] - '0';
	}
	
	return min(M_MAX-1, r);
}


void get_colors(char *p1, char *p2, char *p3, float *r, float *g, float *b) {
	if(strcmp(p1, "red") == 0) {
		*r = 1.0;
		*g = 0.0;
		*b = 0.0;
		return;
	}
	
	if(strcmp(p1, "green") == 0) {
		*r = 0.0;
		*g = 1.0;
		*b = 0.0;
		return;
	}
	else if(strcmp(p1, "blue") == 0) {
		*r = 0.0;
		*g = 0.0;
		*b = 1.0;
		return;
	}
	else if(strcmp(p1, "black") == 0 || strcmp(p1, "off") == 0) {
		*r = 0.0;
		*g = 0.0;
		*b = 0.0;
		return ;
	}

	*r = minf(1.0, (float) toint(p1) / 255.0);
	*g = minf(1.0, (float) toint(p2) / 255.0);
	*b = minf(1.0, (float) toint(p3) / 255.0);
	
}

void setup();
void loop ();

void * fx_loop (void *p) {
	sleep(1);
	setup();
	while( 1 ) loop();
	
	return NULL;
}

void key_handler( unsigned char c, int x, int y ) {
	switch(c) {
//	case GLUT_KEY_LEFT	:
	case 'a'		:
		dir = 'l';
		break;
//	case GLUT_KEY_RIGHT	:
	case 'd'		:
		dir = 'r';
		break;
//	case GLUT_KEY_UP	:
	case 'w'		:
		dir = 'u';
		break;
//	case GLUT_KEY_DOWN	:
	case 's'		:
		dir = 'd';
		break;
	}
}

int main (int argc, char *argv[]) {
	
	orthoX = 10 * MAT_COLS;
	orthoY = 10 * MAT_LINES;
	LED_COUNT = MAT_COLS * MAT_LINES;
	
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
	glutMainLoop();

	return 0;
	
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
		M[i][j][0] = (float) r / 255.0;
		M[i][j][1] = (float) g / 255.0;
		M[i][j][2] = (float) b / 255.0;
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
		M[i][j][0] = (float) r / 255.0;
		M[i][j][1] = (float) g / 255.0;
		M[i][j][2] = (float) b / 255.0;
	}
	
}

void add_line_range ( int i, int start, int end, int r, int g, int b ) {
	
	int j = 0;
	
	if(start > end) {
	
		j = start;
		start = end;
		end = j;
		
	}
	
	end = min(end, MAT_COLS);
	
	for(j = start; j < end; j++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + (float) r / 255.0);
		M[i][j][1] = minf(1.0, M[i][j][1] + (float) g / 255.0);
		M[i][j][2] = minf(1.0, M[i][j][2] + (float) b / 255.0);
	}

}

void add_col_range ( int j, int start, int end, int r, int g, int b ) {

	int i = 0;
	
	if(start > end) {
	
		j = start;
		start = end;
		end = j;
		
	}
	
	end = min(end, MAT_LINES);
	
	for(i = start; i < end; i++) {
		M[i][j][0] = minf(1.0, M[i][j][0] + (float) r / 255.0);
		M[i][j][1] = minf(1.0, M[i][j][1] + (float) g / 255.0);
		M[i][j][2] = minf(1.0, M[i][j][2] + (float) b / 255.0);
	}
	
}

void inv_line_range ( int i, int start, int end ) {
	
	int j;
	if(start > end) {
	
		j = start;
		start = end;
		end = j;
		
	}
	end = min(end, MAT_COLS);
	
	for(j = start; j < end; j++) {
		M[i][j][0] = 1.0 - M[i][j][0];
		M[i][j][1] = 1.0 - M[i][j][1];
		M[i][j][2] = 1.0 - M[i][j][2];
	}

}

void inv_col_range ( int j, int start, int end ) {

	int i = 0;
	if(start > end) {
	
		j = start;
		start = end;
		end = j;
		
	}
	end = min(end, MAT_LINES);
	
	for(i = start; i < end; i++) {
		M[i][j][0] = 1.0 - M[i][j][0];
		M[i][j][1] = 1.0 - M[i][j][1];
		M[i][j][2] = 1.0 - M[i][j][2];
	}

}

void set_strip ( int n, int r, int g, int b ) {
	int i, j;
	
	i = n / MAT_COLS;
	j = (i%2)?(MAT_COLS - (n % MAT_COLS) - 1):(n % MAT_COLS);
	
	M[i][j][0] = (float) r / 255.0;
	M[i][j][1] = (float) g / 255.0;
	M[i][j][2] = (float) b / 255.0;

}

int analogRead(int a) { return a; }

void randomSeed(int a) { srand(time(NULL)); }

int random(int n) { return rand() % n; }

#define LED_PIN 0
#define NEO_KHZ800 0
#define NEO_KHZ400 0
#define NEO_GRB 0
#define NEO_RGB 0
#define NEO_RGBW 0

class Adafruit_NeoPixel { 

	public :
	
		Adafruit_NeoPixel(int, int, int) { }
	
		void begin() { }
		void clear() { int i; for (i = 0; i < MAT_LINES; i++) set_line_Mf(i, 0, 0, 0); }
		void show()  { int i, j, k; for(i = 0; i < MAT_LINES; i++) for(j = 0; j < MAT_COLS; j++) for(k = 0; k < 3; k++) RM[i][j][k] = M[i][j][k]; }
		
		void setPixelColor( int n, int r, int g, int b ) { 
		
			int i, j;
	
			i = n / MAT_COLS;
			j = (i%2)?(MAT_COLS - (n % MAT_COLS) - 1):(n % MAT_COLS);
			
			M[i][j][0] = (float) r / 255.0;
			M[i][j][1] = (float) g / 255.0;
			M[i][j][2] = (float) b / 255.0;
		
		}
		
		void setPixelColor( int n, int color ) { 
		
			int i, j;
			int r = (color & 0xFF0000) >> 16;
			int g = (color & 0x00FF00) >> 8;
			int b = color & 0x0000FF;
	
			i = n / MAT_COLS;
			j = (i%2)?(MAT_COLS - (n % MAT_COLS) - 1):(n % MAT_COLS);
			
			M[i][j][0] = (float) r / 255.0;
			M[i][j][1] = (float) g / 255.0;
			M[i][j][2] = (float) b / 255.0;
		
		}
		
		int getPixelColor( int n ) {
			int i, j;
			
			i = n / MAT_COLS;
			j = (i%2)?(MAT_COLS - (n % MAT_COLS) - 1):(n % MAT_COLS);
			
			return (((int) (M[i][j][0] * 255)) << 16) + (((int) (M[i][j][1] * 255)) << 8) + (int) (M[i][j][2] * 255);
		}
		
		int Color( int r, int g, int b) {
			return (r << 16) | (g << 8) | b;
		}

};
