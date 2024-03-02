#pragma once
#include <string>
#include <vector>
#include <map>
#include "BooleanExpression.h"
#include "PostfixEvaluator.h"

class TruthTableGenerator {
public:
    TruthTableGenerator() = default;
    void generateTruthTable(const std::string& expression);
    std::vector<std::map<char, bool>> getCombinations() const;
    std::vector<bool> getResults() const;

private:
    std::vector<std::map<char, bool>> combinations;
    std::vector<bool> results;
    void printHeader(const std::vector<char>& variables);
    void printRow(const std::map<char, bool>& combination, bool result);
};
