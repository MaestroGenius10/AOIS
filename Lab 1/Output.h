#pragma once
#include"BinaryConverter.h"
#include"BinaryCalculator.h"
#include"IEEE754.h"
#include<iostream>
class Output {
public:
	void printNumberInfo(int numberToConvert);
	void printNumberSum(int firstSummand, int secondSummand);
	void printNumberDif(int minuend, int subtrahend);
	void printNumberProduct(int multiplicand, int multiplier);
	void printNumberDivision(int divident, int divisor);
	void printIEEESum(float firstSummand, float secondSummand);
private:
	char sign;
	std::string DirectCode;
	std::string ReverseCode;
	std::string AdditionalCode;
};
