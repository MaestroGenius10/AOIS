#include"..\LogicalCalculator\BooleanExpression.h"
#include"..\LogicalCalculator\Output.h"
#include"..\LogicalCalculator\NormalFormsBuilder.h"
#include"..\LogicalCalculator\InfixToPostfixConverter.h"
#include"..\LogicalCalculator\PostfixEvaluator.h"
#include"..\LogicalCalculator\TruthTableGenerator.h"
#include"..\LogicalCalculator\ReducedFormsBuilder.h"
#include"..\\LogicalCalculator\KarnaughMapDNF.h"
#include"..\\LogicalCalculator\KarnaughMapCNF.h"
#include <iostream>

int main(){
    Output printer;
    std::string function = printer.userInput();
    printer.printAllInfo(function);
}


