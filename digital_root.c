#include <stdio.h>
#include <stdlib.h>

// Found at https://www.codewars.com/kata/541c8630095125aba6000c00

int get_digits(int number) {
  int retval = 0, tmp_num = number;
  while (tmp_num != 0) {
    tmp_num /= 10;
    retval += 1;
  }
  return retval;
}

int loop(int num, int digits) {
  char buf[1], *arr_str = malloc(sizeof(char) * digits);
  int new_num = 0, *int_arr = malloc(sizeof(int) * digits);
  sprintf(arr_str, "%d", num);
  for (int ndx = 0; ndx < digits; ndx++) {
    buf[0] = arr_str[ndx];
    new_num += atoi(buf);
  }
  free(arr_str);
  free(int_arr);
  return new_num;
}

int digital_root(const int n) {
  int count = get_digits(n);
  int num = n;
  while (count > 1) {
    num = loop(num, count);
    count = get_digits(num);
  }
  return num;
}

#define test(fn_name, input, expected) {   \
  int result = fn_name(input);            \
  if (result != expected) {               \
    printf("Expected %d, instead got %d", \
    expected,                             \
    result);                              \
  }                                       \
}

int main(void) {
  test(digital_root, 16, 7);
  test(digital_root, 195, 6);
  test(digital_root, 992, 2);
  test(digital_root, 167346, 9);
  test(digital_root, 0, 0);
  return 0;
}