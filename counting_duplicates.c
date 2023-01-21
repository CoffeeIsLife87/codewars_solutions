#include <ctype.h> // Needed for `tolower()`
#include <stdbool.h> // Needed for `bool`
#include <stdlib.h> // Needed for `realloc()`
#include <string.h> // Needed for `strlen()`
#include <stdio.h>

/* Count the number of Duplicates
  Write a function that will return the count of distinct case-insensitive 
  alphabetic characters and numeric digits that occur more than once in the input string. 
  The input string can be assumed to contain only alphabets 
  (both uppercase and lowercase) and numeric digits.

  Examples:
  1. "abcde" -> 0 # no characters repeats more than once
  2. "aabbcde" -> 2 # 'a' and 'b'
  3. "aabBcde" -> 2 # 'a' occurs twice and 'b' twice (`b` and `B`)
  4. "indivisibility" -> 1 # 'i' occurs six times
  5. "Indivisibilities" -> 2 # 'i' occurs seven times and 's' occurs twice
  6. "aA11" -> 2 # 'a' and '1'
  7. "ABBA" -> 2 # 'A' and 'B' each occur twice

  (Found at https://www.codewars.com/kata/54bf1c2cd5b56cc47f0007a1 )
*/

/*
  Goes through a loop of duplicates that's created as they're found
  If the character is already on the list of counted letters then it just skips it

  Thinking for this block:
  *   We could have a list of all the characters we've found and check against that
  *     Does that scale with a larger variety of characters? Or just more in general?
*/
size_t duplicate_count(const char *text) {
  int length = strlen(text);
  char* duped_chars = malloc(sizeof(char));
  int dupes = 0;
  
  for (int a_ndx = 0; a_ndx <= length; a_ndx++) {
    bool found = false;
    char current_char = tolower(text[a_ndx]);

    for (int d_ndx = 0; d_ndx < dupes; d_ndx++) {
      if (current_char == duped_chars[d_ndx]) {
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }

    for (int b_ndx = a_ndx + 1; b_ndx <= length; b_ndx++) {
      if (current_char == tolower(text[b_ndx])) {
        dupes += 1;
        duped_chars = realloc(duped_chars, sizeof(char) * dupes);
        duped_chars[dupes - 1] = current_char;
        break;
      }
    }
  }
  free(duped_chars);

  return dupes;
}

/*
  Same as `duplicate_count()` but takes time at the 
  beginning to convert all the characters to lower 
  so we don't do it at comparison time

  Thinking for this block:
  *   We could also convert everything to lower imediately instead of doing it repeatedly for comparison
  *     Does recreating the whole string waste more time than just converting as needed?
*/
size_t converted_duplicate_count(const char *text) {
  int length = strlen(text);
  char* duped_chars = malloc(sizeof(char));
  int dupes = 0;
  
  char* converted_string = malloc(sizeof(char) * length);
  for (int c_ndx = 0; c_ndx <= length; c_ndx++) {
    converted_string[c_ndx] = tolower(text[c_ndx]);
  }
  
  for (int a_ndx = 0; a_ndx <= length; a_ndx++) {
    bool found = false;
    char current_char = converted_string[a_ndx];

    for (int d_ndx = 0; d_ndx < dupes; d_ndx++) {
      if (current_char == duped_chars[d_ndx]) {
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }

    for (int b_ndx = a_ndx + 1; b_ndx <= length; b_ndx++) {
      if (current_char == converted_string[b_ndx]) {
        dupes += 1;
        duped_chars = realloc(duped_chars, sizeof(char) * dupes);
        duped_chars[dupes - 1] = current_char;
        break;
      }
    }
  }
  free(duped_chars);

  return dupes;
}

/*
  Pulls out characters as it finds them instead
  of creating a list to check against

  Timed out on codewars test (Took to long)

  Thinking for this block:
  *   We could actually start pulling out characters if we wanted to potentially speed everything up
  *     Would we spend more time pulling than doing actual comparing tho?
*/
size_t pull_dupes_duplicate_count(const char *text) {
  int length = strlen(text);
  int dupes = 0;
  char* custom_text = malloc(sizeof(char) * length + 1);
  strcpy(custom_text, text);
  
  for (int a_ndx = 0; a_ndx <= length; a_ndx++) {
    bool pull_char = false;
    char current_char = tolower(custom_text[a_ndx]);

    for (int b_ndx = a_ndx + 1; b_ndx <= length; b_ndx++) {
      if (current_char == tolower(custom_text[b_ndx])) {
        if (!pull_char) {
          pull_char = true;
          dupes += 1; 
        }
      }
    }

    if (!pull_char)
      continue;

    for (int rev_pos = length + 1; rev_pos >= 0; rev_pos--) {
      if (tolower(custom_text[rev_pos] == current_char)) {
        for (int shift_pos = rev_pos; shift_pos < length; shift_pos++) {
          custom_text[shift_pos] = custom_text[shift_pos + 1];
        }
        length -= 1;
      }
    }
    a_ndx -= 1;

  }

  return dupes;
}

/*
  Creates a janky hashmap based on the int value of the character
  Sets `used[ndx] = true;` after using the letter once. Not after finding a match

  Thinking for this block:
  *   It's faster to jump straight to an index rather than checking every value over and over again
  *     I can sacrifice 255 bits of memory to check if I have this character quickly
*/
size_t scuffed_hashmap_duplicate_count(const char *text) {
  const int length = strlen(text);
  bool used[255] = {false};
  int dupes = 0;
  char current_char;

  for (int a_ndx = 0; a_ndx <= length; a_ndx++) {
    current_char = tolower(text[a_ndx]);

    if (used[(int)current_char])
      continue;
    
    used[(int)current_char] = true;

    for (int b_ndx = a_ndx + 1; b_ndx <= length; b_ndx++) {
      if (tolower(text[b_ndx]) == current_char) {
        dupes += 1;
        break;
      }
    }
  }
  return dupes;
}

#define indie_test(fn_name, str, expt_rslt) ({        \
  if (!(fn_name(str) == expt_rslt)) {                 \
    printf("Test of string %s failed on function %s", \
           str,                                       \
           fn_name);                                  \
  }                                                   \
})

#define TEST(str, expt_rslt) {                                 \
  indie_test(duplicate_count, str, expt_rslt);                 \
  indie_test(converted_duplicate_count, str, expt_rslt);       \
  indie_test(pull_dupes_duplicate_count, str, expt_rslt);      \
  indie_test(scuffed_hashmap_duplicate_count, str, expt_rslt); \
}

int main(void) {
  TEST("abcde", 0);
  TEST("abcdea", 1);
  TEST("indivisibility", 1);
  return 0;
}