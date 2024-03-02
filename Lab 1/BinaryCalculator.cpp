#include"BinaryCalculator.h"
#include<algorithm>
#include<utility>

std::string BinaryCalculator::binarySum(int firstSummand, int secondSummand) {
	BinaryConverter converter;
	std::string firstSummandBinary = converter.additionalCode(firstSummand);
	std::string secondSummandBinary = converter.additionalCode(secondSummand);
	std::string result = "";
	int firstSummandSize = firstSummandBinary.size() - 1;
	int secondSummandSize = secondSummandBinary.size() - 1;
	int carry = 0;
	while (firstSummandSize >= 0 || secondSummandSize >= 0 || carry == 1) {
		carry += (firstSummandSize >= 0) ? firstSummandBinary[firstSummandSize] - '0' : 0;
		carry += (secondSummandSize >= 0) ? secondSummandBinary[secondSummandSize] - '0' : 0;
		result = char(carry % 2 + '0') + result;
		carry /= 2;
		--firstSummandSize;
		--secondSummandSize;
	}
	if (result.size() > 16) {
		result.erase(0, 1);
	}
	char sign = result[0];
	return result;
}

std::string BinaryCalculator::binaryDifference(int minuend, int subtrahend) {
	BinaryConverter converter;
	std::string minuendBinary = converter.additionalCode(minuend);
	std::string subtrahendBinary = converter.additionalCode(subtrahend);
	std::string subtrahendBinaryProm = converter.bitsInventer(subtrahendBinary);
	std::string subtrahendBinaryFinal = converter.addOne(subtrahendBinaryProm);
	std::string result = "";
	int minuendSize = minuendBinary.size() - 1;
	int subtrahendSize = subtrahendBinaryFinal.size() - 1;
	int carry = 0;
	while (minuendSize >= 0 || subtrahendSize >= 0 || carry == 1) {
		carry += (minuendSize >= 0) ? minuendBinary[minuendSize] - '0' : 0;
		carry += (subtrahendSize >= 0) ? subtrahendBinaryFinal[subtrahendSize] - '0' : 0;
		result = char(carry % 2 + '0') + result;
		carry /= 2;
		--minuendSize;
		--subtrahendSize;
	}
	if (result.size() > 16) {
		result.erase(0, 1);
	}
	char sign = result[0];
	return result;
}

std::string BinaryCalculator::binaryProduct(int multiplicand, int multiplier) {
	BinaryConverter converter;
	std::string firstSign = converter.directCode(multiplicand);
	std::string secondSign = converter.directCode(multiplier);
	firstSign = firstSign[0];
	secondSign = secondSign[0];
	std::string binaryMultiplicand = converter.directCode(fabs(multiplicand));
	std::string binaryMultiplier = converter.directCode(fabs(multiplier));
	int binMultiplicandSize = binaryMultiplicand.length();
	int binMultiplierSize = binaryMultiplier.length();

	std::vector<int> product(binMultiplicandSize + binMultiplicandSize, 0);

	for (int i = binMultiplicandSize - 1; i >= 0; --i) {
		for (int j = binMultiplierSize - 1; j >= 0; --j) {
			int bitMultiplicand = binaryMultiplicand[i] - '0';
			int bitMultiplier = binaryMultiplier[j] - '0';
			product[i + j + 1] += bitMultiplicand * bitMultiplier;
			product[i + j] += product[i + j + 1] / 2;
			product[i + j + 1] %= 2;
		}
	}

	std::string result;
	for (int bit : product) {
		result += std::to_string(bit);
	}
	signBit = firstSign == secondSign ? '0' : '1';
	result = result.substr(result.length() - 15, 15);
	result = signBit + result;
	return result;
}

std::pair<std::string, std::string> BinaryCalculator::binaryDivision(int dividend, int divisor) {
	BinaryConverter converter;
	std::string firstSign = converter.directCode(dividend);
	std::string secondSign = converter.directCode(divisor);
	char firstSignBit = firstSign[0];
	char secondSignBit = secondSign[0];

	std::string binaryDividend = converter.directCode(fabs(dividend));
	std::string binaryDivisor = converter.directCode(fabs(divisor));

	int precision = 6;
	std::string result = "";
	std::string part = "";
	int index = 0;

	binaryDividend += std::string(precision, '0');

	while (index < binaryDividend.length()) {
		part = converter.removeLeadingZerosBinary(part);
		if (converter.isGreaterOrEqualBinary(part, binaryDivisor) || index >= binaryDividend.length()) {
			part = converter.binarySubtract(part, binaryDivisor);
			result += "1";
		}
		else if (!result.empty() || index < binaryDividend.length()) {
			result += "0";
		}
		if (index < binaryDividend.length()) {
			part += binaryDividend[index];
		}
		index++;
	}
	std::string quotient = result.substr(0, result.length() - precision + 1);
	std::string remainder = result.substr(result.length() + 1 - precision);
	if (quotient.empty()) quotient = "0";
	if (remainder.empty()) remainder = "0";
	signBit = firstSignBit == secondSignBit ? '0' : '1';
	quotient = signBit + quotient;
	return { quotient, remainder };
}
