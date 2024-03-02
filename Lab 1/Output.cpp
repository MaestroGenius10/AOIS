#include"Output.h"
void Output::printNumberInfo(int numberToConvert) {
	setlocale(LC_ALL, "Ru");
	BinaryConverter converter;
	Output printer;
	DirectCode = converter.directCode(numberToConvert);
	char sign = DirectCode[0] - '0';
	std::string signBit = std::to_string(sign);
	DirectCode = DirectCode.substr(1, 15);
	ReverseCode = converter.reverseCode(numberToConvert).substr(1, 15);
	AdditionalCode = converter.additionalCode(numberToConvert).substr(1, 15);
	
	std::cout << "Число: " << numberToConvert << std::endl;
	std::cout << "Прямой код: [" << signBit << " " << DirectCode << "]" << std::endl;
	std::cout << "Обратный код: [" << signBit << " " << ReverseCode << "]" << std::endl;
	std::cout << "Дополнительный код: [" << signBit << " " << AdditionalCode << "]" << std::endl;
}

void Output::printNumberSum(int firstSummand, int secondSummand) {
	BinaryCalculator calculator;
	BinaryConverter converter;
	std::string sum = calculator.binarySum(firstSummand, secondSummand);
	printNumberInfo(firstSummand);
	printNumberInfo(secondSummand);
	int result = converter.toDecimal(sum);
	printNumberInfo(result);
}

void Output::printNumberDif(int minuend, int subtrahend) {
	BinaryCalculator calculator;
	BinaryConverter converter;
	std::string dif = calculator.binaryDifference(minuend, subtrahend);
	printNumberInfo(minuend);
	printNumberInfo(subtrahend);
	int result = converter.toDecimal(dif);
	printNumberInfo(result);
}

void Output::printNumberProduct(int multiplicand, int multiplier) {
	BinaryCalculator calculator;
	BinaryConverter converter;
	std::string prod = calculator.binaryProduct(multiplicand, multiplier);
	printNumberInfo(multiplicand);
	printNumberInfo(multiplier);
	int result = converter.directToDecimal(prod);
	printNumberInfo(result);
}

void Output::printNumberDivision(int dividend, int divisor) {
	BinaryConverter converter;
	BinaryCalculator calculator;
	std::pair<std::string, std::string> div = calculator.binaryDivision(dividend, divisor);
	std::string result = div.first;
	sign = result[0];
	std::string signBit;
	signBit = sign == '1' ? '-' : ' ';
	result = result.erase(0, 2);
	std::string reminder = div.second;
	printNumberInfo(dividend);
	printNumberInfo(divisor);
	int resultInt = converter.directToDecimal(result);
	double reminderDouble = converter.directReminderToDecimal(reminder);
	double finalResult = resultInt + reminderDouble;
	std::cout << "_________________________________" << std::endl;
	std::cout << "Прямой код деления: [" << sign << " " << result.erase(0, 1) << "." << reminder << "]" << std::endl;
	std::cout << "Результат в десятичной системе: " << signBit << finalResult << std::endl;

}

void Output::printIEEESum(float firstSummand, float secondSummand) {
	setlocale(LC_ALL, "ru");
	IEEE754 converter;
	std::string firstSummandIEEE = converter.floatToIEEE754(firstSummand);
	std::string secondSummandIEEE = converter.floatToIEEE754(secondSummand);

	std::string result = converter.addIEEE754(firstSummandIEEE, secondSummandIEEE);

	float resultDecimal = converter.IEEE754ToFloat(result);

	std::cout << "Первое слагаемое: " << firstSummandIEEE << std::endl;
	std::cout << "Второе слагаемое: " << secondSummandIEEE << std::endl;

	std::cout << "Результат: " << result << std::endl;
	std::cout << "Результат в десятичной форме: " << resultDecimal << std::endl;

}