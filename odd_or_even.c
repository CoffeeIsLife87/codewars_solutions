#include <stddef.h>

/*
  Check whether the sum of all the elements in an array is even or odd

  Found at https://www.codewars.com/kata/5949481f86420f59480000e7
*/

/*
  We check this by creating an int, running through the list and adding
  all the elements of the array to it, and then using `% 2 == 0`
  We can also check if `sz == 0` because if that's the case then the array is `[0]`
  In alternate methods, we could maybe save a little bit of time by checking `sz` first
*/
const char *odd_or_even(const int *v, size_t sz) {
  int final_num = 0;
  for (size_t ndx = 0; ndx < sz; ndx++) {
    final_num += v[ndx];
  }

  if ((sz == 0) || (final_num % 2 == 0)) {
    return "even";
  }
  return "odd";
}

int main(void) {

}