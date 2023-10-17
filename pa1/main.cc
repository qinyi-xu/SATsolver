#include <iostream>
#include <map>
#include <regex>
#include "parser.h"
#include "treeNode.h"

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
  // varName has spaces
  if (std::regex_match(line, std::regex(".*[a-zA-Z]+\\s+[a-zA-Z0-9]+.*"))) {
    throw ((std::string) "invalid input");
  }

  // varName starts with digit
  if (std::regex_match(line, std::regex(".*[0-9]+\\s*[a-zA-Z0-9]+.*"))) {
    throw ((std::string) "invalid input");
  }

  int pos = line.find(';');
  if (pos == -1) {
    throw ((std::string) "invalid input");
  }
  int size = line.size();
  formulaStr = line.substr(0, pos);
  assignmentStr = line.substr(pos + 1, size);

  if (formulaStr.empty()) {
    throw ((std::string) "invalid input");
  }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    if (!std::getline(std::cin, line)) {
      break;
    }
    try {
      parseLine(line, formulaStr, assignmentStr);
      FormulaParser formulaParser(formulaStr);
      AssignmentParser assignmentParser(assignmentStr);
      std::map<std::string, bool> assignments = assignmentParser.parseAssignment();
      TreeNode *treeRoot = formulaParser.getTreeRoot();
      std::cout << int(treeRoot->evaluate(assignments)) << std::endl;
    }
    catch (std::string e) {
      std::cout << "Error: " << e << std::endl;
    }
  }
}
