#include"FinalFormsBuilder.h"
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<iomanip>
std::vector<std::string> FinalFormsBuilder::splitExpression(std::string& expression) {
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

std::vector<std::string> FinalFormsBuilder::findUniqueVariables(std::vector<std::string>& expressions) {
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

int FinalFormsBuilder::countUniqueVariables(std::vector<std::string>& expressions) {
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

std::vector<std::string> FinalFormsBuilder::convertLogicToNumeric
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

std::vector<std::string> FinalFormsBuilder::findMerges(std::vector<std::string>& strings, int N) {
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

std::vector<std::string> FinalFormsBuilder::numericStringsToVariables
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

bool FinalFormsBuilder::isContained(std::string& candidate, std::string& target) {
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

std::vector<std::vector<bool>> FinalFormsBuilder::buildCoverageMatrix
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

std::vector<std::string> FinalFormsBuilder::findExtraStrings(
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

std::vector<std::string> FinalFormsBuilder::removeStrings(std::vector<std::string>& input, std::vector<std::string>& toRemove) {
    std::vector<std::string> result = input;

    for (const auto& rem : toRemove) {
        auto it = std::find(result.begin(), result.end(), rem);
        if (it != result.end()) {
            result.erase(it);
        }
    }
    return result;
}

std::string FinalFormsBuilder::vectorToStringDNF(std::vector<std::string>& vec) {
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

void FinalFormsBuilder::TDNFCalcTable(std::string& input) {
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
            std::string finalizedString = vectorToStringDNF(charString);
            std::cout << "Тупиковая форма: " << std::endl;
            std::cout << finalizedString << std::endl;
            break;
        }
        auto coverageMatrix = buildCoverageMatrix(splittedString, charString);
        std::vector <std::string> toRemoveStrings = findExtraStrings(charString, coverageMatrix);
        std::cout << std::endl;
        std::vector<std::string> removedString = removeStrings(charString, toRemoveStrings);
        std::string finalizedString = vectorToStringDNF(removedString);
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

bool FinalFormsBuilder::canMerge(std::string& a, std::string& b, int N) {
    int diffCount = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] != b[i]) diffCount++;
    }
    return diffCount == 1;
}

std::string FinalFormsBuilder::mergeStrings(std::string& a, std::string& b, int N) {
    std::string result = a;
    for (int i = 0; i < N; ++i) {
        if (a[i] != b[i]) result[i] = '2';
    }
    return result;
}
