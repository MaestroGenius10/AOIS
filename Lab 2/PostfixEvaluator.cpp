#include "PostfixEvaluator.h"
#include <stack>
#include <cctype> 

bool PostfixEvaluator::evaluate(const std::vector<std::string>& postfix, const std::map<char, bool>& variableValues) {
    std::stack<bool> stack;

    for (const auto& token : postfix) {
        if (token.length() == 1 && std::isalpha(token[0])) {
            stack.push(variableValues.at(token[0]));
        }
        else {
            if (token == "!") {
                bool op1 = stack.top(); stack.pop();
                stack.push(!op1);
            }
            else {
                bool op2 = stack.top(); stack.pop();
                bool op1 = stack.top(); stack.pop();

                if (token == "&") {
                    stack.push(op1 && op2);
                }
                else if (token == "+") {
                    stack.push(op1 || op2);
                }
                else if (token == ">") {
                    stack.push(!op1 || op2);
                }
                else if (token == "=") {
                    stack.push(op1 == op2);
                }
            }
        }
    }

    return stack.top();
}