#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include "constant.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  TreeNode *treeNode = nullptr;
  TreeNode *leftChild = nullptr;
  TreeNode *rightChild = nullptr;
  Token token = tknzr->getToken();
  if (token.type != And) {
    treeNode = parseTerm();
  }
  if(!tknzr->hasToken()){
    return treeNode;
  }
  token = tknzr->getToken();
  while (token.type == And){
    leftChild = treeNode;
    treeNode = new OperatorNode(token.content);
    tknzr->advanceToken();
    rightChild = parseTerm();
    treeNode->updateChildren(leftChild, rightChild);
    if(!tknzr->hasToken()){
      break;
    }
    token = tknzr->getToken();
  }
  return treeNode;
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here
  TreeNode *treeNode = nullptr;
  TreeNode *leftChild = nullptr;
  if(!tknzr->hasToken()){
    throw ((std::string) "invalid input");
  }
  Token token = tknzr->getToken();
  tknzr->advanceToken();
  if (token.type == Constant) {
    treeNode = new ConstantNode(token.content);
  } else if (token.type == VarName) {
    treeNode = new VariableNode(token.content);
  } else if (token.type == Not) {
    treeNode = new OperatorNode(token.content);
    leftChild = parseTerm();
    treeNode->updateLeftChild(leftChild);
  } else if (token.type == LeftBracket) {
    treeNode = parseFormula();
    if (!tknzr->hasToken()) {
      throw ((std::string) "invalid input");
    }
    token = tknzr->getToken();
    if(token.type == RightBracket){
      tknzr->advanceToken();
    } else {
      throw ((std::string) "invalid input");
    }
  } else {
    throw ((std::string) "invalid input");
  }
  return treeNode;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  TreeNode *treeNode = nullptr;
  TreeNode *leftChild = nullptr;
  TreeNode *rightChild = nullptr;
  if(!tknzr->hasToken()){
    throw ((std::string) "invalid input");
  }
  Token token = tknzr->getToken();
  if (token.type != Or) {
    treeNode = parseConjTerm();
  }
  if(!tknzr->hasToken()){
    return treeNode;
  }
  token = tknzr->getToken();
  while (token.type == Or) {
    leftChild = treeNode;
    treeNode = new OperatorNode(token.content);
    tknzr->advanceToken();
    rightChild = parseConjTerm();
    treeNode->updateChildren(leftChild, rightChild);
    if(!tknzr->hasToken()){
      break;
    }
    token = tknzr->getToken();
  }
  return treeNode;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  TreeNode *treeRoot = parseFormula();
  if(tknzr->hasToken()) {
    throw ((std::string) "invalid input");
  }
  return treeRoot;
}

FormulaParser::~FormulaParser() {
  // your code starts here
  delete this->tknzr;
  this->tknzr = nullptr;
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;
  // your code starts here
  Token token;
  std::string tempVarName;
  bool tempConstant;
  bool hasVarName = false;
  int count = 1;
  while (tknzr->hasToken()) {
    switch (count) {
      case 1:
        hasVarName = false;
        token = tknzr->getToken();
        tknzr->advanceToken();
        if (token.type != VarName) {
          throw ((std::string) "invalid input");
        }
        if (results.count(token.content) == 0) {
          tempVarName = token.content;
        } else {
          hasVarName = true;
          tempConstant = results[token.content];
        }
        count++;
        break;
      case 2:
        token = tknzr->getToken();
        tknzr->advanceToken();
        if (token.type != Colon) {
          throw ((std::string) "invalid input");
        }
        count++;
        break;
      case 3:
        token = tknzr->getToken();
        tknzr->advanceToken();
        if (token.type != Constant) {
          throw ((std::string) "invalid input");
        }
        if (hasVarName) {
          if ((tempConstant && token.content == "0") || (!tempConstant && token.content == "1")) {
            throw ((std::string) "contradicting assignment");
          }
        } else {
          if (token.content == "1") {
            results.insert({tempVarName, true});
          } else {
            results.insert({tempVarName, false});
          }
        }
        count++;
        break;
      case 4:
        token = tknzr->getToken();
        tknzr->advanceToken();
        if (token.type != Comma) {
          throw ((std::string) "invalid input");
        }
        count = 1;
        break;
    }
  }
  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
  delete this->tknzr;
  this->tknzr = nullptr;
}
