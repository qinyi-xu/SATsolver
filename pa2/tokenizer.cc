#include "tokenizer.h"
#include "constant.h"
#include <regex>

Tokenizer::Tokenizer(std::string ln) {
  // complete the constructor
  tokensIndex = 0;

  int index = 0;
  if (!ln.empty()) {
    //string::npos means no match is found
    while ((index = ln.find(' ', index)) != std::string::npos) {
      ln.erase(index, 1);
    }
  }

  index = 0;
  std::string temp = "";
  while (index < ln.size()) {
    if (ln[index] == '+') {
      Token newToken;
      newToken.content = std::string(1, ln[index]);
      newToken.type = Or;
      tokens.emplace_back(newToken);
      index++;
    } else if (ln[index] == '*') {
      Token newToken;
      newToken.content = std::string(1, ln[index]);
      newToken.type = And;
      tokens.emplace_back(newToken);
      index++;
    } else if (ln[index] == '-') {
      Token newToken;
      newToken.content = std::string(1, ln[index]);
      newToken.type = Not;
      tokens.emplace_back(newToken);
      index++;
    } else if (ln[index] == '(') {
      Token newToken;
      newToken.content = std::string(1, ln[index]);
      newToken.type = LeftBracket;
      tokens.emplace_back(newToken);
      index++;
    } else if (ln[index] == ')') {
      Token newToken;
      newToken.content = std::string(1, ln[index]);
      newToken.type = RightBracket;
      tokens.emplace_back(newToken);
      index++;
    } else if (std::regex_match(std::string(1, ln[index]), std::regex("[a-zA-Z]"))) {
      temp = temp + ln[index];
      index++;
      while (std::regex_match(std::string(1, ln[index]), std::regex("[a-zA-Z0-9]"))) {
        temp = temp + ln[index];
        index++;
      }
      if (temp.size() > 10) {
        throw ((std::string) "invalid input");
      } else {
        Token newToken;
        newToken.content = temp;
        newToken.type = VarName;
        tokens.emplace_back(newToken);
        temp = "";
      }
    } else {
      throw ((std::string) "invalid input");
    }
  }
}

bool Tokenizer::advanceToken() {
  // your code starts here
  tokensIndex++;
  return false;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  if (tokensIndex < tokens.size()) {
    return true;
  }
  return false;
}

// only can be called when hasToken() is true
Token Tokenizer::getToken() {
  Token resultToken;
  // your code starts there
  resultToken = tokens[tokensIndex];
  return resultToken;
}
