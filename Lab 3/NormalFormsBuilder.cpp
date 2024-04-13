#include "NormalFormsBuilder.h"
#include<sstream>
NormalFormsBuilder::NormalFormsBuilder(const std::vector<std::map<char, bool>>& combinations, const std::vector<bool>& results)
    : combinations(combinations), results(results) {}

std::string NormalFormsBuilder::buildMDNF() {
    std::string mdnf;
    bool firstTerm = true;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i]) {
            if (!firstTerm) mdnf += " + ";
            mdnf += "(";
            bool firstVar = true;
            for (const auto& var : combinations[i]) {
                if (!firstVar) mdnf += " & ";
                if (!var.second) mdnf += "!";
                mdnf += var.first;
                firstVar = false;
            }
            mdnf += ")";
            firstTerm = false;
        }
    }
    return mdnf.empty() ? "0" : mdnf;
}

std::string NormalFormsBuilder::buildMCNF() {
    std::string mcnf;
    bool firstTerm = true;
    for (size_t i = 0; i < results.size(); ++i) {
        if (!results[i]) {
            if (!firstTerm) mcnf += " & ";
            mcnf += "(";
            bool firstVar = true;
            for (const auto& var : combinations[i]) {
                if (!firstVar) mcnf += " + ";
                if (var.second) mcnf += "!";
                mcnf += var.first;
                firstVar = false;
            }
            mcnf += ")";
            firstTerm = false;
        }
    }
    return mcnf.empty() ? "1" : mcnf;
}

std::string NormalFormsBuilder::buildNumericMDNF() {
    std::string mdnf;
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i]) {
            if (!mdnf.empty()) mdnf += ", ";
            mdnf += std::to_string(i);
        }
    }
    return mdnf.empty() ? "{}" : "{" + mdnf + "}" + "+";
}

std::string NormalFormsBuilder::buildNumericMCNF() {
    std::string mcnf;
    for (size_t i = 0; i < results.size(); ++i) {
        if (!results[i]) {
            if (!mcnf.empty()) mcnf += ", ";
            mcnf += std::to_string(i);
        }
    }
    return mcnf.empty() ? "{}" : "{" + mcnf + "}" + "&";
}
long long int NormalFormsBuilder::numericFunctionForm() {
    long long int result = 0;
    int pointer = results.size();
    for (size_t i = 0; i < pointer; ++i) {
        if (results[pointer - i - 1]) {
            result += pow(2, i);
        }
    }
    return result;
}
