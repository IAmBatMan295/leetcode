#include <iostream>
#include <string>

int foon(std::string haystack, std::string needle) {
  int k = haystack.length(), l = needle.length(), j = 0;
  for (int i = 0; i <= k - l; i++) {

    // check for each indext from 0 to length of heystack-needle.
    // it covers the case where the needle is at the absolute absolute
    // last index it can be.

    while (j < l) {
      if (haystack[i + j] != needle[j]) {

        // from i'th start comparing the characters of heystack to
        // the characters of needle starting from 0.

        j = 0;

        // if they don't match then reset the offset j to 0 (basicaly to where i
        // is) and repeat the process for next i.
        break;
      }

      j++;
    }

    if (j == l)

      // if j was not reset and correctly reached to offset l which is the
      // length of needle, that mean needle was found.
      return i;
  }
  return -1;

  // not found.
}

int main() {

  std::string hay = "11pfhspp", needle = "fh";
  std::cout << "First occurence of the needle is at " << foon(hay, needle)
            << std::endl;

  return 0;
}
