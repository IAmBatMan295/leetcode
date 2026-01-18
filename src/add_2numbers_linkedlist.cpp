#include <iostream>

// simply create another linked, add the numbers,
// generate the carry and store it in the new list.
// maintain 3 different iterators for all 3 different lists
// and once any of the original lists finish you create a
// new pointer that tracks the list thats not empty and
// then keep adding the carry untill that list is also empty.
// finaly terminate the list with propper edgecase handling for
// carry being 1 even after adding all elements.

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using node = ListNode;

node *AddTwoNumbers(node *l1, node *l2) {
  node *iterator1 = l1, *iterator2 = l2;
  node *l3 = new node();

  // new list's head(dummy).
  //
  node *iterator3 = l3;

  int carry = 0, sum = 0;

  while (iterator1 != nullptr && iterator2 != nullptr) {

    iterator3->next = new node();
    iterator3 = iterator3->next;

    // create new node in the new list.

    sum = iterator1->val + iterator2->val + carry;

    iterator3->val = sum % 10;

    // store the modulus of the sum.

    carry = sum < 10 ? 0 : 1;

    // generate carry.

    iterator1 = iterator1->next;
    iterator2 = iterator2->next;
  }
  node *remaining = (iterator1 == nullptr) ? iterator2 : iterator1;

  // determine the non-null list.

  while (remaining != nullptr) {

    iterator3->next = new node();
    iterator3 = iterator3->next;

    sum = remaining->val + carry;
    iterator3->val = sum % 10;
    carry = sum < 10 ? 0 : 1;
    remaining = remaining->next;
  }

  // add and append elements with carry from the remaining list to the new list.

  if (carry == 1)
    iterator3->next = new node(1);

  // handle the edgecase.

  return (l3->next);

  // return the actual head of the list instead of the dummy initializer.
}

int main() {
  node *l1 = new node(9);
  l1->next = new node(5);
  l1->next->next = new node(5);
  node *l2 = new node(5);
  l2->next = new node(5);

  node *cur = l1;

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }
  std::cout << "\n";

  cur = l2;

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  // print the list before removing duplicates.

  std::cout << "\nafter operation :" << "\n";

  cur = AddTwoNumbers(l1, l2);

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  std::cout << "\n";

  return 0;
}
