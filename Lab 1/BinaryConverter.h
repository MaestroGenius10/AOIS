#pragma once
#include<string>
#include<algorithm>
#include<utility>
class BinaryConverter {
public:
	std::string toBinary(int numberToConvert);
	std::string bitsInventer(std::string& DirectCode);
	std::string result;
	std::string ToSixteenBit(int numberToConvert, std::string input);
	std::string addOne(std::string& input);
	std::string directCode(int numberToConvert);
	std::string reverseCode(int numberToConvert);
	std::string additionalCode(int numberToConvert);
	double directReminderToDecimal(std::string input);
	int directToDecimal(std::string input);
	int additionalToDecimal(std::string input);
	int toDecimal(std::string input);
	std::string removeLeadingZerosBinary(const std::string& input);
	std::string binarySubtract(std::string minuend, std::string subtrahend);
	bool isGreaterOrEqualBinary(const std::string& minuend, const std::string& subtrahend);



private:
	char sign;
	std::string DirectCode;
	std::string ReverseCode;
	std::string AdditionalCode;

};
