#include <iostream>
#include <string>
using namespace std;

int foon(string haystack, string needle) {
  int k = haystack.length(), l = needle.length(), j = 0;
  for (int i = 0; i <= k - l; i++) {
    while (j < l) {
      if (haystack[i + j] != needle[j]) {
        j = 0;
        break;
      }

      j++;
    }
    if (j == l)
      return i;
  }
  return -1;
}

int main() {

  string hay = "11pfhspp", needle = "fh";
  cout << "First occurence of the needle is at " << foon(hay, needle) << endl;

  return 0;
}
