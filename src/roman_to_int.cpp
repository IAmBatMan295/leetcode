#include <iostream>
#include <string>
using namespace std;
int romanToInt(string s) {
  int j = s.length() - 1, sum = 0;
  while (j >= 0) {
    if (j != 0) {
      switch (s[j]) {
      case 'I': {
        sum++;
        j--;
        break;
      }
      case 'V': {
        if (s[j - 1] == 'I') {
          sum += 4;
          j -= 2;
        } else {
          sum += 5;
          j--;
        }
        break;
      }
      case 'X': {
        if (s[j - 1] == 'I') {
          sum += 9;
          j -= 2;
        } else {
          sum += 10;
          j--;
        }
        break;
      }
      case 'L': {
        if (s[j - 1] == 'X') {
          sum += 40;
          j -= 2;
        } else {
          sum += 50;
          j--;
        }
        break;
      }
      case 'C': {
        if (s[j - 1] == 'X') {
          sum += 90;
          j -= 2;
        } else {
          sum += 100;
          j--;
        }
        break;
      }
      case 'D': {
        if (s[j - 1] == 'C') {
          sum += 400;
          j -= 2;
        } else {
          sum += 500;
          j--;
        }
        break;
      }
      case 'M': {
        if (s[j - 1] == 'C') {
          sum += 900;
          j -= 2;
        } else {
          sum += 1000;
          j--;
        }
      }
      }
    } else {
      switch (s[j]) {
      case 'I': {
        sum += 1;
        break;
      }
      case 'V': {
        sum += 5;
        break;
      }
      case 'X': {
        sum += 10;
        break;
      }
      case 'L': {
        sum += 50;
        break;
      }
      case 'C': {
        sum += 100;
        break;
      }
      case 'D': {
        sum += 500;
        break;
      }
      case 'M': {
        sum += 1000;
        break;
      }
      }
      j--;
    }
  }

  return sum;
}
int main() {
  string s = "MCDIX";
  cout << s << " in Roman is: " << romanToInt(s) << endl;
  return 0;
}
