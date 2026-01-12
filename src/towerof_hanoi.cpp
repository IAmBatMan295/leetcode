#include <iostream>

int toh(int n, char s, char a, char d) {
  if (n == 1) {
    std::cout << s << "->" << d << std::endl;
    return 1;
  }
  int x = toh(n - 1, s, d, a);
  std::cout << s << "->" << d << std::endl;
  int y = toh(n - 1, a, s, d);
  return x + y + 1;
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
