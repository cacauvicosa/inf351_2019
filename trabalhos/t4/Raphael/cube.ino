void setup() {
  for (int i = 2; i <= 13; ++i)
    pinMode(i, OUTPUT);
}

void loop() {
  // Set each LED individually.
  for (int y = 0; y < 3; ++y)
    for (int x = 0; x < 3; ++x)
      for (int z = 0; z < 3; ++z) {
        matrix(x, y, z);
        delay(1000);
      }

  unset_cols();

  // Set each row.
  for (int y = 0; y < 3; ++y) {
    set_whole_row(y);
    delay(1000);
  }

  // Set each col.
  for (int x = 0; x < 3; ++x)
    for (int z = 0; z < 3; ++z) {
      set_whole_col(x, z);
      delay(1000);
    }
}

void matrix(int x, int y, int z) {
  unset_cols();
  unset_rows();

  set_row(y);
  set_col(x, z);
}

void set_whole_row(int y) {
  unset_rows();
  set_row(y);

  for (int x = 0; x < 3; ++x)
    for (int z = 0; z < 3; ++z)
      set_col(x, z);
}

void set_whole_col(int x, int z) {
  unset_cols();
  set_col(x, z);

  for (int y = 0; y < 3; ++y)
    set_row(y);
}

void set_row(int y) { digitalWrite(y + 11, LOW); }
void set_col(int x, int z) { digitalWrite(z * 3 + x + 2, HIGH); }

void unset_rows() {
  for (int i = 11; i <= 13; ++i)
    digitalWrite(i, HIGH);
}

void unset_cols() {
  for (int i = 2; i <= 10; ++i)
    digitalWrite(i, LOW);
}
