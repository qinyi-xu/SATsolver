#include "tseitinTransformer.h"
#include "satSolver.h"
#include "formulaParser.h"
#include <iostream>

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line
    // your code starts here
    if (!std::getline(std::cin, line)) {
      break;
    }
    try {
      FormulaParser formulaParser(line);
      TseitinTransformer tseitinTransformer(formulaParser.getTreeRoot());
      std::vector<std::vector<int>> cnf = tseitinTransformer.transform();
      if(satCallingMiniSat(tseitinTransformer.getVarNum(), cnf)) {
        std::cout << "sat" << std::endl;
      } else {
        std::cout << "unsat" << std::endl;
      }
    }
    catch (std::string e) {
      std::cout << "Error: " << e << std::endl;
    }
  }
}
