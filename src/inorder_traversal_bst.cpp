#include <iostream>
#include <vector>

typedef struct TreeNode tnode;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  std::vector<int> result;

  std::vector<int> inorderTraversal(TreeNode *root) {

    if (root == nullptr)
      return {};

    if (root->left != nullptr)
      inorderTraversal(root->left);

    result.push_back(root->val);

    if (root->right != nullptr)
      inorderTraversal(root->right);

    return result;
  }
};

int main() {
  tnode *obj = new tnode(1);
  obj->left = new tnode(2);
  obj->right = new tnode(3);
  obj->right->left = new tnode(4);

  Solution test;

  std::vector<int> result = test.inorderTraversal(obj);

  std::cout << "\nInorder Traversal : ";
  for (auto iter = result.begin(); iter != result.end(); iter++) {
    std::cout << *iter << " ";
  }

  std::cout << "\n";
  return 0;
}
