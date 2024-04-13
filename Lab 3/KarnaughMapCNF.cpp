#include "KarnaughMapCNF.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include"ReducedFormsBuilder.h"
std::string KarnaughMapCNF::grayCodeToString(int code, int length) {
    std::string binary = std::bitset<32>(code).to_string();
    return binary.substr(32 - length);
}
KarnaughMapCNF::KarnaughMapCNF(const std::vector<std::map<char, bool>>& combinations, const std::vector<bool>& results)
    : combinations(combinations), results(results) {
    if (!combinations.empty()) {
        variablesCount = combinations.front().size();
    }
    initializeMap(variablesCount);
}

void KarnaughMapCNF::initializeMap(int varCount) {
    if (varCount == 3) {
        map.resize(2, std::vector<bool>(4, false));
    }
    else {
        int size = std::pow(2, std::ceil(varCount / 2.0));
        map.resize(size, std::vector<bool>(size, false));
    }
}

std::vector<int> KarnaughMapCNF::generateGrayCode(int bits) {
    std::vector<int> grayCodes;
    for (int i = 0; i < (1 << bits); i++) {
        grayCodes.push_back(i ^ (i >> 1));
    }
    return grayCodes;
}

int KarnaughMapCNF::grayCodeToBinary(int gray) {
    int binary = 0;
    for (; gray; gray >>= 1) {
        binary ^= gray;
    }
    return binary;
}

int KarnaughMapCNF::grayCodeToIndex(int gray, const std::vector<int>& grayCodes) {
    auto it = std::find(grayCodes.begin(), grayCodes.end(), gray);
    if (it != grayCodes.end()) {
        return std::distance(grayCodes.begin(), it);
    }
    return -1;
}

void KarnaughMapCNF::generateMap() {
    fillMap();
}

void KarnaughMapCNF::fillMap() {
    auto rowGrayCodes = generateGrayCode(variablesCount == 3 ? 1 : std::ceil(variablesCount / 2.0));
    auto colGrayCodes = generateGrayCode(variablesCount == 3 ? 2 : std::floor(variablesCount / 2.0));

    for (size_t i = 0; i < combinations.size(); ++i) {
        int row = 0, col = 0;
        int bitIndex = 0;
        if (variablesCount == 3) {
            for (const auto& var : combinations[i]) {
                if (bitIndex == 0) {
                    row = var.second;
                }
                else {
                    col = (col << 1) | var.second;
                }
                ++bitIndex;
            }
            map[row][grayCodeToIndex(col, colGrayCodes)] = results[i];
        }
        else {
            for (const auto& var : combinations[i]) {
                if (bitIndex < std::ceil(variablesCount / 2.0)) row = (row << 1) | var.second;
                else col = (col << 1) | var.second;
                ++bitIndex;
            }
            map[grayCodeToIndex(row, rowGrayCodes)][grayCodeToIndex(col, colGrayCodes)] = results[i];
        }
    }
}

void KarnaughMapCNF::printMap() {
    auto colBits = variablesCount == 3 ? 2 : std::floor(variablesCount / 2.0);
    auto rowBits = variablesCount == 3 ? 1 : std::ceil(variablesCount / 2.0);

    auto colGrayCodes = generateGrayCode(colBits);
    auto rowGrayCodes = generateGrayCode(rowBits);

    std::cout << "    ";
    for (int colCode : colGrayCodes) {
        std::cout << grayCodeToString(colCode, colBits) << " ";
    }
    std::cout << "\n  ";
    for (size_t i = 0; i < colGrayCodes.size(); ++i) {
        std::cout << "---";
    }
    std::cout << "\n";
    for (int i = 0; i < rowGrayCodes.size(); ++i) {
        std::cout << grayCodeToString(rowGrayCodes[i], rowBits) << " | ";
        for (int j = 0; j < colGrayCodes.size(); ++j) {
            std::cout << map[i][j] << " ";
        }
        std::cout << "\n";
    }
}
void KarnaughMapCNF::findAllRegions() {
    findRegions1x1();
    findRegions1x2();
    findRegions2x1();
    findRegions2x2();
    findRegions1x4();
    findRegions4x1();
    findRegions2x4();
    findRegions4x2();
    filterAndPrintUniqueRegions();
    markUnincluded1x1Regions();
}

void KarnaughMapCNF::addRegion(std::set<std::pair<int, int>> region) {
    uniqueRegions.insert(region);
}

void KarnaughMapCNF::filterAndPrintUniqueRegions() {
    for (const auto& region : uniqueRegions) {
        printRegion(region);
    }
}
void KarnaughMapCNF::findRegions1x1() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (!map[i][j]) {
                std::set<std::pair<int, int>> region = { {i, j} };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions1x2() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            int nextColIndex = (j + 1) % map[0].size();
            if (!map[i][j] && !map[i][nextColIndex]) {
                std::set<std::pair<int, int>> region = { {i, j}, {i, nextColIndex} };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions2x1() {
    for (int i = 0; i < map.size(); ++i) {
        int nextRowIndex = (i + 1) % map.size();
        for (int j = 0; j < map[0].size(); ++j) {
            if (!map[i][j] && !map[nextRowIndex][j]) {
                std::set<std::pair<int, int>> region = { {i, j}, {nextRowIndex, j} };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions2x2() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (!map[i][j] &&
                !map[(i + 1) % map.size()][j] &&
                !map[i][(j + 1) % map[0].size()] &&
                !map[(i + 1) % map.size()][(j + 1) % map[0].size()]) {
                std::set<std::pair<int, int>> region = {
                    {i, j},
                    {(i + 1) % map.size(), j},
                    {i, (j + 1) % map[0].size()},
                    {(i + 1) % map.size(), (j + 1) % map[0].size()}
                };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions1x4() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (!map[i][j] &&
                !map[i][(j + 1) % map[0].size()] &&
                !map[i][(j + 2) % map[0].size()] &&
                !map[i][(j + 3) % map[0].size()]) {
                std::set<std::pair<int, int>> region = {
                    {i, j},
                    {i, (j + 1) % map[0].size()},
                    {i, (j + 2) % map[0].size()},
                    {i, (j + 3) % map[0].size()}
                };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions4x1() {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (!map[i][j] &&
                !map[(i + 1) % map.size()][j] &&
                !map[(i + 2) % map.size()][j] &&
                !map[(i + 3) % map.size()][j]) {
                std::set<std::pair<int, int>> region = {
                    {i, j},
                    {(i + 1) % map.size(), j},
                    {(i + 2) % map.size(), j},
                    {(i + 3) % map.size(), j}
                };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions2x4() {
    for (int i = 0; i < map.size(); ++i) {
        int nextRowIndex = (i + 1) % map.size();
        for (int j = 0; j < map[0].size(); ++j) {
            int nextColIndex = (j + 1) % map[0].size();
            int nextNextColIndex = (j + 2) % map[0].size();
            int nextNextNextColIndex = (j + 3) % map[0].size();
            if (!map[i][j] && !map[nextRowIndex][j] &&
                !map[i][nextColIndex] && !map[nextRowIndex][nextColIndex] &&
                !map[i][nextNextColIndex] && !map[nextRowIndex][nextNextColIndex] &&
                !map[i][nextNextNextColIndex] && !map[nextRowIndex][nextNextNextColIndex]) {
                std::set<std::pair<int, int>> region = {
                    {i, j}, {nextRowIndex, j},
                    {i, nextColIndex}, {nextRowIndex, nextColIndex},
                    {i, nextNextColIndex}, {nextRowIndex, nextNextColIndex},
                    {i, nextNextNextColIndex}, {nextRowIndex, nextNextNextColIndex}
                };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::findRegions4x2() {
    for (int i = 0; i < map.size(); ++i) {
        int nextRowIndex = (i + 1) % map.size();
        int nextNextRowIndex = (i + 2) % map.size();
        int nextNextNextRowIndex = (i + 3) % map.size();
        for (int j = 0; j < map[0].size(); ++j) {
            int nextColIndex = (j + 1) % map[0].size();
            if (!map[i][j] && !map[nextRowIndex][j] && 
                !map[nextNextRowIndex][j] && !map[nextNextNextRowIndex][j] &&
                !map[i][nextColIndex] && !map[nextRowIndex][nextColIndex] && 
                !map[nextNextRowIndex][nextColIndex] && !map[nextNextNextRowIndex][nextColIndex]) {
                std::set<std::pair<int, int>> region = {
                    {i, j}, {nextRowIndex, j}, {nextNextRowIndex, j}, {nextNextNextRowIndex, j},
                    {i, nextColIndex}, {nextRowIndex, nextColIndex}, {nextNextRowIndex, nextColIndex}, {nextNextNextRowIndex, nextColIndex}
                };
                addRegion(region);
            }
        }
    }
}

void KarnaughMapCNF::printRegion(const std::set<std::pair<int, int>>& region) {
    setlocale(LC_ALL, "Ru");
    if (region.empty()) return;
    std::cout << region.size() << " клеток. Координаты региона (";
    for (auto it = region.begin(); it != region.end(); ++it) {
        if (it != region.begin()) std::cout << ", ";
        std::cout << "(" << it->first << "," << it->second << ")";
    }
    std::cout << ")" << std::endl;
}
void KarnaughMapCNF::findAndSaveMaxRegions() {
    if (uniqueRegions.empty()) return;
    size_t maxSize = 0;
    for (const auto& region : uniqueRegions) {
        maxSize = std::max(maxSize, region.size());
    }
    maxRegions.clear();
    for (const auto& region : uniqueRegions) {
        if (region.size() == maxSize) {
            maxRegions.push_back(region);
        }
    }
}

void KarnaughMapCNF::printMaxRegions() {
    setlocale(LC_ALL, "RU");
    std::cout << "Координаты максимальных регионов: " << std::endl;
    for (const auto& region : maxRegions) {
        printRegion(region);
    }
}

void KarnaughMapCNF::markUnincluded1x1Regions() {
    unincludedRegions.clear();
    for (const auto& region : uniqueRegions) {
        if (region.size() == 1) { 
            const std::pair<int, int>& coord = *region.begin();
            bool isIncluded = false;
            for (const auto& maxRegion : maxRegions) {
                if (maxRegion.find(coord) != maxRegion.end()) {
                    isIncluded = true;
                    break;
                }
            }
            if (!isIncluded) {
                unincludedRegions.push_back(region);
            }
        }
    }
}

void KarnaughMapCNF::findMaxRegionsContainingSingleCells() {
    for (const auto& cellRegion : unincludedRegions) {
        const auto& cell = *cellRegion.begin();
        std::set<std::pair<int, int>> maxRegion;
        int maxSize = 0;
        for (const auto& region : uniqueRegions) {
            if (region.find(cell) != region.end() && region.size() > maxSize) {
                maxRegion = region;
                maxSize = region.size();
            }
        }
        if (maxSize > 0 && std::find(substringRegion.begin(), substringRegion.end(), maxRegion) == substringRegion.end()) {
            substringRegion.push_back(maxRegion);
        }
    }
}



void KarnaughMapCNF::analyzeChanges(const std::vector<bool>& changes, int varCount, bool isRow, std::vector<bool>& varChange) {
    int limit = isRow ? ((varCount + 1) / 2) : (varCount / 2);
    for (int i = 0; i < limit; ++i) {
        bool constant = true;
        for (int j = 0; j < changes.size(); ++j) {
            if (changes[j] && ((j >> i) & 1) == 0) {
                constant = false;
                break;
            }
        }
        varChange[isRow ? i : i + limit] = constant;
    }
}

bool KarnaughMapCNF::determineState(const std::pair<int, int>& cell, int varIndex, int varCount) {
    int numRows = 1 << (varCount / 2);
    int numCols = 1 << (varCount - varCount / 2);

    auto rowGrayCodes = generateGrayCode(numRows);
    auto colGrayCodes = generateGrayCode(numCols);

    bool currentState;

    if (varIndex < varCount / 2) {
        int grayCode = rowGrayCodes[cell.first];
        currentState = (grayCode & (1 << (varCount / 2 - 1 - varIndex))) != 0;
    }
    else {
        int grayCode = colGrayCodes[cell.second];
        currentState = (grayCode & (1 << (varCount - 1 - varIndex))) != 0;
    }

    return currentState;
}

std::vector<std::string> KarnaughMapCNF::regionToExpression(const std::set<std::pair<int, int>>& region, int varCount) {
    if (region.empty()) return {};

    std::vector<std::string> expressions;
    std::string expr;
    for (int var = 0; var < varCount; ++var) {
        bool hasTrue = false;
        bool hasFalse = false;

        for (const auto& cell : region) {
            bool state = determineState(cell, var, varCount);
            hasTrue |= !state;
            hasFalse |= state;
        }

        if (hasTrue && hasFalse) continue;
        if (hasFalse) expr += '!';
        expr += variables[var];
    }

    if (!expr.empty()) {
        expressions.push_back(expr);
    }

    return expressions;
}


void KarnaughMapCNF::convertMaxRegionsToExpressions() {
    markUnincluded1x1Regions();
    findMaxRegionsContainingSingleCells();
    setlocale(LC_ALL, "RU");

    std::vector<std::string> allExpressions;
    auto addExpressions = [&allExpressions](const std::vector<std::string>& expressions) {
        allExpressions.insert(allExpressions.end(), expressions.begin(), expressions.end());
        };

    for (const auto& region : maxRegions) {
        std::vector<std::string> expressions = regionToExpression(region, variablesCount);
        addExpressions(expressions);
    }

    for (const auto& region : substringRegion) {
        std::vector<std::string> expressions = regionToExpression(region, variablesCount);
        addExpressions(expressions);
    }

    ReducedFormsBuilder builder;
    std::string finalString = builder.vectorToStringCNF(allExpressions);
    std::cout << "Результат:" << std::endl;
    std::cout << finalString << std::endl;
}
