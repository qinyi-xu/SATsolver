#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  int curID = 0;
  if (subRoot->getContent() == "+") {
    curID = varIdCounter;
    varIdCounter++;
    addOrEq(curID, transSubformula(subRoot->getLeftChild()), transSubformula(subRoot->getRightChild()));
    return curID;
  } else if (subRoot->getContent() == "*") {
    curID = varIdCounter;
    varIdCounter++;
    addAndEq(curID, transSubformula(subRoot->getLeftChild()), transSubformula(subRoot->getRightChild()));
    return curID;
  } else if (subRoot->getContent() == "-") {
    curID = varIdCounter;
    varIdCounter++;
    addNegEq(curID, transSubformula(subRoot->getLeftChild()));
    return curID;
  } else {
    if (varIdTable.count(subRoot->getContent()) == 0) {
      curID = varIdCounter;
      varIdCounter++;
      varIdTable.insert({subRoot->getContent(), curID});
      return curID;
    } else {
      return varIdTable.at(subRoot->getContent());
    }
  }
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  cnf.push_back({0 - curID, 0 - childID});
  cnf.push_back({curID, childID});
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({0 - curID, leftID, rightID});
  cnf.push_back({0 - leftID, curID});
  cnf.push_back({0 - rightID, curID});
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({0 - curID, leftID});
  cnf.push_back({0 - curID, rightID});
  cnf.push_back({0 - leftID, 0 - rightID, curID});
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  cnf.push_back({1});
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return varIdCounter - 1;
}
