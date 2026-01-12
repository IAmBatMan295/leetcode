#include <iostream>
#include <string>
std::string badd(std ::string a, std::string b) {
  bool t = a.length() >= b.length();
  std::string &m = t ? a : b;
  std::string &n = t ? b : a;
  int c = 0, i = m.length() - 1, j = n.length() - 1;
  for (; j >= 0; i--, j--) {
    int sum = (m[i] - '0') + (n[j] - '0') + c;
    m[i] = (sum % 2) + '0';
    c = sum / 2;
  }
  while (i >= 0) {
    int sum = (m[i] - '0') + c;
    m[i] = (sum % 2) + '0';
    c = sum / 2;
    i--;
  }
  if (c == 1)
    m.insert(m.begin(), '1');
  return m;
}

int main() {
  std::string a = "101", b = "101";
  std::cout << a << " + " << b << " in binary = " << badd(a, b) << std::endl;
  return 0;
}
