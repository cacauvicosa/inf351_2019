/// Author: Raphael Nepomuceno <raphael.nepomuceno@protonmail.com>

// Tetris {{{

#define TETRIS_COLS (12)
#define TETRIS_ROWS (12)

#define MAX_AREA (2 * 3)

typedef unsigned char byte;

typedef struct {
  byte r;
  byte g;
  byte b;
} color_t;

typedef struct {
  bool points[MAX_AREA];

  byte cols;
  byte rows;
} block_shape_t;

typedef struct {
  block_shape_t shape;

  byte x;
  byte y;

  color_t color;
} block_t;

typedef struct {
  bool set;
  color_t color;
} tile_t;

typedef struct {
  tile_t tiles[TETRIS_COLS * TETRIS_ROWS];

  byte cols;
  byte rows;
} world_t;

/// Resets the state for the specified world.
void new_world(world_t *world) {
  for (byte i = 0; i < world->rows * world->cols; ++i)
    world->tiles[i].set = false;
}

/// Resets the state for the specified block.
void new_block(block_t *block, byte type) {
  block->x = 0;
  block->y = 0;

  switch (type) {
  case 0:
    block->color = (color_t){0x00, 0xFF, 0xFF};
    block->shape = (block_shape_t){
        .points = {1, 1, 1, 1},
        .cols = 4,
        .rows = 1,
    };
    break;

  case 1:
    block->color = (color_t){0x00, 0x00, 0xFF};
    block->shape = (block_shape_t){
        .points = {1, 0, 0, 1, 1, 1},
        .cols = 3,
        .rows = 2,
    };
    break;

  case 2:
    block->color = (color_t){0xFF, 0x80, 0x00};
    block->shape = (block_shape_t){
        .points = {0, 0, 1, 1, 1, 1},
        .cols = 3,
        .rows = 2,
    };
    break;

  case 3:
    block->color = (color_t){0xFF, 0xFF, 0x00};
    block->shape = (block_shape_t){
        .points = {1, 1, 1, 1},
        .cols = 2,
        .rows = 2,
    };
    break;

  case 4:
    block->color = (color_t){0x00, 0xFF, 0x00};
    block->shape = (block_shape_t){
        .points = {0, 1, 1, 1, 1, 0},
        .cols = 3,
        .rows = 2,
    };
    break;

  case 5:
    block->color = (color_t){0xFF, 0x00, 0xFF};
    block->shape = (block_shape_t){
        .points = {0, 1, 0, 1, 1, 1},
        .cols = 3,
        .rows = 2,
    };
    break;

  case 6:
    block->color = (color_t){0xFF, 0x00, 0x00};
    block->shape = (block_shape_t){
        .points = {1, 1, 0, 0, 1, 1},
        .cols = 3,
        .rows = 2,
    };
    break;
  }
}

/// Rotates a block 90 degrees counter-clockwise.
void rotate(block_shape_t *shape) {
  bool buf[MAX_AREA];

  byte rows = shape->rows;
  byte cols = shape->cols;

  for (byte y = 0; y < rows; ++y)
    for (byte x = 0; x < cols; ++x)
      // Mirror and transpose.
      buf[x * rows + y] =
          shape->points[y * cols + (cols - 1 - x)]; // (x, y) <- (y, w - 1 - x)

  for (byte i = 0; i < MAX_AREA; ++i)
    shape->points[i] = buf[i];

  shape->rows = cols;
  shape->cols = rows;
}

/// Checks if a block touches any other set tile directly below it.
bool touches(const block_t *block, const world_t *world) {
  // TODO: change to detect if current move is invalid, and, if so, backtrack.
  for (byte y = 0; y < block->shape.rows; ++y) {
    byte row = y + block->y;

    // Block touches the floor.
    if (row == world->rows - 1)
      return true;

    // Array offset to the first tile below the block.
    byte below = (row + 1) * world->cols + block->x;

    // Array offset to the block row.
    byte offset = y * block->shape.cols;

    for (byte x = 0; x < block->shape.cols; ++x)
      if (block->shape.points[offset + x] && world->tiles[below + x].set)
        return true;
  }

  return false;
}

/// Transforms a block into a world tile.
void paste(const block_t *block, world_t *world) {
  for (byte y = 0; y < block->shape.rows; ++y) {
    for (byte x = 0; x < block->shape.cols; ++x) {
      byte wy = block->y + y;
      byte wx = block->x + x;

      byte pos = wy * world->cols + wx;

      if (block->shape.points[y * block->shape.cols + x]) {
        world->tiles[pos].set = true;
        world->tiles[pos].color = block->color;
      }
    }
  }
}

/// Checks if all tiles in the specified row are set.
bool is_dirty_row(world_t *world, byte row) {
  bool dirty = true;
  byte pos = row * world->cols;

  for (byte x = 0; x < world->cols; ++x)
    dirty &= world->tiles[pos + x].set;

  return dirty;
}

/// Shifts all rows, until floor_, down by 1. Row 0 is unset.
void shift_down(world_t *world, byte floor_) {
  for (char y = floor_ - 1; y >= 0; --y) {
    byte row = y * world->cols;
    byte below = (y + 1) * world->cols;

    for (byte x = 0; x < world->cols; ++x)
      world->tiles[below + x] = world->tiles[row + x];
  }

  // Unset all tiles in row 0.
  for (byte x = 0; x < world->cols; ++x)
    world->tiles[x].set = false;
}

/// Cleans up fully set rows.
void cleanup(world_t *world) {
  for (byte y = 0; y < world->rows;)
    if (is_dirty_row(world, y))
      shift_down(world, y);
    else
      ++y;
}
// }}}

#include <Adafruit_NeoPixel.h>

#define LED_PIN (8)

#define ROWS (6)
#define COLS (6)

#define MS_PER_TICK (300)

Adafruit_NeoPixel pixels =
    Adafruit_NeoPixel(ROWS * COLS, LED_PIN, NEO_GRB + NEO_KHZ800);

// LED helper {{{

/// Lights up a pixel.
void set_pixel(int x, int y, int r, int g, int b) {
  // Odd rows are counted backwartds.
  if (y % 2 == 1)
    x = (COLS - 1) - x;

  pixels.setPixelColor(COLS * y + x, pixels.Color(r, g, b));
}
// }}}

void setup() {
  pixels.begin();
  randomSeed(analogRead(0));

  block_t block;
  world_t world = {.cols = 12, .rows = 12};

  new_block(&block, random(0, 7));
  new_world(&world);

  byte input;

  while (true) {
    // Simulate random input.
    input = random(65, 71);

    if (move(&block, input) == false)
      // Move down.
      move(&block, 66);

    if (touches(&block, &world)) {
      paste(&block, &world);
      new_block(&block, random(0, 7));
    }

    // Draw
    draw_world(&world);
    draw_block(&block);

    pixels.show();
    delay(MS_PER_TICK);
  }
}

bool move(block_t *block, byte input) {
  switch (input) {
  case 65:
    rotate(&block->shape);
    return true;

  case 66:
    block->y += 1;
    return true;

  case 68:
    if (block->x > 0)
      block->x -= 1;
    return true;

  case 67:
    if (block->x + block->shape.cols < 12)
      block->x += 1;
    return true;

  default:
    return false;
  }
}

/// Draws the game state.
void draw_world(world_t *world) {
  tile_t tile;

  for (byte y = 0; y < world->rows; ++y)
    for (byte x = 0; x < world->cols; ++x) {
      tile = world->tiles[y * world->cols + x];

      if (tile.set)
        set_pixel(x, y, tile.color.r, tile.color.g, tile.color.b);
      else
        set_pixel(x, y, 0, 0, 0);
    }
}

void draw_block(block_t *block) {
  for (byte y = 0; y < block->shape.rows; ++y)
    for (byte x = 0; x < block->shape.cols; ++x)
      if (block->shape.points[y * block->shape.cols + x])
        set_pixel(block->x + x, block->y + y, block->color.r, block->color.g,
                  block->color.b);
      else
        set_pixel(block->x + x, block->y + y, 0, 0, 0);
}
