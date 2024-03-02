#include "InfixToPostfixConverter.h"
#include <stack>
#include <cctype>

std::vector<std::string> InfixToPostfixConverter::infixToPostfix(const std::string& input) {
    std::stack<char> operations;
    std::vector<std::string> postfix;
    for (size_t i = 0; i < input.length(); ++i) {
        char current = input[i];

        if (current == '(') {
            operations.push(current);
        }
        else if (current == ')') {
            while (!operations.empty() && operations.top() != '(') {
                postfix.push_back(std::string(1, operations.top()));
                operations.pop();
            }
            if (!operations.empty()) operations.pop();
        }
        else if (isOperation(current)) {
            while (!operations.empty() && getPriority(operations.top()) >= getPriority(current)) {
                postfix.push_back(std::string(1, operations.top()));
                operations.pop();
            }
            operations.push(current);
        }
        else if (std::isalpha(current)) {
            postfix.push_back(std::string(1, current));
        }
    }

    while (!operations.empty()) {
        postfix.push_back(std::string(1, operations.top()));
        operations.pop();
    }

    return postfix;
}

bool InfixToPostfixConverter::isOperation(char current) {
    return current == '&' || current == '+' || current == '!' || current == '>' || current == '=';
}

int InfixToPostfixConverter::getPriority(char op) {
    if (op == '!') return 5;
    if (op == '&') return 4;
    if (op == '+') return 3;
    if (op == '>') return 2;
    if (op == '=') return 1;
    return 0;
}
