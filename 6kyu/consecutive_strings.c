#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
  Find the longest string possible based off of 2 adjacent strings in an array

  Found at https://www.codewars.com/kata/56a5d994ac971f1ac500003e
*/

char *longestConsec(const char *const strings[/*arr_len*/], int arr_len, int k) {
  if (arr_len < 1 || k < 1)
    return calloc(1, 1);

  int longest_len = 0;
  int starting_pos = 0;
  for (int ndx = 0; ndx < arr_len; ndx++) {
    if ((ndx + k) > arr_len)
      break;

    int current_num = 0;
    for (int count = 0; count < k; count++)
      current_num += strlen(strings[ndx + count]);
      
    if (current_num > longest_len) {
      longest_len = current_num;
      starting_pos = ndx;
    }
  }
  char *ret_string = calloc((size_t)(longest_len + 1), sizeof(char));
  int filled_len = 0;
  for (int count = 0; count < k; count++) {
    int add_str_pos = starting_pos + count;
    int add_str_len = strlen(strings[add_str_pos]);
    strncpy(&ret_string[filled_len], strings[add_str_pos], add_str_len);
    filled_len += add_str_len;
  }
  ret_string[longest_len] = '\0';

  return ret_string;
}

#define sample_test(input, len, k, expected) {                              \
  char *test_string = longestConsec(input, len, k);                         \
  if (strcmp(test_string, expected) != 0) {                                 \
    printf("Incorrect output. Got %s, Expected %s", test_string, expected); \
  }                                                                         \
  free(test_string);                                                        \
}

int main(void)
{
  sample_test(((const char *const[]){"zone", "abigail", "theta", "form", "libe", "zas", "theta", "abigail"}),
              8, 2, "abigailtheta");

  sample_test(((const char *const[]){"ejjjjmmtthh", "zxxuueeg", "aanlljrrrxx", "dqqqaaabbb", "oocccffuucccjjjkkkjyyyeehh"}),
              5, 1, "oocccffuucccjjjkkkjyyyeehh");

  sample_test(((const char *const[]){"itvayloxrp", "wkppqsztdkmvcuwvereiupccauycnjutlv", "vweqilsfytihvrzlaodfixoyxvyuyvgpck"}),
              3, 2, "wkppqsztdkmvcuwvereiupccauycnjutlvvweqilsfytihvrzlaodfixoyxvyuyvgpck");

  return 0;
}