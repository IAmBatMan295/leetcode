#include <iostream>
#include <string>
using namespace std;
int romanToInt(string s) {
  int j = s.length() - 1, sum = 0;
  while (j >= 0) {
    if (j != 0) {
      if (s[j] == 'I') {
        sum++;
        j--;
      } else if (s[j] == 'V') {
        if (s[j - 1] == 'I') {
          sum += 4;
          j -= 2;
        } else {
          sum += 5;
          j--;
        }
      } else if (s[j] == 'X') {
        if (s[j - 1] == 'I') {
          sum += 9;
          j -= 2;
        } else {
          sum += 10;
          j--;
        }
      } else if (s[j] == 'L') {
        if (s[j - 1] == 'X') {
          sum += 40;
          j -= 2;
        } else {
          sum += 50;
          j--;
        }
      } else if (s[j] == 'C') {
        if (s[j - 1] == 'X') {
          sum += 90;
          j -= 2;
        } else {
          sum += 100;
          j--;
        }
      } else if (s[j] == 'D') {
        if (s[j - 1] == 'C') {
          sum += 400;
          j -= 2;
        } else {
          sum += 500;
          j--;
        }
      } else {
        if (s[j - 1] == 'C') {
          sum += 900;
          j -= 2;
        } else {
          sum += 1000;
          j--;
        }
      }
    } else {
      if (s[j] == 'I')
        sum += 1;
      if (s[j] == 'V')
        sum += 5;
      if (s[j] == 'X')
        sum += 10;
      if (s[j] == 'L')
        sum += 50;
      if (s[j] == 'C')
        sum += 100;
      if (s[j] == 'D')
        sum += 500;
      if (s[j] == 'M')
        sum += 1000;
      j--;
    }
  }

  return sum;
}
int main() {
  string s = "XC";
  cout << s << " in Roman is: " << romanToInt(s) << endl;
  return 0;
}
