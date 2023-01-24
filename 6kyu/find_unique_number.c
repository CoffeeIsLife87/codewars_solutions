/*
  Find the unique number in an array

  [1, 1, 1, 2, 1, 1] would give 2
  [0, 0, 0.55, 0, 0] would give 0.55

  Found at https://www.codewars.com/kata/585d7d5adb20cf33cb000235
*/

#include <stddef.h>
#include <stdbool.h>

float finduniq(const float *nums, size_t n)
{
  float common_num;
  if (nums[0] == nums[1]) // If a number appears twice, it's common
    common_num = nums[0];
  else if (nums[0] == nums[2]) { // if 0 and 2 match, then 1 has to be unique because we already checked it against 0
    return nums[1];
  } else { // if 0 and 1 didn't match and neither did 0 and 2, that means 0 is the unique number
    return nums[0];
  }

  for (size_t ndx = 2; ndx < n; ndx++) {
    if (nums[ndx] != common_num) {
      return nums[ndx];
    }
  }
  return 0;
}

int main(void) {
  float ret_val = finduniq((const float[]){ 0, 0, 0.55, 0, 0 }, 5);
  return 0;
}