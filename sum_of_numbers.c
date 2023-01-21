/* Sum of Numbers
  This challenge is like a scuffed factorial

  Find the sum of the numbers and every integer number between them
  (1, 0) --> 1 (1 + 0 = 1)
  (1, 2) --> 3 (1 + 2 = 3)
  (0, 1) --> 1 (0 + 1 = 1)
  (1, 1) --> 1 (1 since both are same)
  (-1, 0) --> -1 (-1 + 0 = -1)
  (-1, 2) --> 2 (-1 + 0 + 1 + 2 = 2)

  Found at https://www.codewars.com/kata/55f2b110f61eb01779000053
*/

/* 
  This bit doesn't work when `a` is negative and `b` is positive
  It probably has something to do with the way I'm calling the functions
*/
/*
int sum_function(signed int u , signed int l) {
  signed sum = l;
  while(u != l) {
    sum += (l += 1);
  }
  return sum;
}

//#define get_sum(a, b) sum_function((a < b) ? b, a : a, b);
//int get_sum(signed int a, signed int b) {return sum_function((()a <= (signed int)b) ? b, a : a, b);}
*/

/* 
  This one works by determining which is larger and using the macro based on that

  I think the file size using this method might be marginally larger depending 
  on how often is used. C Macros are basically template code that write more code
  based on the input they're given. So this code appears twice slightly 
  differently in this version of the code
*/
#define get_sum_macro(u, l) ({  \
  signed int sum = l;           \
  while(u != l) {               \
    sum += (l += 1);            \
  }                             \
  return sum;                   \
})

int m_get_sum(int a , int b) {
  (a <= b) ? get_sum_macro(b, a) : get_sum_macro(a, b);
}

/*
  This section of code still has a tenary opperator but instead of doing the math
  based on a macro, it uses a function. Meaning no duplicate code in the final compiled version

*/
int get_sum_function(int upper, int lower) {
  signed int sum = lower;
  while (upper != lower) {
    sum += (lower += 1);
  }
  return sum;
}

int f_get_sum(int a, int b) {
  return (a <= b ? get_sum_function(b, a) : get_sum_function(a, b));
}

int main(void) {
  int result = f_get_sum(5 , -1);
  return 0;
}