#pragma once
#include <vector>
#include <string>

class InfixToPostfixConverter {
public:
    std::vector<std::string> infixToPostfix(const std::string& input);

private:
    bool isOperation(char current);
    int getPriority(char op);
};