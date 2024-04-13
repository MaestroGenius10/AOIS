#include "TruthTableGenerator.h"
#include "InfixToPostfixConverter.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <set>

void TruthTableGenerator::generateTruthTable(const std::string& expression) {
    InfixToPostfixConverter converter;
    auto postfix = converter.infixToPostfix(expression);

    std::set<char> variableSet;
    for (const auto& token : postfix) {
        if (std::isalpha(token[0])) {
            variableSet.insert(token[0]);
        }
    }

    std::vector<char> variables(variableSet.begin(), variableSet.end());
    std::sort(variables.begin(), variables.end());
    int numRows = pow(2, variables.size());

    printHeader(variables);

    for (int i = 0; i < numRows; ++i) {
        std::map<char, bool> variableMap;
        for (size_t j = 0; j < variables.size(); ++j) {
            variableMap[variables[j]] = (i >> (variables.size() - j - 1)) & 1;
        }

        PostfixEvaluator evaluator;
        bool result = evaluator.evaluate(postfix, variableMap);

        combinations.push_back(variableMap);
        results.push_back(result);
        printRow(variableMap, result);
    }
}

std::vector<std::map<char, bool>> TruthTableGenerator::getCombinations() const {
    return combinations;
}

std::vector<bool> TruthTableGenerator::getResults() const {
    return results;
}

void TruthTableGenerator::printHeader(const std::vector<char>& variables) {
    for (auto var : variables) {
        std::cout << var << "\t";
    }
    std::cout << "Result" << std::endl;
}

void TruthTableGenerator::printRow(const std::map<char, bool>& combination, bool result) {
    for (const auto& pair : combination) {
        std::cout << pair.second << "\t";
    }
    std::cout << result << std::endl;
}

