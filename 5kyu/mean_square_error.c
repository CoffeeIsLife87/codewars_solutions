#include <stddef.h>

/*
  Found at https://www.codewars.com/kata/51edd51599a189fe7f000015

  Find the difference between a[i] and b[i]. Sqaure the absolute (converted to Positive) difference. Add it to a number
  Devide that number by the amount of elements to get the average of the whole array
*/

int square(int i) {
  if (i < 0) {
    i = i * -1;
  }
  return i * i;
}

double mean_square_error(size_t n, const int a[n], const int b[n]) {
  int final_num = 0;
  for (size_t ndx = 0; ndx < n; ndx++) {
    final_num += square(a[ndx] > b[ndx] ? (a[ndx] - b[ndx]) : (b[ndx] - a[ndx]));
  }
  return (double)final_num / (double)n;
}

int main(void) {
    const int a[4] = {10, 20, 10, 2};
    const int b[4] = {10, 25, 5, -2};
    double expected = 9.0;
    double yes = mean_square_error(4, a, b);
    return 0;
}