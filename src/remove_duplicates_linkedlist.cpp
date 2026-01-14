#include <iostream>

// In this problem our approach will be to just iterate through
// the whole list with  2 pointers, one that tracks distinct elements
// and the other is our iterator. And we simply rearrange the links and
// skip the duplicates.

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition of the structure with constructors.

using node = ListNode;

// alias for the ListNode.

node *RemoveDuplicates(node *head) {

  if (head == nullptr || head->next == nullptr)
    return head;

  // if head is null or there's only one element then return the head.

  node *prev = head;
  node *cur = head->next;

  // prev variable tracks our distinct elements while cur is our iterator.

  while (cur != nullptr) {
    if (cur->val == prev->val)
      cur = cur->next;
    else {
      prev->next = cur;
      prev = cur;
      cur = cur->next;
    }
  }

  // until cur becomes null, we keep skipping nodes if its value its
  // same as the prev and if its not we attatch prev to cur, increment
  // the prev and then also the cur. here we dont delete the skipped nodes
  // but it's the recommended practice for the projects and other useful
  // implementations.

  prev->next = nullptr;

  // before returning the head, we make sure the last distinct node
  // is correctly terminated with nullptr in case the cur kept skipping
  // all the duplicates and the list ended.

  return head;
}

int main() {

  node *head = new node(1);
  head->next = new node(1);
  head->next->next = new node(2);
  head->next->next->next = new node(3);
  head->next->next->next->next = new node(3);

  // here we made the list manually with constructors and chaining the next
  // pointers.

  std::cout << "\nBefore operation :" << "\n";

  node *cur = head;

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  // print the list before removing duplicates.

  std::cout << "\nafter operation :" << "\n";

  cur = RemoveDuplicates(head);

  // remove the dupicates.

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  // print the list again after removing duplicates.

  std::cout << "\n";

  return 0;
}
