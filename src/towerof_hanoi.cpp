#include <iostream>

int toh(int n, char s, char a, char d) {
  if (n == 1) {
    std::cout << s << "->" << d << std::endl;
    return 1;
  }
  return toh(n - 1, s, d, a) + toh(1, s, a, d) + toh(n - 1, a, s, d);
}
int main() {

  int n;
  std::cout << "\nEnter the no of disks: ";
  std::cin >> n;
  std::cout << "The operations are:\n";
  int sum = toh(n, 's', 'a', 'd');
  std::cout << "\nTotal no of steps= " << sum << std::endl;

  return 0;
}
