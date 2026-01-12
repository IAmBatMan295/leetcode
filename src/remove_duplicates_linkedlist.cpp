#include <iostream>
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
using node = ListNode;

node *rmd(node *head) {
  if (head == nullptr || head->next == nullptr)
    return head;
  node *prev = head;
  node *cur = head->next;

  while (cur != nullptr) {
    if (cur->val == prev->val)
      cur = cur->next;
    else {
      prev->next = cur;
      prev = cur;
      cur = cur->next;
    }
  }
  prev->next = nullptr;
  return head;
}

int main() {

  node *head = new node(1);
  head->next = new node(1);
  head->next->next = new node(2);
  head->next->next->next = new node(3);
  head->next->next->next->next = new node(3);

  std::cout << "\nBefore operation :" << "\n";
  node *cur = head;
  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  std::cout << "\nafter operation :" << "\n";

  cur = rmd(head);

  while (cur != nullptr) {
    std::cout << cur->val << " ";
    cur = cur->next;
  }

  std::cout << std::endl;

  return 0;
}
