#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void append_string(char* ret_buffer, int* str_length, bool single_num, signed int lower, signed int upper) {
  char smaller_buf[20];
  if (single_num) {
    sprintf(smaller_buf, "%d,", lower);
  } else {
    sprintf(smaller_buf, "%d-%d,", lower, upper);
  }
  strncpy(&ret_buffer[*str_length], smaller_buf, strlen(smaller_buf));
  *str_length += strlen(smaller_buf);
}

char* range_extraction(const int *args, size_t n)
{
  char ret_buffer[100];
  int string_length = 0;
  signed int starting_num = args[0];
  int found_count = 0;
  for (size_t ndx = 0; ndx < (n - 1); ndx++) {
    if ((args[ndx] + 1) == args[ndx + 1]) {
      found_count += 1;
    } else if (args[ndx] == args[ndx + 1]) {
      continue;
    } else if (found_count >= 2) {
      append_string((char*)ret_buffer, &string_length, false, starting_num, args[ndx]);
      starting_num = args[ndx + 1];
      found_count = 0;
    } else {
      if (found_count == 1) {
        append_string((char*)ret_buffer, &string_length, true, args[ndx - 1], 0);
      }
      found_count = 0;
      append_string((char*)ret_buffer, &string_length, true, args[ndx], 0);
      starting_num = args[ndx + 1];
    }
  }
  if (found_count >= 2) {
    append_string((char*)ret_buffer, &string_length, false, starting_num, args[n - 1]);
  }
  if (found_count < 2) {
    if (n > 1) {
      append_string((char*)ret_buffer, &string_length, true, args[n - 2], 0);
    }
    append_string((char*)ret_buffer, &string_length, true, args[n - 1], 0);
  }
  ret_buffer[string_length - 1] = '\0';
  //char* ret_string = calloc(sizeof(char), strlen(ret_buffer));
  char* ret_string = malloc(sizeof(char) * string_length);
  //strncpy(ret_string, ret_buffer, strlen(ret_buffer));
  memcpy(ret_string, ret_buffer, sizeof(char) * string_length);
  return ret_string;
}

int main(void) {
  //range_extraction((const []){-10, -9, -8, -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20}, 23);
  range_extraction((const []){ -6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20 }, 20);
  return 0;
}