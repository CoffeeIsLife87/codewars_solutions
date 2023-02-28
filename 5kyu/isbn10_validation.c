/*
  Check if an ISBN number is valid

  found at https://www.codewars.com/kata/51fc12de24a9d8cb0e000001/
*/

#include <stdbool.h>

bool is_valid_ISBN_10 (const char *ISBN)
{
  int len = strlen(ISBN);
  int final_num = 0;
  if (len != 10) {
    return false;
  }
  for (int pos = 0; pos < len; pos++) {
    int num = (int)(ISBN[pos]) - (int)'0';
    if ((num > 9) && (pos != 9)) { return false; }
    if (ISBN[pos] == 'X') { num = 10; }

    final_num += num * (pos + 1);
  }
  if ((final_num % 11) == 0) {
    return true;
  }
  return false;
}