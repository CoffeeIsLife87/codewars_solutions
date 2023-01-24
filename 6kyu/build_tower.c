/*
  Build a Tower in an array using '*'

  Example:

  [[_ _ * _ _],
   [_ * * * _],
   [* * * * *]]

  Found at https://www.codewars.com/kata/576757b1df89ecf5bd00073b
*/

void build_tower(unsigned n, char tower[n][2 * n - 1])
{
  const int width = ((2 * n) - 1);
  int starting_x, x_count;
  for (int y = 0; y < n; y++) {
    x_count = (2 * y);
    starting_x = ((width - x_count) / 2);
    for (int x = 0; x < width; x++) {
      if ((x >= starting_x) && (x <= starting_x + x_count)) {
        tower[y][x] = '*';
      } else {
        tower[y][x] = ' ';
      }
    }
  }
}

int main(void) {
  char tower[4][7];
  build_tower(4, tower);
  return 0;
}