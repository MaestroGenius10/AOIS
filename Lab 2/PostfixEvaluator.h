#pragma once
#include "BooleanExpression.h"
#include <vector>
#include <string>
#include <map>

class PostfixEvaluator {
public:
    bool evaluate(const std::vector<std::string>& postfix, const std::map<char, bool>& variableValues);
};

