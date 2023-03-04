#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Found at https://www.codewars.com/kata/51ba717bb08c1cd60f00002f

typedef enum {
  APPEND_MULTI,
  APPEND_SINGLE,
  APPEND_DOUBLE,
  APPEND_END,
} append_type;

void append_string(char* ret_buffer, int* str_length, append_type type, signed int lower, signed int upper) {
  char smaller_buf[20];
  switch (type) {
    case APPEND_MULTI:  { sprintf(smaller_buf, "%d-%d,", lower, upper); } break;
    case APPEND_SINGLE: { sprintf(smaller_buf, "%d,"   , lower       ); } break;
    case APPEND_DOUBLE: { sprintf(smaller_buf, "%d,%d,", upper, lower); } break;
    case APPEND_END: break;
  }
  strncpy(&ret_buffer[*str_length], smaller_buf, strlen(smaller_buf));
  *str_length += strlen(smaller_buf);
}

char* range_extraction(const int *args, size_t n)
{
  if (n < 1) {
    return NULL;
  }

  int previous_num = args[0];
  for (size_t i = 1; i < n; i++) {
    if (args[i] < previous_num) {
      return NULL;
    }
    previous_num = args[i];
  }

  char ret_buffer[100] = {'\0'};
  int string_length = 0;

  size_t last_pos = 0;
  
  for (size_t ndx = 0; ndx <= (n - 1); ndx++) {
    // The second condition makes sure we run the string appending on the last iteration as well
    if (((args[ndx] + 1) == args[ndx + 1]) && (ndx < (n - 1)))
      continue;

    // condition 1 makes sure we don't read out of bounds
    if ((ndx > 0) && (args[ndx - 1] == args[ndx])) {
      last_pos = ndx + 1;
      continue;
    }

    size_t found_count = (ndx - last_pos) + 1;
    if (found_count > 2) { // Use "<num 1> - <num 2>" formatting
      append_string((char*)ret_buffer, &string_length, APPEND_MULTI, args[last_pos], args[ndx]);
    } else { // Use "<num 1>,<num 2>," formatting
      //int upper_num = (found_count == 2 ? args[ndx - 1] : 0);
      append_type type = (found_count == 2 ? APPEND_DOUBLE : APPEND_SINGLE);
      append_string((char*)ret_buffer, &string_length, type, args[ndx], args[ndx - 1]);
    }
    last_pos = ndx + 1;
  }
  ret_buffer[string_length - 1] = '\0'; // Cap off working buffer
  char* ret_string = malloc(sizeof(char) * string_length); // create return string
  memcpy(ret_string, ret_buffer, sizeof(char) * string_length); // copy from working buffer to return string
  return ret_string;
}

/*
  Previous attempts that didn't work.
  They're both probably overcomplicated

  "#if 0" to avoid compiling unused functions
*/
#if 0
char* range_extraction_almost_working(const int *sure, size_t n)
{
  int args[100] = {0};
  memcpy(args, sure, sizeof(int) * n);
  char ret_buffer[100] = {'\0'};
  int string_length = 0;
  signed int starting_num = args[0];
  int found_count = 0;
  for (size_t ndx = 0; ndx < (n - 1); ndx++) {
    if ((args[ndx]) == args[ndx + 1]) { // next number less than or same as current number
      memcpy(&args[ndx + 1], &args[ndx + 2], n - (ndx));
      n -= 1;
    }

    if ((args[ndx] + 1) == args[ndx + 1]) { // next number 1 greater than current number?
      found_count += 1;
    } else if (found_count >= 2) { // if we found more than 2
      append_string((char*)ret_buffer, &string_length, false, starting_num, args[ndx]);
      starting_num = args[ndx + 1];
      found_count = 0;
    } else { // if we only found 1
      if ( (found_count == 1) && (args[ndx] != args[ndx - 1]) ) {
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

char* range_extraction_add_all(const int *args, size_t n)
{
  char ret_buffer[100] = {'\0'};
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
      if ( (found_count == 1) && (args[ndx] != args[ndx - 1]) ) {
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
#endif

int main(void) {
  //range_extraction((const []){-10, -9, -8, -6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20}, 23);
  //range_extraction((const []){ -6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20 }, 20);
  //range_extraction((const []){-5,-4,-2,-1,1,2,4,5}, 8);
  //range_extraction((const []){1,2,4,5,5,7}, 6);
  //range_extraction((const []){}, 0);

  return 0;
}