# C++ Reference Guide: Essential Concepts

## Point 3: String Parameters - Copy vs Reference vs View

### The Problem: Hidden Copies

When you pass a string to a function, C++ can either **copy** the entire string or just **reference** it.

```cpp
// BAD: Makes a full copy! 🐌
void printString(std::string str) {
    std::cout << str << std::endl;
}

// GOOD: Just references the original! ⚡
void printString(const std::string& str) {
    std::cout << str << std::endl;
}

// BEST (C++17): Lightweight view! 🚀
void printString(std::string_view str) {
    std::cout << str << std::endl;
}
```

### Real Example: Checking if a Word is a Palindrome

```cpp
// ❌ BAD: Unnecessary copy
bool isPalindrome(std::string word) {
    int left = 0;
    int right = word.length() - 1;

    while (left < right) {
        if (word[left] != word[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// ✅ GOOD: No copy, just read
bool isPalindrome(const std::string& word) {
    int left = 0;
    int right = word.length() - 1;

    while (left < right) {
        if (word[left] != word[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// ⭐ BEST: Works with more types, modern C++
bool isPalindrome(std::string_view word) {
    int left = 0;
    int right = word.length() - 1;

    while (left < right) {
        if (word[left] != word[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

### When to Use What?

| Type                           | When to Use                                           | Example                                          |
| ------------------------------ | ----------------------------------------------------- | ------------------------------------------------ |
| `std::string` (by value)       | You need to **modify** the string inside the function | `std::string toUpper(std::string s)`             |
| `const std::string&`           | Read-only, need backwards compatibility               | `bool contains(const std::string& text, char c)` |
| `std::string_view`             | Read-only, modern C++17+                              | `int countVowels(std::string_view text)`         |
| `std::string&` (non-const ref) | You want to **modify** the original string            | `void makeUpperCase(std::string& s)`             |

### Complete Example: Different Scenarios

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

// Scenario 1: READ-ONLY - Use string_view
int countSpaces(std::string_view text) {
    int count = 0;
    for (char c : text) {
        if (c == ' ') count++;
    }
    return count;
}

// Scenario 2: MODIFY A COPY - Take by value
std::string reverseString(std::string text) {
    std::reverse(text.begin(), text.end());
    return text;  // Return the modified copy
}

// Scenario 3: MODIFY THE ORIGINAL - Take by reference
void removeSpaces(std::string& text) {
    text.erase(
        std::remove(text.begin(), text.end(), ' '),
        text.end()
    );
}

// Scenario 4: Backwards compatibility - const reference
bool startsWith(const std::string& text, const std::string& prefix) {
    if (prefix.length() > text.length()) return false;
    return text.substr(0, prefix.length()) == prefix;
}

int main() {
    std::string message = "Hello World";

    // string_view: Just reading
    std::cout << "Spaces: " << countSpaces(message) << std::endl;

    // By value: Get a modified copy
    std::string reversed = reverseString(message);
    std::cout << "Reversed: " << reversed << std::endl;
    std::cout << "Original: " << message << std::endl;  // Unchanged!

    // By reference: Modify the original
    removeSpaces(message);
    std::cout << "After removing spaces: " << message << std::endl;

    return 0;
}
```

### Memory Impact

```cpp
std::string bigString(1000000, 'a');  // 1 MB string

// This copies 1 MB! 😱
void processV1(std::string s) { 
    // ... 
}

// This copies 0 bytes! 😊
void processV2(std::string_view s) { 
    // ... 
}

processV1(bigString);  // Allocates 1 MB
processV2(bigString);  // Allocates 0 MB
```

---

## Point 5: Reverse Iterators

### What Are Iterators?

Think of iterators as **pointers** that help you traverse containers without worrying about indices.

```cpp
std::vector<int> nums = {1, 2, 3, 4, 5};

// Using indices (old way)
for (int i = 0; i < nums.size(); i++) {
    std::cout << nums[i] << " ";
}

// Using iterators (modern way)
for (auto it = nums.begin(); it != nums.end(); ++it) {
    std::cout << *it << " ";
}

// Range-based for (easiest, same as iterators under the hood)
for (int num : nums) {
    std::cout << num << " ";
}
```

### Reverse Iterators: Going Backwards

```cpp
std::vector<int> nums = {10, 20, 30, 40, 50};

// Forward: 10 20 30 40 50
for (auto it = nums.begin(); it != nums.end(); ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl;

// Reverse: 50 40 30 20 10
for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl;
```

### Iterator Types Cheat Sheet

| Iterator     | Description                                        | Example                          |
| ------------ | -------------------------------------------------- | -------------------------------- |
| `.begin()`   | Points to first element                            | `nums.begin()` → `10`            |
| `.end()`     | Points **after** last element (don't dereference!) | `nums.end()` is invalid to read  |
| `.rbegin()`  | Reverse begin (points to last element)             | `nums.rbegin()` → `50`           |
| `.rend()`    | Reverse end (points before first element)          | `nums.rend()` is invalid to read |
| `.cbegin()`  | Const begin (read-only)                            | Same as `.begin()` but const     |
| `.crbegin()` | Const reverse begin (read-only)                    | Same as `.rbegin()` but const    |

### Real Example: Check if String is Palindrome

```cpp
#include <string>
#include <algorithm>

// Method 1: Using indices
bool isPalindromeIndex(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// Method 2: Using reverse iterators ⭐
bool isPalindromeIterator(const std::string& s) {
    auto forward = s.begin();
    auto backward = s.rbegin();

    while (forward < backward.base()) {
        if (*forward != *backward) {
            return false;
        }
        ++forward;
        ++backward;
    }
    return true;
}

// Method 3: Using STL algorithm (most elegant!)
bool isPalindromeSTL(const std::string& s) {
    return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}
```

### Real Example: Find Last Occurrence of a Value

```cpp
#include <vector>
#include <algorithm>

// Using reverse iterator
int findLastIndex(const std::vector<int>& nums, int target) {
    auto it = std::find(nums.rbegin(), nums.rend(), target);

    if (it == nums.rend()) {
        return -1;  // Not found
    }

    // Convert reverse iterator to index
    return std::distance(it, nums.rend()) - 1;
}

// Example usage
int main() {
    std::vector<int> nums = {1, 3, 5, 3, 7, 3, 9};
    int lastPos = findLastIndex(nums, 3);  // Returns 5 (last 3)
    return 0;
}
```

### Real Example: Reverse a Portion of a Vector

```cpp
#include <vector>
#include <algorithm>

void reverseRange(std::vector<int>& nums, int start, int end) {
    // Using reverse iterators makes this elegant
    std::reverse(nums.begin() + start, nums.begin() + end + 1);
}

// Example
int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    reverseRange(nums, 2, 5);  // Reverse indices 2-5
    // Result: {1, 2, 6, 5, 4, 3, 7}
    return 0;
}
```

### When to Use Indices vs Iterators?

**Use Indices When:**

- You need the actual position number
- You're working with multiple containers of different sizes
- You need random access (jumping around)

```cpp
// Merging two sorted arrays - indices are clearer
std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    int i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            result.push_back(a[i++]);
        } else {
            result.push_back(b[j++]);
        }
    }

    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);

    return result;
}
```

**Use Iterators When:**

- You're traversing sequentially
- You want to use STL algorithms
- You want code that works with any container

```cpp
// Find and remove all even numbers - iterators shine here
void removeEvens(std::vector<int>& nums) {
    nums.erase(
        std::remove_if(nums.begin(), nums.end(), 
                      [](int n) { return n % 2 == 0; }),
        nums.end()
    );
}
```

---

## Point 6: Unifying Duplicate Loops (DRY Principle)

### The Problem: Duplicate Code

When you have two loops doing almost the same thing, you're violating **DRY** (Don't Repeat Yourself).

### Example: Merging Two Sorted Linked Lists

```cpp
// ❌ BAD: Duplicate logic
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    // Loop 1: While both lists have nodes
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Loop 2: Append remaining from l1 (DUPLICATE LOGIC!)
    while (l1 != nullptr) {
        tail->next = l1;
        l1 = l1->next;
        tail = tail->next;
    }

    // Loop 3: Append remaining from l2 (DUPLICATE LOGIC!)
    while (l2 != nullptr) {
        tail->next = l2;
        l2 = l2->next;
        tail = tail->next;
    }

    return dummy.next;
}

// ✅ GOOD: Unified logic
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    // Single loop handles everything!
    while (l1 != nullptr || l2 != nullptr) {
        if (l2 == nullptr || (l1 != nullptr && l1->val <= l2->val)) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    return dummy.next;
}

// ⭐ EVEN BETTER: Simplest approach
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Remaining nodes (one of these will be nullptr)
    tail->next = (l1 != nullptr) ? l1 : l2;

    return dummy.next;
}
```

### Example: Finding Maximum in Different Ranges

```cpp
// ❌ BAD: Two separate loops
int findMaxInVector(const std::vector<int>& nums) {
    if (nums.empty()) return INT_MIN;

    int maxVal = nums[0];

    // Find max in first half
    for (int i = 0; i < nums.size() / 2; i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    // Find max in second half (DUPLICATE!)
    for (int i = nums.size() / 2; i < nums.size(); i++) {
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    return maxVal;
}

// ✅ GOOD: One loop
int findMaxInVector(const std::vector<int>& nums) {
    if (nums.empty()) return INT_MIN;

    int maxVal = nums[0];
    for (int num : nums) {
        if (num > maxVal) {
            maxVal = num;
        }
    }
    return maxVal;
}

// ⭐ BEST: Use STL
int findMaxInVector(const std::vector<int>& nums) {
    if (nums.empty()) return INT_MIN;
    return *std::max_element(nums.begin(), nums.end());
}
```

### Example: Processing Two Arrays of Different Lengths

```cpp
#include <vector>
#include <algorithm>

// Problem: Sum elements from two arrays, handling different lengths

// ❌ BAD: Separate loops
int sumTwoArrays(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;

    // Process common part
    int minLen = std::min(a.size(), b.size());
    for (int i = 0; i < minLen; i++) {
        sum += a[i] + b[i];
    }

    // Process remaining from array a
    for (int i = minLen; i < a.size(); i++) {
        sum += a[i];
    }

    // Process remaining from array b (DUPLICATE PATTERN!)
    for (int i = minLen; i < b.size(); i++) {
        sum += b[i];
    }

    return sum;
}

// ✅ GOOD: Unified loop
int sumTwoArrays(const std::vector<int>& a, const std::vector<int>& b) {
    int sum = 0;
    int maxLen = std::max(a.size(), b.size());

    for (int i = 0; i < maxLen; i++) {
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
    }

    return sum;
}
```

### Example: Building a String with Carry Logic

This is like adding two binary numbers or adding digits with carry.

```cpp
// ❌ BAD: Two separate while loops
std::string addWithCarry(const std::string& num1, const std::string& num2) {
    std::string result;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    // While both have digits
    while (i >= 0 && j >= 0) {
        int sum = (num1[i] - '0') + (num2[j] - '0') + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
        i--;
        j--;
    }

    // Process remaining from num1 (DUPLICATE LOGIC!)
    while (i >= 0) {
        int sum = (num1[i] - '0') + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
        i--;
    }

    // Process remaining from num2 (DUPLICATE LOGIC!)
    while (j >= 0) {
        int sum = (num2[j] - '0') + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
        j--;
    }

    if (carry) result += '1';

    std::reverse(result.begin(), result.end());
    return result;
}

// ✅ GOOD: Unified loop with OR condition
std::string addWithCarry(const std::string& num1, const std::string& num2) {
    std::string result;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int carry = 0;

    // Single loop: continues while ANY condition is true
    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
```

### The Key Pattern: Using OR (||) to Unify Loops

```cpp
// Pattern: Process two things that might have different lengths

// ❌ BAD
while (condition1 && condition2) { /* both */ }
while (condition1) { /* only 1 */ }
while (condition2) { /* only 2 */ }

// ✅ GOOD
while (condition1 || condition2) {
    if (condition1) { /* do thing 1 */ }
    if (condition2) { /* do thing 2 */ }
}
```

### When NOT to Unify Loops

Sometimes separate loops are actually clearer!

```cpp
// This is fine - the loops do DIFFERENT things
void processData(const std::vector<int>& nums) {
    // Pass 1: Calculate sum
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }

    // Pass 2: Calculate variance using sum
    double mean = static_cast<double>(sum) / nums.size();
    double variance = 0;
    for (int num : nums) {
        variance += (num - mean) * (num - mean);
    }
    variance /= nums.size();
}
```

---

## Summary: Quick Reference

### String Parameters

- **Read-only**: Use `std::string_view` or `const std::string&`
- **Need to modify copy**: Use `std::string` (by value)
- **Modify original**: Use `std::string&` (non-const reference)

### Iterators

- **Forward**: `.begin()` to `.end()`
- **Reverse**: `.rbegin()` to `.rend()`
- **Const**: Add `c` prefix (`.cbegin()`, `.crbegin()`)
- **Access value**: Use `*it` to dereference

### Unifying Loops

- Use `||` condition to process multiple sources
- Check bounds inside: `if (i < size)` before accessing
- One loop = one place to fix bugs!

---

## Practice Exercises

1. **Rewrite this function to use `string_view`:**
   
   ```cpp
   int countCharacter(std::string text, char c) {
       int count = 0;
       for (char ch : text) {
           if (ch == c) count++;
       }
       return count;
   }
   ```

2. **Rewrite using reverse iterators:**
   
   ```cpp
   void printReverse(const std::vector<int>& nums) {
       for (int i = nums.size() - 1; i >= 0; i--) {
           std::cout << nums[i] << " ";
       }
   }
   ```

3. **Unify these two loops:**
   
   ```cpp
   std::vector<int> result;
   for (int x : arr1) result.push_back(x);
   for (int x : arr2) result.push_back(x);
   ```

---

**Remember**: Write code that is easy to read, easy to maintain, and hard to break! 🚀
