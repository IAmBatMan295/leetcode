/*
we'll simply solve this using binary search.

we search the root between the given number and 0.
*/

#include <iostream>

int SquareRoot(int x) {
  double upper = x, lower = 0, square = 0, mid = 0;

  // we use double for all the variables since we're dealing
  // with floating point numbers.

  while (true) {
    mid = (upper + lower) / 2;
    square = mid * mid;
    if (square >= x && square < x + 0.99)

      // we do the search until the square of the mid is
      // between given number and one bigger than it.

      break;

    if (square > x)
      upper = mid;
    else
      lower = mid;
  }
  return mid;
}
int main() {
  int x;
  std::cout << "Enter a number : ";
  std::cin >> x;
  std::cout << "Square root of " << x << " is " << SquareRoot(x) << std::endl;
}
