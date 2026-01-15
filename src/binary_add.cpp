
// Our approach is to iterate through each digit at a time and add them
// by converting them to int and then add then with carry using modulo 2
// logic to generate carry.

#include <iostream>
#include <string>

std::string BinaryAdd(const std ::string &s1, const std::string &s2) {

  // Using const std::string& references to strings instead of using std::string
  // to avoid copies.

  bool t = s1.length() >= s2.length();

  std::string big = t ? s1 : s2;
  const std::string &small = t ? s2 : s1;

  // set the aliases to keep track of bigger string.

  // here we created a copy of the bigger string since we are
  // going to operate on it and store our result in that string
  // in place which is not possible with readonly reference.

  int carry = 0, sum = 0;
  auto it1 = big.rbegin();
  auto it2 = small.rbegin();

  // our reverse iterators.

  while (it1 != big.rend() || it2 != small.rend()) {

    if (it2 == small.rend())
      sum = (*it1 - '0') + carry;

    // do the operations on the remaining part of the bigger string
    // if both strings weren't of equal length.

    else {
      sum = (*it1 - '0') + (*it2 - '0') + carry;

      // generate overall sum.
      // this is executed untill smaller string is ended.

      it2++;
    }

    // here *it is just a character which just an
    // ASCII representation of an integer.

    // we simply convert it into binary by subtracting
    //'0' equivalent to 48 in integer.since the original
    // string just containsts 0 and 1 only, it will result in
    // 0 and 1 in integer too.

    *it1 = (sum % 2) + '0';

    // we assign 2's modulus to our resultant digit.
    // also converting it back into char by adding '0'.

    carry = sum / 2;

    // generate carry out for next digit operation.
    // this divide by 2 works here only because the
    // digits are 1 and 0 so max result is 3.

    it1++;
  }

  if (carry == 1)
    big.insert(big.begin(), '1');

  // if there's still a carry after all the operations
  // then simply add a new digit at the begining of
  // the bigger string (MSB).

  return big;
}

int main() {

  std::string a = "1", b = "11";

  std::cout << a << " + " << b << " in binary = " << BinaryAdd(a, b) << "\n";

  return 0;
}
