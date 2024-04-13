#include"ReducedFormsBuilder.h"
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<iomanip>
std::vector<std::string> ReducedFormsBuilder::splitExpression(std::string& expression) {
    std::vector<std::string> splitString;
    std::istringstream iss(expression);
    std::string segment;

    while (std::getline(iss, segment, '(')) {
        size_t pos = segment.find(')');
        if (pos != std::string::npos) {
            std::string content = segment.substr(0, pos);
            content.erase(std::remove(content.begin(), content.end(), '&'), content.end());
            content.erase(std::remove(content.begin(), content.end(), '+'), content.end());
            content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());

            if (!content.empty()) {
                splitString.push_back(content);
            }
            iss.seekg(pos - segment.length() + 1, iss.cur);
        }
    }

    return splitString;
}


std::vector<std::string> ReducedFormsBuilder::findUniqueVariables(std::vector<std::string>& expressions) {
    std::set<std::string> uniqueVars;

    for (const auto& expr : expressions) {
        for (char ch : expr) {
            if (std::isalpha(ch)) {
                uniqueVars.insert(std::string(1, ch));
            }
        }
    }
    std::vector<std::string> result(uniqueVars.begin(), uniqueVars.end());
    return result;
}

int ReducedFormsBuilder::countUniqueVariables(std::vector<std::string>& expressions) {
    std::set<char> uniqueVars;
    for (const auto& expr : expressions) {
        for (char ch : expr) {
            if (std::isalpha(ch)) {
                uniqueVars.insert(ch);
            }
        }
    }
    return uniqueVars.size();
}

std::vector<std::string> ReducedFormsBuilder::convertLogicToNumeric
(std::vector<std::string>& logicStrings, std::vector<std::string>& uniqueVars) {
    std::vector<std::string> numericStrings;
    for (const auto& logicStr : logicStrings) {
        std::string numericStr = "";
        for (const auto& var : uniqueVars) {
            if (logicStr.find("!" + var) != std::string::npos) {
                numericStr += "0"; 
            }
            else if (logicStr.find(var) != std::string::npos) {
                numericStr += "1";
            }
            else {
                numericStr += "2"; 
            }
        }
        numericStrings.push_back(numericStr);
    }
    return numericStrings;
}

bool ReducedFormsBuilder::canMerge(std::string& a, std::string& b, int N) {
    int diffCount = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] != b[i]) diffCount++;
    }
    return diffCount == 1;
}

std::string ReducedFormsBuilder::mergeStrings(std::string& a, std::string& b, int N) {
    std::string result = a;
    for (int i = 0; i < N; ++i) {
        if (a[i] != b[i]) result[i] = '2';
    }
    return result;
}

std::vector<std::string> ReducedFormsBuilder::findMerges(std::vector<std::string>& strings, int N) {
    std::map<std::string, int> mergeCount;
    std::unordered_set<int> usedIndices;

    for (int i = 0; i < strings.size(); ++i) {
        for (int j = i + 1; j < strings.size(); ++j) {
            if (canMerge(strings[i], strings[j], N)) {
                std::string merged = mergeStrings(strings[i], strings[j], N);
                mergeCount[merged]++;
                usedIndices.insert(i);
                usedIndices.insert(j);
            }
        }
    }

    std::vector<std::string> result;
    for (const auto& pair : mergeCount) {
        for (int i = 0; i < 1; ++i) { 
            result.push_back(pair.first);
        }
    }

    for (int i = 0; i < strings.size(); ++i) {
        if (usedIndices.find(i) == usedIndices.end()) {
            result.push_back(strings[i]);
        }
    }

    return result;
}

std::vector<std::string> ReducedFormsBuilder::numericStringsToVariables
(std::vector<std::string>& numericStrings, std::vector<std::string>& uniqueVariables) {
    std::vector<std::string> variableStrings;
    for (const auto& numString : numericStrings) {
        std::string varString;
        for (size_t i = 0; i < numString.length(); ++i) {
            if (numString[i] == '2') continue;

            if (numString[i] == '1') {
                varString += uniqueVariables[i];
            }
            else if (numString[i] == '0') {
                varString += "!" + uniqueVariables[i];
            }
        }
        variableStrings.push_back(varString);
    }

    return variableStrings;
}

bool ReducedFormsBuilder::isContained(std::string& candidate, std::string& target) {
    if (candidate.empty()) return false;

    for (size_t i = 0; i < candidate.size(); ++i) {
        if (candidate[i] == '!') {
            if (i + 1 < candidate.size() && target.find(candidate.substr(i, 2)) == std::string::npos) {
                return false; 
            }
            ++i;
        }
        else if (target.find(candidate[i]) == std::string::npos || target.find('!' + std::string(1, candidate[i])) != std::string::npos) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<bool>> ReducedFormsBuilder::buildCoverageMatrix
(std::vector<std::string>& before, std::vector<std::string>& after) {
    std::vector<std::vector<bool>> coverageMatrix(after.size(), std::vector<bool>(before.size(), false));

    for (size_t i = 0; i < after.size(); ++i) {
        for (size_t j = 0; j < before.size(); ++j) {
            if (isContained(after[i], before[j])) {
                coverageMatrix[i][j] = true;
            }
        }
    }

    return coverageMatrix;
}

void ReducedFormsBuilder::displayTable
(std::vector<std::string>& before, std::vector<std::string>& after, std::vector<std::vector<bool>>& coverageMatrix) {
    int columnWidth = 10;
    std::cout << std::setw(columnWidth) << " ";
    for (const auto& b : before) {
        std::cout << std::setw(columnWidth) << b;
    }
    std::cout << "\n";

    for (size_t i = 0; i < after.size(); ++i) {
        std::cout << std::setw(columnWidth) << after[i];
        for (size_t j = 0; j < before.size(); ++j) {
            std::cout << std::setw(columnWidth) << (coverageMatrix[i][j] ? "+" : " ");
        }
        std::cout << "\n";
    }
}

std::vector<std::string> ReducedFormsBuilder::findExtraStrings(
    std::vector<std::string>& rows, std::vector<std::vector<bool>>& coverageMatrix) {

    std::vector<std::string> extraStrings; 
    std::vector<bool> coveredColumns(coverageMatrix[0].size(), false);

    for (size_t rowIndex = 0; rowIndex < rows.size(); ++rowIndex) {
        bool coversNew = false;

        for (size_t colIndex = 0; colIndex < coverageMatrix[rowIndex].size(); ++colIndex) {
            if (coverageMatrix[rowIndex][colIndex] && !coveredColumns[colIndex]) {
                coversNew = true;
                coveredColumns[colIndex] = true;
            }
        }

        if (!coversNew) {
            extraStrings.push_back(rows[rowIndex]);
        }
    }

    return extraStrings;
}

 std::vector<std::string> ReducedFormsBuilder::removeStrings(std::vector<std::string>& input, std::vector<std::string>& toRemove) {
    std::vector<std::string> result = input; 
    for (const auto& rem : toRemove) {
        auto it = std::find(result.begin(), result.end(), rem);
        if (it != result.end()) {
            result.erase(it);
        }
    }
    return result;
}

 std::string ReducedFormsBuilder::vectorToStringDNF(std::vector<std::string>& vec) {
     std::ostringstream result;
     for (size_t i = 0; i < vec.size(); ++i) {
         result << "(";
         for (size_t j = 0; j < vec[i].size(); ++j) {
             char c = vec[i][j];
             if (c == '!') {
                 result << c << vec[i][++j];
             }
             else {
                 result << c;
             }
             if (j < vec[i].size() - 1) {
                 result << " & ";
             }
         }
         result << ")";
         if (i < vec.size() - 1) {
             result << " + ";
         }
     }
     return result.str();
 }

 std::string ReducedFormsBuilder::vectorToStringCNF(std::vector<std::string>& vec) {
     std::ostringstream result;
     for (size_t i = 0; i < vec.size(); ++i) {
         result << "(";
         for (size_t j = 0; j < vec[i].size(); ++j) {
             char c = vec[i][j];
             if (c == '!') {
                 result << c << vec[i][++j];
             }
             else {
                 result << c;
             }
             if (j < vec[i].size() - 1) {
                 result << " + ";
             }
         }
         result << ")";
         if (i < vec.size() - 1) {
             result << " & ";
         }
     }
     return result.str();
 }

void ReducedFormsBuilder::TDNFCalcTable(std::string& input) {
    setlocale(LC_ALL, "ru");
    std::vector<std::string> previousString;
    bool continueMerge = true;
    while (continueMerge) {
        std::vector<std::string> splittedString = splitExpression(input);
        int counter = countUniqueVariables(splittedString);
        std::vector<std::string> variables = findUniqueVariables(splittedString);
        std::vector<std::string> numericString = convertLogicToNumeric(splittedString, variables);
        std::vector<std::string> mergedString = findMerges(numericString, counter);
        std::vector<std::string> charString = numericStringsToVariables(mergedString, variables);
        if (charString == previousString) {
            std::cout << "Данная форма является тупиковой " << std::endl;
            std::string finalizedString = vectorToStringDNF(charString);
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        auto coverageMatrix = buildCoverageMatrix(splittedString, charString);
        std::cout << "Построим и отобразим таблицу для удаления дублирующихся импликант: " << std::endl;
        displayTable(splittedString, charString, coverageMatrix);
        std::cout << "На основе таблицы найдём и исключим лишние импликанты: " << std::endl;
        std::vector <std::string> toRemoveStrings = findExtraStrings(charString, coverageMatrix);
        for (const auto& str : toRemoveStrings) {
            std::cout << str << " ";
        }
        if (toRemoveStrings.empty()) {
            std::cout << "Лишних импликант нет! ";
        }
        std::cout << std::endl;
        std::vector<std::string> removedString = removeStrings(charString, toRemoveStrings);
        std::string finalizedString = vectorToStringDNF(removedString);
        if  (charString == removedString)
        {
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        else {
            input = finalizedString;      
        }
    }
}

void ReducedFormsBuilder::TCNFCalcTable(std::string& input) {
    setlocale(LC_ALL, "ru");
    std::vector<std::string> previousString;
    bool continueMerge = true;
    while (continueMerge) {
        std::vector<std::string> splittedString = splitExpression(input);
        int counter = countUniqueVariables(splittedString);
        std::vector<std::string> variables = findUniqueVariables(splittedString);
        std::vector<std::string> numericString = convertLogicToNumeric(splittedString, variables);
        std::vector<std::string> mergedString = findMerges(numericString, counter);
        std::vector<std::string> charString = numericStringsToVariables(mergedString, variables);
        if (charString == previousString) {
            std::cout << "Данная форма является тупиковой " << std::endl;
            std::string finalizedString = vectorToStringCNF(charString);
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        auto coverageMatrix = buildCoverageMatrix(splittedString, charString);
        std::cout << "Построим и отобразим таблицу для удаления дублирующихся импликант: " << std::endl;
        displayTable(splittedString, charString, coverageMatrix);
        std::cout << "На основе таблицы найдём и исключим лишние импликанты: " << std::endl;
        std::vector <std::string> toRemoveStrings = findExtraStrings(charString, coverageMatrix);
        for (const auto& str : toRemoveStrings) {
            std::cout << str << " ";
        }
        if (toRemoveStrings.empty()) {
            std::cout << "Лишних импликант нет! ";
        }
        std::cout << std::endl;
        std::vector<std::string> removedString = removeStrings(charString, toRemoveStrings);
        std::string finalizedString = vectorToStringCNF(removedString);
        if (charString == removedString)
        {
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        else {
            input = finalizedString;
        }
    }
}


std::vector<std::string> ReducedFormsBuilder::transformExpressionsCNF(const std::vector<std::string>& expressions) {
    std::vector<std::string> transformed;

    for (const auto& expr : expressions) {
        std::string transformedExpr;
        for (size_t i = 0; i < expr.length(); ++i) {
            if (expr[i] == '!') {
                if (i + 1 < expr.length() && isalpha(expr[i + 1])) {
                    transformedExpr += '0';
                    ++i; 
                }
            }
            else if (isalpha(expr[i])) {
                transformedExpr += '1';
            }
        }
        transformed.push_back(transformedExpr);
    }

    return transformed;
}

std::vector<std::string> ReducedFormsBuilder::transformExpressionsDNF(const std::vector<std::string>& expressions) {
    std::vector<std::string> transformed;

    for (const auto& expr : expressions) {
        std::string transformedExpr;
        for (size_t i = 0; i < expr.length(); ++i) {
            if (expr[i] == '!') {
                if (i + 1 < expr.length() && isalpha(expr[i + 1])) {
                    transformedExpr += '1';
                    ++i;
                }
            }
            else if (isalpha(expr[i])) {
                transformedExpr += '0';
            }
        }
        transformed.push_back(transformedExpr);
    }

    return transformed;
}

std::vector<std::string> ReducedFormsBuilder::substituteValuesForAllExpressions
(const std::vector<std::string>& expressions, const std::vector<std::string>& truthValues) {
    std::vector<std::string> results;
    for (size_t truthIndex = 0; truthIndex < truthValues.size(); ++truthIndex) {
        const auto& currentTruthValue = truthValues[truthIndex];
        std::unordered_map<char, char> valueMap;
        for (size_t charIndex = 0, truthCharIndex = 0; charIndex < expressions[truthIndex].length(); ++charIndex, ++truthCharIndex) {
            if (expressions[truthIndex][charIndex] == '!') {
                ++charIndex;
            }
            if (charIndex < expressions[truthIndex].length()) {
                valueMap[expressions[truthIndex][charIndex]] = currentTruthValue[truthCharIndex];
            }
        }

        std::string currentResult;
        for (const auto& expr : expressions) {
            std::string substitutionResult;

            for (size_t i = 0; i < expr.length(); ++i) {
                if (expr[i] == '!') {
                    if (i + 1 < expr.length() && valueMap.find(expr[i + 1]) != valueMap.end()) {
                        substitutionResult += (valueMap[expr[i + 1]] == '1' ? '0' : '1'); 
                        ++i;
                    }
                }
                else if (valueMap.find(expr[i]) != valueMap.end()) {
                    substitutionResult += valueMap[expr[i]];
                }
            }
            if (!currentResult.empty()) {
                currentResult += " ";
            }
            currentResult += substitutionResult;
        }
        results.push_back(currentResult);
    }

    return results;
}

std::vector<std::string> ReducedFormsBuilder::findRedundantStringsDNF
(const std::vector<std::string>& originalStrings, const std::vector<std::string>& truthStrings) {
    std::vector<std::string> redundantStrings;
    bool allAreRedundant = true;

    for (size_t i = 0; i < truthStrings.size(); ++i) {
        std::istringstream iss(truthStrings[i]);
        std::string element;
        std::vector<std::string> elements;

        while (iss >> element) {
            elements.push_back(element);
        }

        if (elements.size() == originalStrings.size()) {
            bool hasZero = false;
            for (const auto& e : elements) {
                if (e.find('0') != std::string::npos) {
                    hasZero = true;
                    break;
                }
            }
            if (!hasZero) {
                redundantStrings.push_back(originalStrings[i]);
            }
            else {
                allAreRedundant = false;
            }
        }
        else {
            allAreRedundant = false;
        }
    }
    if (allAreRedundant) {
        return {};
    }

    return redundantStrings;
}

std::vector<std::string> ReducedFormsBuilder::findRedundantStringsCNF
(const std::vector<std::string>& originalStrings, const std::vector<std::string>& truthStrings) {
    std::vector<std::string> redundantStrings;
    bool allAreRedundant = true;

    for (size_t i = 0; i < truthStrings.size(); ++i) {
        std::istringstream iss(truthStrings[i]);
        std::string element;
        std::vector<std::string> elements;

        while (iss >> element) {
            elements.push_back(element);
        }

        if (elements.size() == originalStrings.size()) {
            bool hasOne = false;
            for (const auto& e : elements) {
                if (e.find('1') != std::string::npos) {
                    hasOne = true;
                    break;
                }
            }
            if (!hasOne) {
                redundantStrings.push_back(originalStrings[i]);
            }
            else {
                allAreRedundant = false;
            }
        }
        else {
            allAreRedundant = false;
        }
    }

    if (allAreRedundant) {
        return {};
    }

    return redundantStrings;
}

void ReducedFormsBuilder::TCNFCalc(std::string& input) {
    setlocale(LC_ALL, "ru");
    std::vector<std::string> previousString = splitExpression(input);
    bool continueMerge = true;
    while (continueMerge) {
        std::vector<std::string> splittedString = splitExpression(input);
        int counter = countUniqueVariables(splittedString);
        std::vector<std::string> variables = findUniqueVariables(splittedString);
        std::vector<std::string> numericString = convertLogicToNumeric(splittedString, variables);
        std::vector<std::string> mergedString = findMerges(numericString, counter);
        std::vector<std::string> charString = numericStringsToVariables(mergedString, variables);
        if (charString == previousString) {
            std::cout << "Данная форма является тупиковой " << std::endl;
            std::string finalizedString = vectorToStringCNF(charString);
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        std::vector<std::string> truthValues = transformExpressionsCNF(charString);
        std::vector<std::string> substitutedValues = substituteValuesForAllExpressions(charString, truthValues);
        std::vector<std::string> extraStrings = findRedundantStringsCNF(charString, substitutedValues);
        
        std::cout << std::endl;
        std::vector<std::string> removedString = removeStrings(charString, extraStrings);
        std::string finalizedString = vectorToStringCNF(removedString); 
        std::vector<std::string> splittedStringFinal = splitExpression(finalizedString);
        int counterFinal = countUniqueVariables(splittedStringFinal);
        std::vector<std::string> variablesFinal = findUniqueVariables(splittedStringFinal);
        std::vector<std::string> numericStringFinal = convertLogicToNumeric(splittedStringFinal, variablesFinal);
        std::vector<std::string> mergedStringFinal = findMerges(numericStringFinal, counterFinal);
        std::vector<std::string> charStringFinal = numericStringsToVariables(mergedStringFinal, variablesFinal);
        if (charStringFinal == removedString)
        {
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        else {
            input = finalizedString;
        }
    }
}

void ReducedFormsBuilder::TDNFCalc(std::string& input) {
    setlocale(LC_ALL, "ru");
    std::vector<std::string> previousString = splitExpression(input);
    bool continueMerge = true;
    while (continueMerge) {
        std::vector<std::string> splittedString = splitExpression(input);
        int counter = countUniqueVariables(splittedString);
        std::vector<std::string> variables = findUniqueVariables(splittedString);
        std::vector<std::string> numericString = convertLogicToNumeric(splittedString, variables);
        std::vector<std::string> mergedString = findMerges(numericString, counter);
        std::vector<std::string> charString = numericStringsToVariables(mergedString, variables);
        if (charString == previousString) {
            std::cout << "Данная форма является тупиковой " << std::endl;
            std::string finalizedString = vectorToStringDNF(charString);
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        std::vector<std::string> truthValues = transformExpressionsDNF(charString);
        std::vector<std::string> substitutedValues = substituteValuesForAllExpressions(charString, truthValues);
        std::vector<std::string> extraStrings = findRedundantStringsDNF(charString, substitutedValues);
       
        std::cout << std::endl;
        std::vector<std::string> removedString = removeStrings(charString, extraStrings);
        std::string finalizedString = vectorToStringDNF(removedString);
        std::vector<std::string> splittedStringFinal = splitExpression(finalizedString);
        int counterFinal = countUniqueVariables(splittedStringFinal);
        std::vector<std::string> variablesFinal = findUniqueVariables(splittedStringFinal);
        std::vector<std::string> numericStringFinal = convertLogicToNumeric(splittedStringFinal, variablesFinal);
        std::vector<std::string> mergedStringFinal = findMerges(numericStringFinal, counterFinal);
        std::vector<std::string> charStringFinal = numericStringsToVariables(mergedStringFinal, variablesFinal);
        if (charStringFinal == removedString)
        {
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        else {
            input = finalizedString;
        }
    }
}



