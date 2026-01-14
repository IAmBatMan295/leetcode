#include <iostream>

int toh(int n, char src, char aux, char dest) {
  if (n == 1) {
    std::cout << src << "->" << dest << std::endl;

    // base condition for  only one disk which can be
    // simply moved from src to destination.

    return 1;
  }

  int x = toh(n - 1, src, dest, aux);

  // recursively call toh() for top (n-1) destisks to move them to auxiliary
  // rod using destination rod as the effective auxiliary rod.
  // this will run recursively and print all the moves required to do this
  // as well as return the no of moves.

  std::cout << src << "->" << dest << std::endl;

  // print the move for the remaining last disk.

  int y = toh(n - 1, aux, src, dest);

  // now move the call toh() to move the (n-1) disks from auxiliary rod
  // to destination using sourse rod as the effective auxiliary rod.
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
