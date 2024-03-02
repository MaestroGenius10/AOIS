#include<iostream>
#include<cmath>
#include"BinaryConverter.h"
std::string BinaryConverter::toBinary(int numberToConvert) {
	if (numberToConvert > 0)
		do {
			result = std::to_string(numberToConvert % 2) + result;
			numberToConvert /= 2;
		} while (numberToConvert > 0);
	else
		do {
			result = (std::to_string(abs(numberToConvert % 2)) + result);
			numberToConvert /= 2;
		} while (numberToConvert < 0);

		return result;
}

std::string BinaryConverter::bitsInventer(std::string& DirectCode) {
	std::string result = DirectCode;
	for (char& i : result) {
		if (i == '0') {
			i = '1';
		}
		else if (i == '1') {
			i = '0';
		}
	}
	return result;
}

std::string BinaryConverter::ToSixteenBit(int numberToConvert, std::string input) {
	BinaryConverter converter;
	std::string result = input;
	if (numberToConvert >= 0 && result.length() < 15) {
		sign = 0;
		std::string signBit = std::to_string(sign);
		result = signBit + std::string(15 - result.length(), '0') + result;
	}
	else if (numberToConvert < 0 && result.length() < 15) {
		sign = 1;
		std::string signBit = std::to_string(sign);
		result = signBit + std::string(15 - result.length(), '1') + result;
	}
	return result;
}

std::string BinaryConverter::addOne(std::string& input) {
	std::string result = input;
	int sizeOfNumber = result.size() - 1;

	while (sizeOfNumber >= 0) {
		if (result[sizeOfNumber] == '1') {
			result[sizeOfNumber] = '0';
			--sizeOfNumber;
		}
		else {
			result[sizeOfNumber] = '1';
			return result;
		}
	}
	return result;
}

std::string BinaryConverter::directCode(int numberToConvert) {
	BinaryConverter converter;
	if (numberToConvert >= 0) {
		DirectCode = converter.toBinary(numberToConvert);
		DirectCode = converter.ToSixteenBit(numberToConvert, DirectCode);
	}
	else {
		DirectCode = converter.toBinary(numberToConvert);
		sign = 1;
		std::string signBit = std::to_string(sign);
		DirectCode = signBit + std::string(15 - DirectCode.length(), '0') + DirectCode; 
	}
	return DirectCode;
}

std::string BinaryConverter::reverseCode(int numberToConvert) {
	BinaryConverter converter;
	if (numberToConvert >= 0) {
		ReverseCode = converter.directCode(numberToConvert);
	}
	else {
		ReverseCode = converter.toBinary(numberToConvert);
		ReverseCode = converter.bitsInventer(ReverseCode);
	}
	ReverseCode = converter.ToSixteenBit(numberToConvert, ReverseCode);
	return ReverseCode;
}

std::string BinaryConverter::additionalCode(int numberToConvert) {
	BinaryConverter converter;
	if (numberToConvert >= 0) {
		AdditionalCode = converter.directCode(numberToConvert);
	}
	else {
		AdditionalCode = converter.reverseCode(numberToConvert);
		AdditionalCode = converter.addOne(AdditionalCode);
	}
	AdditionalCode = converter.ToSixteenBit(numberToConvert, AdditionalCode);
	return AdditionalCode;
}

int BinaryConverter::directToDecimal(std::string input) {
	BinaryConverter converter;
	sign = input[0];
	DirectCode = input.substr(1, 15);
	int result = 0;
	int pointer = DirectCode.length();
	for (int i = 0;i < pointer;++i) {
		if (DirectCode[pointer - i - 1] == '1') {
			result += pow(2, i);
		}
	}
	if (sign == '1') {
		result = -result;
	}
	return result;
}

int BinaryConverter::additionalToDecimal(std::string input) {
	BinaryConverter converter;
	sign = input[0];
	AdditionalCode = input.substr(1, 15);
	if (sign == '1') {
		AdditionalCode = converter.bitsInventer(AdditionalCode);
		AdditionalCode = converter.addOne(AdditionalCode);
	}
	int result = 0;
	int pointer = AdditionalCode.length();
	for (int i = 0;i < pointer;++i) {
		if (AdditionalCode[pointer - i - 1] == '1') {
			result += pow(2, i);
		}
	}
	return result;
}

int BinaryConverter::toDecimal(std::string input) {
	BinaryConverter converter;
	char signDefinitor = input[0];
	int result = 0;
	if (signDefinitor == '0') {
		result = converter.directToDecimal(input);
	}
	else {
		result = converter.additionalToDecimal(input);
		result = -result;
	}

	return result;
}

double BinaryConverter::directReminderToDecimal(std::string input) {
	BinaryConverter converter;
	DirectCode = input;
	double result = 0;
	int pointer = DirectCode.length() - 1;
	for (int i = 0; i < pointer; ++i) {
		if (DirectCode[i] == '1') {
			result += pow(2, -(i + 1));
		}
	}
	return result;
}

std::string BinaryConverter::removeLeadingZerosBinary(const std::string& input) {
	std::string result = input;
	while (result.length() > 1 && result[0] == '0') {
		result.erase(0, 1);
	}
	return result;
}
std::string BinaryConverter::binarySubtract(std::string minuend, std::string subtrahend) {
	std::string result = "";
	int borrow = 0;

	while (minuend.length() < subtrahend.length()) minuend = "0" + minuend;
	while (subtrahend.length() < minuend.length()) subtrahend = "0" + subtrahend;

	for (int i = minuend.length() - 1; i >= 0; i--) {
		int digitDifference = (minuend[i] - '0') - (subtrahend[i] - '0') - borrow;
		if (digitDifference < 0) {
			digitDifference += 2;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		result = char(digitDifference + '0') + result;
	}

	return removeLeadingZerosBinary(result);
}

bool BinaryConverter::isGreaterOrEqualBinary(const std::string& minuend, const std::string& subtrahend) {
	std::string trimmedA = removeLeadingZerosBinary(minuend);
	std::string trimmedB = removeLeadingZerosBinary(subtrahend);
	if (trimmedA.length() > trimmedB.length()) return true;
	if (trimmedB.length() > trimmedA.length()) return false;
	return trimmedA >= trimmedB;
}

