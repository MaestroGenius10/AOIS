#pragma once
#include<iostream>
#include"BooleanExpression.h"
#include"InfixToPostfixConverter.h"
#include"NormalFormsBuilder.h"
#include"PostfixEvaluator.h"
#include"TruthTableGenerator.h"

class Output {
public:
	std::string userInput();
	void printAllInfo(std::string& expression);
};
