#pragma once
#include <vector>
#include <map>
#include <string>

class NormalFormsBuilder {
public:
    NormalFormsBuilder(const std::vector<std::map<std::string, bool>>& combinations,
        const std::vector<bool>& results,
        const std::vector<std::string>& variables,
        const std::string& resultVariable);
    std::string buildMDNF() const;

private:
    std::vector<std::map<std::string, bool>> combinations;
    std::vector<bool> results;
    std::vector<std::string> variables;
    std::string resultVariable;
};
