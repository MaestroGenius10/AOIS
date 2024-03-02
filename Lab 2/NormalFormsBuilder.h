#pragma once
#include <vector>
#include <map>
#include <string>

class NormalFormsBuilder {
public:
    NormalFormsBuilder(const std::vector<std::map<char, bool>>& combinations, const std::vector<bool>& results);
    std::string buildMDNF();
    std::string buildMCNF();
    std::string buildNumericMDNF();
    std::string buildNumericMCNF();
    long long int numericFunctionForm();
private:
    const std::vector<std::map<char, bool>>& combinations;
    const std::vector<bool>& results;
};
