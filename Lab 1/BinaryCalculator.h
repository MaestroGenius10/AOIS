#pragma once
#include"BinaryConverter.h"
#include<cmath>
#include<vector>
class BinaryCalculator {
public:
	std::string binarySum(int firstSummand, int secondSummand);
	std::string binaryDifference(int minuend, int subtrahend);
	std::string binaryProduct(int multiplicand, int multiplier);
	std::pair<std::string, std::string> binaryDivision(int dividend, int divisor);

private:
	int firstSummand;
	int secondSummand;
	int minuend;
	int subtrahend;
	int multiplicand;
	int multiplier;
	std::string signBit;
	std::string result;
};
