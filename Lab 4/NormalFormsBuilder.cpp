#include "NormalFormsBuilder.h"
#include <sstream>

NormalFormsBuilder::NormalFormsBuilder(const std::vector<std::map<std::string, bool>>& combinations,
    const std::vector<bool>& results,
    const std::vector<std::string>& variables,
    const std::string& resultVariable)
    : combinations(combinations), results(results), variables(variables), resultVariable(resultVariable) {}

std::string NormalFormsBuilder::buildMDNF() const {
    std::stringstream mdnf;
    bool firstTerm = true;
    for (size_t i = 0; i < combinations.size(); ++i) {
        if (results[i]) {
            if (!firstTerm) mdnf << " + ";
            mdnf << "(";
            bool firstVar = true;
            for (const auto& varName : variables) {
                if (!firstVar) mdnf << " & ";
                auto varValue = combinations[i].at(varName);
                mdnf << (varValue ? "" : "!") << varName;
                firstVar = false;
            }
            mdnf << ")";
            firstTerm = false;
        }
    }
    return mdnf.str().empty() ? "1" : mdnf.str();
}
