#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  std::vector<Minisat::Lit> literals;
  for (int i = 0; i < numVar; i++) {
    literals.push_back(Minisat::mkLit(solver->newVar()));
  }
  Minisat::vec<Minisat::Lit> clause;
  for (int i = 0; i < cnf.size(); i++) {
    for (int j = 0; j < cnf[i].size(); j++) {
      if (cnf[i][j] > 0) {
        clause.push(literals[cnf[i][j] - 1]);
      } else {
        clause.push(~literals[0 - cnf[i][j] - 1]);
      }
    }
    solver->addClause(clause);
    clause.clear();
  }
  return solver->solve();
}
