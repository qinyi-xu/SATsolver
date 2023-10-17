#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  leftChild = lChild;
  rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  bool leftValue = false;
  bool rightValue = false;
  if(this->getContent() == "+") {
    if (this->getLeftChild() == nullptr || this->getRightChild() == nullptr) {
      throw ((std::string) "invalid input");
    }
    leftValue = this->getLeftChild()->evaluate(assignment);
    rightValue = this->getRightChild()->evaluate(assignment);
    return leftValue || rightValue;
  } else if (this->getContent() == "*") {
    if (this->getLeftChild() == nullptr || this->getRightChild() == nullptr) {
      throw ((std::string) "invalid input");
    }
    leftValue = this->getLeftChild()->evaluate(assignment);
    rightValue = this->getRightChild()->evaluate(assignment);
    return leftValue && rightValue;
  } else if (this->getContent() == "-") {
    if (this->getLeftChild() == nullptr) {
      throw ((std::string) "invalid input");
    }
    return !this->getLeftChild()->evaluate(assignment);
  }
  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if(this->getContent() == "1") {
    return true;
  }
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (assignment.count(this->getContent()) == 1) {
    return assignment.at(this->getContent());
  } else {
    throw ((std::string) "incomplete assignment");
  }
}

TreeNode::~TreeNode() {
  // your code starts here
  this->content = "";
  delete[]this->leftChild;
  this->leftChild = nullptr;
  delete[]this->rightChild;
  this->rightChild = nullptr;
}
