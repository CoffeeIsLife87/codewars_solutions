#include <stdio.h>

/*
  Convert RGB to Hex

  Valid numbers are 0 - 255
  Nothing below 0 and nothing above 255

  Found at https://www.codewars.com/kata/513e08acc600c94f01000001
*/

/*
  c = check

  if it's below 0, return 0
  if it's above 255, return 255
  if it's in range, return i
*/
#define c(i) (i < 0 ? 0 : ((i > 255) ? 255 : i))

// The way this is written now assumes that `output` has already been allocated
void rgb(int r, int g, int b, char *output)
{
  snprintf(output, 7, "%02X%02X%02X", c(r), c(g), c(b));
}

int main(void) {
  char output[7];
  rgb(-10, 257, 127, (char*)output);
  return 0;
}