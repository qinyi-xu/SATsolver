//
// Created by xqy on 2022/12/13.
//

#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <string>
#include "tokenizer.h"

class TreeNode;

class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer *tknzr;

    TreeNode *parseFormula(); // parse non-terminal Formula in the grammar
    TreeNode *parseConjTerm(); // parse non-terminal ConjTerm in the grammar
    TreeNode *parseTerm(); // parse non-terminal Term in the grammar
public:
    FormulaParser(std::string ln);

    TreeNode *getTreeRoot(); // parse the Boolean formula and return the root node of the formula syntax tree
    ~FormulaParser();
};

#endif
