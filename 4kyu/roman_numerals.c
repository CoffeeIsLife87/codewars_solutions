#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Found at https://www.codewars.com/kata/51b66044bce5799a7f000003
*/

#ifdef BIGARRAY

const char* roman_static[] = {"M" , "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int  number_static[] = {1000, 900, 500,  400, 100,  90 ,  50,  40 ,  10,   9 ,   5,    4,  1 };

// This implementation works mostly if the array is really big and covers a lot of edge cases. 
int from_roman_big_array(char* roman) {
  printf("%s", roman);
  int return_num = 0;
  int char_len = sizeof(roman);
  int str_pos = 0;
  for (int r_ndx = 0; r_ndx < (sizeof(roman_static) / sizeof(roman_static[0])); r_ndx++) {
    int rn_len = strlen(roman_static[r_ndx]);

    while ( strncmp(&roman[str_pos], roman_static[r_ndx], (size_t)rn_len) == 0 && 
           ((str_pos + rn_len) < char_len))
    {
      return_num += number_static[r_ndx];
      
      if ((str_pos + rn_len) < char_len) {str_pos += rn_len;}
      else {break;}
    }
  }
  return return_num;
}

void to_roman_big_array(int number, char* destination) {
  char tmp_arr[64] = {'\0'};
  int str_pos = 0;
  for (int r_ndx = 0; r_ndx < (sizeof(roman_static) / sizeof(roman_static[0])); r_ndx++) {
    while (number >= number_static[r_ndx]) {
      int rn_len = strlen(roman_static[r_ndx]);
      strncpy(&tmp_arr[str_pos], roman_static[r_ndx], rn_len);
      str_pos += rn_len;
      number -= number_static[r_ndx];
    }
  }
  strncpy(destination, tmp_arr, str_pos);
  return;
}

#endif

#define PREVSIZECHECK

#ifdef PREVSIZECHECK

const char roman_static[] = {'M' , 'D', 'C', 'L', 'X', 'V', 'I'};
const int number_static[] = {1000, 500, 100,  50,  10,  5 ,  1 };

/*
  I think to make this easier to think about, we're gonna convert everything to normal numbers first
*/
int from_roman_prev_size_check(char* roman) {
  int return_num = 0;
  int roman_length = strlen(roman);
  int* converted_nums = malloc(sizeof(int) * roman_length);
  for (int r_ndx = 0; r_ndx < roman_length; r_ndx++) {
    for (int r_arr_ndx = 0; r_arr_ndx < (sizeof(roman_static) / sizeof(roman_static[0])); r_arr_ndx++) {
      if (roman[r_ndx] != roman_static[r_arr_ndx]) 
        continue;
      
      converted_nums[r_ndx] = number_static[r_arr_ndx];
      break;
    }
  }

  for (int r_ndx = 0; r_ndx < roman_length; r_ndx++) {
    if (r_ndx + 1 >= roman_length) {
      return_num += converted_nums[r_ndx];
      break;
    }

    if (converted_nums[r_ndx] < converted_nums[r_ndx + 1]){
      return_num += (converted_nums[r_ndx + 1] - converted_nums[r_ndx]);
      r_ndx += 1; // To avoid adding the same thing twice on accident
    } else {
      return_num += converted_nums[r_ndx];
    }
  }

  free(converted_nums);
  return return_num;
}

#endif

#include <stdbool.h>

// This works but it's really ugly and hard to read. Should probably revisit later
void to_roman(int number, char* destination) {
  bool try_sub = false;
  char return_array[100] = {'\0'};
  int roman_arr_len = (sizeof(roman_static) / sizeof(roman_static[0]));
  int roman_ndx = 0;
  int string_pos = 0;
  while (number > 0) {
    if (try_sub) {
      // Find the nearest power of 10 number (... , 1000, 100, 10, 1)
      int nearest_one = ((roman_ndx + 1 % 2 == 0) ? 1 : 2);

      if (((roman_ndx + nearest_one) < roman_arr_len) && 
         (number >= (number_static[roman_ndx] - number_static[roman_ndx + nearest_one])))
      {
        number -= (number_static[roman_ndx] - number_static[roman_ndx + nearest_one]);
        return_array[string_pos] = roman_static[roman_ndx + nearest_one];
        return_array[string_pos + 1] = roman_static[roman_ndx];
        string_pos += 2;
      } else {
        roman_ndx += 1;
        try_sub = false;
        if (roman_ndx >= roman_arr_len) {
          break;
        }
      }
    } else {
      if (number >= number_static[roman_ndx]) {
        return_array[string_pos] = roman_static[roman_ndx];
        number -= number_static[roman_ndx];
        string_pos += 1;
      } else { try_sub = true; }
    }
  }
  // There should be allocation of `destination` here normally
  memcpy(destination, return_array, (sizeof(char) * (string_pos)));
}

// Broken for reasons I don't understand yet
/*
void to_roman(int number, char* destination) {
  char return_array[100] = {'\0'};
  int roman_arr_len = (sizeof(roman_static) / sizeof(roman_static[0]));
  int roman_ndx = 0;
  int string_pos = 0;
  while (number > 0) {
    if (number >= number_static[roman_ndx]) {
      return_array[string_pos] = roman_static[roman_ndx];
      number -= number_static[roman_ndx];
      string_pos += 1;
      continue;
    } else {
      // Find the nearest power of 10 number (... , 1000, 100, 10, 1)
      int nearest_one = ((roman_ndx + 1 % 2 == 0) ? 1 : 2);

      if (((roman_ndx + nearest_one) < roman_arr_len)) {

        int subtracted_num = (number_static[roman_ndx] - number_static[roman_ndx + nearest_one]);
        if (number >= subtracted_num) {
          number -= subtracted_num;
          return_array[string_pos] = roman_static[roman_ndx + nearest_one];
          return_array[string_pos + 1] = roman_static[roman_ndx];
          string_pos += 2;
          continue;
        }
      }
    }

    roman_ndx += 1;
    if (roman_ndx >= roman_arr_len) {
      break;
    }
  }
  // There should be allocation of `destination` here normally
  memcpy(destination, return_array, (sizeof(char) * (string_pos)));
}
*/

int main(void) {
  //cr_assert_eq(from_roman("XXI"), 21);
  //cr_assert_eq(from_roman("I"), 1);
  //cr_assert_eq(from_roman("XXX"), 30);

  char* destination = malloc(sizeof(char));
  to_roman(4, destination);

  printf("%s\n", destination);

  to_roman(21, destination);

  printf("%s\n", destination);

  int num = from_roman_prev_size_check("IX");
  printf("%d\n", num);
  return 0;
}