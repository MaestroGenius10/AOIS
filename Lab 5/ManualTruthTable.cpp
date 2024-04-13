#include "ManualTruthTable.h"
#include <iostream>

void ManualTruthTable::manualInput(const std::vector<std::string>& inputData, const std::vector<std::string>& names) {
    variableNames = names;
    combinations.clear();
    results.clear();

    for (const auto& name : names) {
        results[name] = std::vector<bool>();
    }

    for (const auto& data : inputData) {
        std::map<std::string, bool> combination;
        for (size_t i = 0; i < names.size(); ++i) {
            combination[names[i]] = data[i] == '1';
            results[names[i]].push_back(data[i] == '1'); 
        }
        combinations.push_back(combination);
    }

    printHeader();
    for (size_t i = 0; i < combinations.size(); ++i) {
        printRow(i);
    }
}

void ManualTruthTable::printHeader() const {
    for (const auto& name : variableNames) {
        std::cout << name << "\t";
    }
    std::cout << std::endl;
}

void ManualTruthTable::printRow(size_t index) const {
    if (index < combinations.size()) {
        for (const auto& name : variableNames) {
            std::cout << combinations[index].at(name) << "\t";
        }
        std::cout << std::endl;
    }
}

std::vector<std::map<std::string, bool>> ManualTruthTable::getCombinations() const {
    return combinations;
}

std::vector<bool> ManualTruthTable::getResultsForVariable(const std::string& variableName) const {
    auto it = results.find(variableName);
    if (it != results.end()) {
        return it->second;
    }
}
