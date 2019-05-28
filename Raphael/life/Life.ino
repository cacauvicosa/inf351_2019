/// Author: Raphael Nepomuceno <raphael.nepomuceno@protonmail.com>

#include <Adafruit_NeoPixel.h>

#define LED_PIN (8)

#define ROWS (6)
#define COLS (6)

#define MS_PER_TICK (50)

Adafruit_NeoPixel pixels =
    Adafruit_NeoPixel(ROWS * COLS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() { pixels.begin(); }

// Conway's Game of Life {{{

#define IN_RANGE(__x, __lower, __upper) (__x >= __lower && __x < __upper)

/// Gets the value at the specified point. If the point is out of bounds,
/// returns 0.
bool get_at(bool *world, int x, int y, int columns, int rows) {
  int at = y * rows + x;

  return IN_RANGE(at, 0, columns * rows) ? world[at] : 0;
}

/// Sets the value at the specified point. If the point is out of bounds, this
/// function does nothing.
void set_at(bool *world, bool value, int x, int y, int columns, int rows) {
  int at = y * rows + x;

  if (IN_RANGE(at, 0, columns * rows))
    world[at] = value;
}

/// Returns the number of alive neighbours (Chebyshev distance = 1) for the
/// specified point. Out-of-bound points are treated as dead.
int neighbours(bool *world, int x, int y, int columns, int rows) {
  int alive = 0;

  for (int dy = -1; dy <= 1; ++dy)
    for (int dx = -1; dx <= 1; ++dx)
      if (dx != 0 || dy != 0)
        alive += get_at(world, x + dx, y + dy, columns, rows) > 0;

  return alive;
}

/// Does a single life cycle from `seed`, updating `world`.
void tick(bool *seed, bool *world, int columns, int rows) {
  for (int y = 0; y < rows; ++y)
    for (int x = 0; x < columns; ++x) {
      int n = neighbours(seed, x, y, columns, rows);
      bool alive = get_at(seed, x, y, columns, rows) > 0;

      if (alive && (n == 2 || n == 3))
        set_at(world, 1, x, y, columns, rows);
      else if (alive == false && (n == 3))
        set_at(world, 1, x, y, columns, rows);
      else
        set_at(world, 0, x, y, columns, rows);
    }
}
// }}}

// Rendering code {{{

bool swap = false;

bool buf1[ROWS * COLS];
bool buf0[ROWS * COLS] = {
    // Initial state
    0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, //
    0, 0, 1, 1, 1, 0, //
    0, 1, 1, 1, 0, 0, //
    0, 0, 0, 0, 0, 0, //
    0, 0, 0, 0, 0, 0, //
};

void loop() {
  // Alternates between two buffers to save memory.
  bool *seed = swap ? buf1 : buf0;
  bool *world = swap ? buf0 : buf1;

  for (int y = 0; y < ROWS; ++y)
    for (int x = 0; x < COLS; ++x)
      if (get_at(world, x, y, COLS, ROWS))
        set_pixel(x, y, 0, 255, 0);
      else
        set_pixel(x, y, 0, 0, 0);

  tick(seed, world, COLS, ROWS);

  swap ^= true;

  pixels.show();

  delay(MS_PER_TICK);
}

void set_pixel(int x, int y, int r, int g, int b) {
  // Odd rows are counted backwartds.
  if (y % 2 == 1)
    x = (COLS - 1) - x;

  pixels.setPixelColor(COLS * y + x, pixels.Color(r, g, b));
}
// }}}
