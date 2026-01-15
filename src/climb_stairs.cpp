
// This is simply solved by fibonacci series.

#include <iostream>

int climbstairs(int n) {

  int sum = 0, t0 = 0, t1 = 1;

  // the zeroth  term is 0 and the first term is 1.

  for (int i = 1; i <= n; i++) {
    sum = t0 + t1;
    t0 = t1;
    t1 = sum;
  }
  return t1;
}
int main() {
  int n;
  std::cout << "Enter the number of stairs:";
  std::cin >> n;
  std::cout << "The no of ways to climb " << n
            << " stairs with only 1 or 2 stairs at a time is: "
            << climbstairs(n) << std::endl;
  return 0;
}
