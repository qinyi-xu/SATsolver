#ifndef SAT_H
#define SAT_H

#include <vector>
#include <map>
#include <list>
#include <cstring>
#include <algorithm>

// return the SAT result of cnf by calling DPLL
bool satCallingDPLL(unsigned int numVar, std::vector<std::vector<int>> &cnf);

bool DPLL(unsigned int numVar, const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap);
std::vector<std::vector<int>> BCP(const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap);
std::vector<std::vector<int>> PLP(unsigned int numVar, const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap);
bool fomularIsFalse(const std::vector<std::vector<int>> &modifiedCnf);
int chooseVar(unsigned int numVar, const std::map<int, bool> &assignMap);

#endif
