/// Author: Raphael Nepomuceno <raphael.nepomuceno@protonmail.com>

#include <Adafruit_NeoPixel.h>

#define LED_PIN (8)

#define ROWS (6)
#define COLS (6)

#define CX (2)
#define CY (3)

#define MS_PER_TICK (50)
#define TICKS_PER_SWAP (100)

Adafruit_NeoPixel pixels =
    Adafruit_NeoPixel(ROWS * COLS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Helper functions {{{

#define IN_RANGE(__x, __lower, __upper) (__x >= __lower && __x < __upper)

/// Gets the value at the specified point. If the point is out of bounds,
/// returns 0.
unsigned char get_at(unsigned char *world, int x, int y, int columns,
                     int rows) {
  int at = y * rows + x;

  return IN_RANGE(at, 0, columns * rows) ? world[at] : 0;
}

/// Sets the value at the specified point. If the point is out of bounds, this
/// function does nothing.
void set_at(unsigned char *world, unsigned char value, int x, int y,
            int columns, int rows) {
  int at = y * rows + x;

  if (IN_RANGE(at, 0, columns * rows))
    world[at] = value;
}
// }}}

void setup() { pixels.begin(); }

bool increase = true;

unsigned char buf[ROWS * COLS] = {
    000, 000, 000, 000, 000, 000, //
    000, 000, 000, 000, 000, 000, //
    000, 000, 000, 000, 000, 000, //
    000, 000, 000, 000, 000, 000, //
    000, 000, 000, 000, 000, 000, //
    000, 000, 000, 000, 000, 000, //
};

char distance(char x, char y, char cx, char cy) {
  return abs(x - cx) + abs(y - cy);
}

void loop() {
  char reference = max(distance(0, 0, CX, CY),        // Top left
                       distance(ROWS, COLS, CX, CY)); // Bottom right

  for (int y = 0; y < ROWS; ++y)
    for (int x = 0; x < COLS; ++x) {
      char d = reference - distance(x, y, 2, 2);
      int color = get_at(buf, x, y, COLS, ROWS);

      if (increase)
        color += d;
      else
        color -= d;

      if (color > 255)
        color = 255;
      else if (color < 0)
        color = 0;

      set_at(buf, color, x, y, COLS, ROWS);

      // Color = 255 => Green
      // Color =   0 => Red
      set_pixel(x, y, 255 - color, color, 0);
    }

  unsigned char r = distance(0, 0, CX, CY) == reference
                        ? get_at(buf, 0, 0, COLS, ROWS)
                        : get_at(buf, COLS - 1, ROWS - 1, COLS, ROWS);

  if (r == 255 || r == 0)
    increase ^= true;

  pixels.show();

  delay(MS_PER_TICK);
}

void set_pixel(int x, int y, int r, int g, int b) {
  // Odd rows are counted backwartds.
  if (y % 2 == 1)
    x = (COLS - 1) - x;

  pixels.setPixelColor(COLS * y + x, pixels.Color(r, g, b));
}
