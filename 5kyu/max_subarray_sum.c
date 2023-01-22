#include <stddef.h>

/*
  This challenge is really neat actually. Basically you have to find a chunk where 
  the sum of all the digits in that chunk is the largest possible

  Take `{-2, 1, -3, 4, -1, 2, 1, -5, 4}` for instance
  You could pull {-2, 1, -3} from the beginning, but that would leave you with -4 (1 - 2 - 3)
  You could also pull {4, -1, 2, 1} from the middle and you'd end up with a +6 (4 + 2 + 1 - 1)

  If the whole array is negative numbers then the highest you can get is 0

  Found at https://www.codewars.com/kata/54521e9ec8e60bc4de000d6c
*/

/*
  The brute force goes through every possible solution
  and just returns the section with the biggest number it found
  This would scale really poorly with a larger array
*/
int brute_force_check_section(const int* array, size_t len, int pos, int section_len) {
  if ((pos + section_len) > (int)len) {
    return 0;
  }
  signed int retnum = 0;
  for (int ndx = pos, count = 0; (pos < len) && (count < section_len); ndx++, count++) {
    retnum += array[pos];
  }
  return retnum;
}

int brute_force_maxSequence(const int* array, size_t n) {
  int highest_num = 0;

  for (int rising_len = 0; rising_len < (int)n; rising_len++) {
    for (int pos = 0; pos < ((int)n - rising_len); pos++) {
      int check_num = brute_force_check_section(array, n, pos, rising_len);
      if (check_num > highest_num) {
        highest_num = check_num;
      }
    }
  }
  return highest_num;
}

/* Thought processes

  It's a pretty safe assumption that any sequence that ends up being greater than 0
  both starts and ends in a positive number. To speed up filtering, I can skip until
  I find a positive number. And start inching forward from there. If we go back to 0
  then we can safely skip that section because any number + 0 is still itself and
  therefore wouldn't be contributed to. Once we get back to 0, we can start regressing until
  we get back into the positive numbers


  The code in this block can probably be shrunk a little ( see `maxSequence_v2()` )
  bit but at this stage it works at least
*/
int maxSequence(const int* array, size_t n) {
  int highest_num = 0;
  int current_counting_num = 0;
  
  for (int ndx = 0; ndx < (int)n; ndx++) {
    if (array[ndx] <= 0) // If it's not greater then 0 then checking it makes no sense
      continue;
    
    // counting_index
    for (int c_ndx = ndx; c_ndx < (int)n; c_ndx++) {
      current_counting_num += array[c_ndx];
      
      // If the current number is higher than our previous highest
      if (current_counting_num > highest_num) {
        highest_num = current_counting_num;
      }

      // If it goes below 0 then we can safely skip ahead to this point on the first loop
      if (current_counting_num <= 0) {
        ndx = c_ndx;
        break;
      }
    }
    current_counting_num = 0;
  }

  return highest_num;
}

/*
  This version is based off of the `maxSequence()` function above but removes the second for loop
  If we hard to report the position and length of the set we used to get the largest sum then the 
  second for loop might make sense, but if we don't then having just wastes time and memory
*/
int maxSequence_v2(const int* array, size_t n) {
  int highest_num = 0;
  int current_counting_num = 0;
  
  for (int ndx = 0; ndx < (int)n; ndx++) {
    // Adding a negative number to 0 will not help us find the largest number
    // So if the number is negative and we're already at 0 then we can skip
    // this spot in the array and move on without wasting time
    if ((current_counting_num == 0) && (array[ndx] <= 0)) 
      continue;
    
    current_counting_num += array[ndx];

    if (current_counting_num > highest_num) {
      highest_num = current_counting_num;
    }

    // Having a negative number means we don't have the largest possible. Lets set
    // it back to 0 so that one of the two conditions to skip meaningless iterations are met
    if (current_counting_num < 0) {
      current_counting_num = 0;
    }
  }

  return highest_num;
}

int main(void) {
  // I don't have any prints here because I was using GDB to check the variables we got at the end
  int highest_num = maxSequence((int[]){-2, 1, -3, 4, -1, 2, 1, -5, 4}, 9);
  return 0;
}