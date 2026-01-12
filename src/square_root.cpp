#include <iostream>

int mysqrt(int x) {
  double u = x, l = 0, k = 0, mid = 0;
  while (true) {
    mid = (u + l) / 2;
    k = mid * mid;
    if (k >= x && k < x + 0.99)
      break;

    if (k > x)
      u = mid;
    else
      l = mid;
  }
  return mid;
}
int main() {
  int x;
  std::cout << "Enter a number : ";
  std::cin >> x;
  std::cout << "Square root of " << x << " is " << mysqrt(x) << std::endl;
}
