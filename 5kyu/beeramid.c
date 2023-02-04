/*
  Create a cup pyramid. 1 4 9 16 25 36 ( The pyramid scales based on i^2 )

  Found at https://www.codewars.com/kata/51e04f6b544cf3f6550000c1
*/

#define sqr(i) (i * i)

int beeramid(double bonus, double price) {
  int ret_num = 0;
  double current_cost = price;
  while (current_cost <= bonus) {
    current_cost += (price * (sqr((2 + ret_num))));
    ret_num += 1;
  } 

  return ret_num;
}

int main(void) {
  beeramid(1500, 2);
  beeramid(10, 2);
  beeramid(9, 2);
  beeramid(5000, 3);
  return 0;
}