#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/*
  Write a morse code reader

  Found at https://www.codewars.com/kata/54b724efac3d5402db00065e
*/

const char *morse[55] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "...---..."};  
const char *ascii[55] = {"A",  "B",    "C",    "D",   "E", "F",    "G",   "H",    "I",  "J",    "K",   "L",    "M",  "N",  "O",   "P",    "Q",    "R",   "S",   "T", "U",   "V",    "W",   "X",    "Y",    "Z",    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ".",      ",",      "?",      "'",      "!",      "/",     "(",     ")",      "&",     ":",      ";",      "=",     "+",     "-",      "_",      "\"",     "$",       "@",      "SOS"};

#define input_string(str) {\
  int in_str_len = strlen(str); \
  ret_length += in_str_len; \
  if (!((ret_length <= 0) || (in_str_len <= 0))) { \
    ret_string = realloc(ret_string, sizeof(char) * ret_length); \
    strncat(&ret_string[ret_length - in_str_len], str, (size_t)in_str_len); \
  } else { \
    fprintf(stderr, "Something was the wrong size: ret_length = %d, in_str_len = %d\n", ret_length, in_str_len); \
  }\
}

/*
  The way this is written now deals with a bunch of edge cases really strangely
  For example, to signal the end of morse character we look for a space or string ending
  But that's done with an `||` opperator 

  We could just as easily start checking to see if it's one of the 2 characters 
  accepted as morse input and avoid some extra errors that way

  In decode_morse_dynamic, I was constantly using realloc which was causing issues on some of the tests. 
  I decided to just drop this in favor of a static array that would be automatically cleared 
  out as soon as the function goes out of scope
*/
char *decode_morse_dynamic(const char* morse_code) {
  int string_length = strlen(morse_code);
  if (string_length <= 0)
    return NULL;
  
  int ret_length = 0;
  char* ret_string = malloc(sizeof(char) * 1);
  
  int space_count = 0;

  for (int ndx = 0; ndx <= string_length; ndx++) {
    if (morse_code[ndx] == ' ')
      space_count += 1;
    else
      space_count = 0;
    
    if ((space_count == 3) && (ret_length > 0)) {
      input_string(" ");
      space_count = 0;
    }

    if (morse_code[ndx] != '-' && morse_code[ndx] != '.')
      continue;

    for (int m_ndx = 0; m_ndx < 55; m_ndx++) {
      int char_len = strlen(morse[m_ndx]);
      bool found = false;
      
      for (int s_ndx = 0; s_ndx <= char_len; s_ndx++) {
        if (string_length < (ndx + s_ndx - 1))
          break;

        if ((morse_code[ndx + s_ndx] != morse[m_ndx][s_ndx] && (s_ndx < char_len))) {
          break;
        } else if (((morse_code[ndx + s_ndx] == ' ') || (morse_code[ndx + s_ndx] == '\0')) && (s_ndx == char_len)) {
          input_string(ascii[m_ndx]);
          ndx += (s_ndx - 1);
          found = true;
        }
      }
      if (found)
        break;
    }
  }
  while (ret_string[ret_length - 1] == ' ') {
    if (ret_string[ret_length - 2] == ' ') {
      ret_string[ret_length - 1] = (char)NULL;
      ret_string = realloc(ret_string, sizeof(char) * ret_length--);
    } else {
      ret_string[ret_length - 1] = '\0';
    }
  }
  return ret_string;
}

char *decode_morse_static(const char* morse_code) {
  int string_length = strlen(morse_code);
  /* I'll leave these lines in here as an example. 
   * In the test, it never says that it has to be a malloc string. 
   * I was returning a non-malloc string that it tried to `free()` 
   * which was causing me to fail one of the tests.
   */
  //if (string_length <= 0)
  //  return NULL;
  
  int ret_length = 0;
  char working_ret_string[100] = {'\0'};
  int last_char_place = 0;  
  int space_count = 0;

  for (int ndx = 0; ndx <= string_length; ndx++) {
    if (morse_code[ndx] == ' ')
      space_count += 1;
    else
      space_count = 0;
  
    if ((space_count == 3) && (ret_length > 0)) {
      working_ret_string[ret_length] = ' ';
      ret_length++;
      space_count = 0;
    }

    /*
     * In the case of the codewars test, it guarenteed that it would be a 
     * valid input string. In real life, that's not guarenteed, so having these 
     * in would be a good guard against silly input. You could also throw an error
     * to the caller if you wanted to
     */
    //if (morse_code[ndx] != '-' && morse_code[ndx] != '.')
    //  continue;
  
    for (int m_ndx = 0; m_ndx < 55; m_ndx++) {
      int char_len = strlen(morse[m_ndx]);
      bool found = false;
      
      for (int s_ndx = 0; s_ndx <= char_len; s_ndx++) {
        if (string_length < (ndx + s_ndx - 1))
          break;

        if ((morse_code[ndx + s_ndx] != morse[m_ndx][s_ndx] && (s_ndx < char_len))) {
          break;
        } else if (((morse_code[ndx + s_ndx] == ' ') || (morse_code[ndx + s_ndx] == '\0')) && (s_ndx == char_len)) {
          int str_in_len = strlen(ascii[m_ndx]);
          strncpy(&working_ret_string[ret_length], ascii[m_ndx], str_in_len);
          ret_length += str_in_len;
          last_char_place = ret_length;
          ndx += (s_ndx - 1);
          found = true;
        }
      }
      if (found)
        break;
    }
  }
  ret_length = last_char_place;
  working_ret_string[ret_length] = '\0';
  
  char* ret_string = malloc(sizeof(char) * ret_length);
  printf("%d\n", ret_length);
  strncpy(ret_string, working_ret_string, ret_length);
  return ret_string;
}

int main(void) {
  char* string = decode_morse_static(".... . -.--   .--- ..- -.. .");
  return 0;
}