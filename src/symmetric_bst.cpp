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

  void inorder(TreeNode *root) {

    result.push_back(root->val);

    if (root->left != nullptr)
      inorder(root->left);
    else
      result.push_back(-1);

    if (root->right != nullptr)
      inorder(root->right);
    else
      result.push_back(-2);

    return;
  }

  std::vector<int> result_inverse;

  void inorder_inverse(TreeNode *root) {

    result_inverse.push_back(root->val);

    if (root->right != nullptr)
      inorder_inverse(root->right);
    else
      result_inverse.push_back(-1);

    if (root->left != nullptr)
      inorder_inverse(root->left);
    else
      result_inverse.push_back(-2);

    return;
  }

  bool isSymmetric(TreeNode *root) {

    inorder(root);

    inorder_inverse(root);

    if (result == result_inverse)
      return true;
    else
      return false;
  }
};

int main() {

  tnode *root = new tnode(1);
  root->left = new tnode(2);
  root->right = new tnode(2);
  root->left->left = new tnode(3);
  root->right->right = new tnode(4);

  Solution test;

  if (test.isSymmetric(root))
    std::cout << "\nThe tree is symmetric.\n";
  else
    std::cout << "\nThe tree is asymmetric.\n";

  return 0;
}
