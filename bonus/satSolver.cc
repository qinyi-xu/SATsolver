#include "satSolver.h"

bool satCallingDPLL(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::map<int, bool> assignMap;
  return DPLL(numVar, cnf, assignMap);
}

bool DPLL(unsigned int numVar, const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap) {
  std::vector<std::vector<int>> modifiedCnf = BCP(cnf, assignMap);
  if (modifiedCnf.empty()) {
    return true;
  } else if (fomularIsFalse(modifiedCnf)) {
    return false;
  }
  modifiedCnf = PLP(numVar, modifiedCnf, assignMap);
  if (modifiedCnf.empty()) {
    return true;
  } else if (fomularIsFalse(modifiedCnf)) {
    return false;
  }
  int p = chooseVar(numVar, assignMap);
  if (p == 0) {
    return false;
  }
  std::map<int, bool> assignMapPTrue = assignMap;
  assignMapPTrue.insert({p, true});
  std::map<int, bool> assignMapPFalse = assignMap;
  assignMapPFalse.insert({p, false});
  if (DPLL(numVar, modifiedCnf, assignMapPTrue)) {
    return true;
  } else {
    return DPLL(numVar, modifiedCnf, assignMapPFalse);
  }
}

std::vector<std::vector<int>> BCP(const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap) {
  if (assignMap.empty()) {
    return cnf;
  }
  std::vector<std::vector<int>> modifiedCnf = cnf;
  std::map<int, bool>::reverse_iterator mapIter;
  std::list<int>::iterator orderIter;
  std::list<int> assignMapOrder;
  for (mapIter = assignMap.rbegin(); mapIter != assignMap.rend(); ++mapIter) {
    assignMapOrder.push_back(mapIter->first);
  }
  for (orderIter = assignMapOrder.begin(); orderIter != assignMapOrder.end(); ++orderIter) {
    for (int i = 0; i < modifiedCnf.size(); i++) {
      for (int j = 0; j < modifiedCnf[i].size(); j++) {
        if ((*orderIter == modifiedCnf[i][j] && assignMap[*orderIter]) ||
            (*orderIter == 0 - modifiedCnf[i][j] && !assignMap[*orderIter])) {
          modifiedCnf.erase(modifiedCnf.begin() + i);
          i--;
          break;
        } else if ((*orderIter == modifiedCnf[i][j] && !assignMap[*orderIter]) ||
                   (*orderIter == 0 - modifiedCnf[i][j] && assignMap[*orderIter])) {
          if (modifiedCnf[i].size() == 1) {
            modifiedCnf[i][j] = 0;
          } else {
            modifiedCnf[i].erase(modifiedCnf[i].begin() + j);
            j--;
          }
        }
        if (modifiedCnf[i].size() == 1 && modifiedCnf[i][0] != 0) {
          if (assignMap.count(modifiedCnf[i][0]) == 1) {
            if (!assignMap[modifiedCnf[i][0]]) {
              modifiedCnf[i][0] = 0;
            } else {
              modifiedCnf.erase(modifiedCnf.begin() + i);
              i--;
              break;
            }
          } else if (assignMap.count(0 - modifiedCnf[i][0]) == 1) {
            if (assignMap[0 - modifiedCnf[i][0]]) {
              modifiedCnf[i][0] = 0;
            } else {
              modifiedCnf.erase(modifiedCnf.begin() + i);
              i--;
              break;
            }
          } else {
            if (modifiedCnf[i][0] > 0) {
              assignMap.insert({modifiedCnf[i][0], true});
              assignMapOrder.push_back(modifiedCnf[i][0]);
            } else {
              assignMap.insert({0 - modifiedCnf[i][0], false});
              assignMapOrder.push_back(0 - modifiedCnf[i][0]);
            }
            modifiedCnf.erase(modifiedCnf.begin() + i);
            i--;
            break;
          }
        }
      }
    }
  }
  return modifiedCnf;
}

std::vector<std::vector<int>> PLP(unsigned int numVar, const std::vector<std::vector<int>> &cnf, std::map<int, bool> &assignMap) {
  std::vector<std::vector<int>> modifiedCnf = cnf;
  std::list<int> list;
  std::list<int> reverseList;
  int pureLiteralCount[numVar + 1];
  memset(pureLiteralCount, 0, sizeof(pureLiteralCount));
  for (int i = 0; i < modifiedCnf.size(); i++) {
    for (int j = 0; j < modifiedCnf[i].size(); j++) {
      if (modifiedCnf[i][j] > 0 && pureLiteralCount[modifiedCnf[i][j]] >= 0) {
        pureLiteralCount[modifiedCnf[i][j]]++;
      } else if (modifiedCnf[i][j] < 0 && pureLiteralCount[0 - modifiedCnf[i][j]] <= 0) {
        pureLiteralCount[0 - modifiedCnf[i][j]]--;
      } else {
        reverseList.push_back(abs(modifiedCnf[i][j]));
      }
    }
  }

  for (int i = 1; i <= numVar; i++) {
    if (std::find(reverseList.begin(), reverseList.end(), i) == reverseList.end() && pureLiteralCount[i] > 0) {
      list.push_back(i);
      assignMap.insert({i, true});
    } else if (std::find(reverseList.begin(), reverseList.end(), i) == reverseList.end() && pureLiteralCount[i] < 0) {
      list.push_back(0 - i);
      assignMap.insert({0 - i, false});
    }
  }

  std::list<int>::iterator iter;
  for (iter = list.begin(); iter != list.end(); ++iter) {
    for (int i = 0; i < modifiedCnf.size(); i++) {
      for (int j = 0; j < modifiedCnf[i].size(); j++) {
        if (*iter == modifiedCnf[i][j]) {
          modifiedCnf.erase(modifiedCnf.begin() + i);
          i--;
          break;
        }
      }
    }
  }

  return modifiedCnf;
}

bool fomularIsFalse(const std::vector<std::vector<int>> &modifiedCnf) {
  for (int i = 0; i < modifiedCnf.size(); i++) {
    if (modifiedCnf[i].size() == 1 && modifiedCnf[i][0] == 0) {
      return true;
    }
  }
  return false;
}

int chooseVar(unsigned int numVar, const std::map<int, bool> &assignMap) {
  for (int i = 1; i <= numVar; i++) {
    if (assignMap.count(i) == 0) {
      return i;
    }
  }
  return 0;
}