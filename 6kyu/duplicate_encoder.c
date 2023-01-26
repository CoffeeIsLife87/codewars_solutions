/*
  Switch every character to a '(' if it's original or a ')' if it appears more than once in the string

  Found at https://www.codewars.com/kata/54b42f9314d9229fd6000d9c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// I borrowed a good amount of code from one of my previous problems that I did a while back
// That can be found at https://github.com/CoffeeIsLife87/codewars_solutions/blob/master/6kyu/counting_duplicates.c

char* DuplicateEncoder (const char *string)
{
  const int length = strlen(string);
  bool used[255] = {false};
  bool duped[255] = {false};
  int dupes = 0;
  char current_char;

  for (int a_ndx = 0; a_ndx <= length; a_ndx++) {
    current_char = tolower(string[a_ndx]);

    if (used[(int)current_char])
      continue;
    
    used[(int)current_char] = true;

    for (int b_ndx = a_ndx + 1; b_ndx <= length; b_ndx++) {
      if (tolower(string[b_ndx]) == current_char) {
        duped[(int)current_char] = true;
        break;
      }
    }
  }

  char* ret_string = calloc(length + 1, sizeof(char));
  for (int ndx = 0; ndx < length; ndx++) {
    if (duped[(int)tolower(string[ndx])]) {
      ret_string[ndx] = ')';
    } else {
      ret_string[ndx] = '(';
    }
  }
  ret_string[length] = '\0';

  return ret_string;
}

int main(void) {
  char* converted = DuplicateEncoder("Prespecialized");
  if (strcmp(converted, ")()())()(()()(") == 0) {
    return 0;
  }
  return 1;
}