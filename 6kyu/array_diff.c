#include <stdbool.h> // Needed for the definition of `bool`
#include <stdlib.h> // Needed for `free()`
#include <string.h> // Needed for `memcpy()`

// Found at https://www.codewars.com/kata/523f5d21c841566fde000009
// I didn't bother writing the tests for this one cause it's a lot of effort

int *array_diff(const int *arr1, size_t n1, const int *arr2, size_t n2, size_t *z) {
  if (n1 <= 0) {
    *z = 0; // Just to be kind <3
    return NULL;
  }
  
  int* working_arr = (int*)malloc(sizeof(int) * n1);
  
  memcpy(working_arr, arr1, sizeof(int) * n1);
  
  int length = (int)n1;
  for (int b_ndx = 0; b_ndx < n2; b_ndx++) {
    for (int a_ndx = 0; a_ndx < length; a_ndx++) {
      if (!(working_arr[a_ndx] == arr2[b_ndx]))
        continue;
      
      for (int reset_pos = a_ndx; reset_pos < length; reset_pos++) {
        
        if ((reset_pos + 1) >= length)
          break;
        
        working_arr[reset_pos] = working_arr[reset_pos + 1];
      }

      a_ndx -= 1;
      length -= 1;
    }
  }

  int* ret_arr = malloc(sizeof(int) * length);
  memcpy(ret_arr, working_arr, sizeof(int) * length);
  free(working_arr);
  *z = length;
  return ret_arr;
}

int main(void) {
  return 0;
}