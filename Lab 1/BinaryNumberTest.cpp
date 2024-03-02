#include "pch.h"
#include "CppUnitTest.h"
#include"..\BinaryNumber\BinaryCalculator.h"
#include"..\BinaryNumber\BinaryConverter.h"
#include"..\BinaryNumber\IEEE754.h"
#include"..\BinaryNumber\Output.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryNumberTest
{
	TEST_CLASS(BinaryNumberTest)
	{
	public:

		TEST_METHOD(TestToBinary)
		{
			BinaryConverter converter;
			int a = 5;
			int b = -5;
			std::string j = converter.toBinary(a);
			std::string expect = std::to_string(101);
			Assert::AreEqual(expect, j);
		}

		TEST_METHOD(TestBitsInverter)
		{
			BinaryConverter converter;
			std::string input = "101";
			std::string output = converter.bitsInventer(input);
			std::string expect = "010";
			Assert::AreEqual(expect, output);
		}
		TEST_METHOD(TestDirectCode)
		{
			BinaryConverter converter;
			int numberToConvertOne = 9;
			int numberToConvertTwo = -9;
			std::string outputOne = converter.directCode(numberToConvertOne);
			std::string outputTwo = converter.directCode(numberToConvertTwo);
			std::string expectOne = "0000000000001001";
			std::string expectTwo = "1000000000001001";
			Assert::AreEqual(expectOne, outputOne);
			Assert::AreEqual(expectTwo, outputTwo);
		}
		TEST_METHOD(TestReverseCode)
		{
			BinaryConverter converter;
			int numberToConvertOne = 9;
			int numberToConvertTwo = -9;
			std::string outputOne = converter.reverseCode(numberToConvertOne);
			std::string outputTwo = converter.reverseCode(numberToConvertTwo);
			std::string expectOne = "0000000000001001";
			std::string expectTwo = "1111111111110110";
			Assert::AreEqual(expectOne, outputOne);
			Assert::AreEqual(expectTwo, outputTwo);
		}
		TEST_METHOD(TestAdditionalCode)
		{
			BinaryConverter converter;
			int numberToConvertOne = 9;
			int numberToConvertTwo = -9;
			std::string outputOne = converter.additionalCode(numberToConvertOne);
			std::string outputTwo = converter.additionalCode(numberToConvertTwo);
			std::string expectOne = "0000000000001001";
			std::string expectTwo = "1111111111110111";
			Assert::AreEqual(expectOne, outputOne);
			Assert::AreEqual(expectTwo, outputTwo);
		}

		TEST_METHOD(TestDirectToDecimal)
		{
			BinaryConverter converter;
			std::string inputOne = std::to_string(1000000000001001);
			int outputOne = converter.directToDecimal(inputOne);
			int expectOne = -9;
			Assert::AreEqual(expectOne, outputOne);
		}
		TEST_METHOD(TestToDecimal)
		{
			BinaryConverter converter;
			std::string inputOne = "0000000000000001";
			int outputOne = converter.toDecimal(inputOne);
			int expectOne = 1;
			Assert::AreEqual(expectOne, outputOne);
		}
		TEST_METHOD(TestBinarySum)
		{
			BinaryConverter converter;
			BinaryCalculator calculator;
			int firstSummand = 18;
			int secondSumamnd = -6;
			std::string outputSum = calculator.binarySum(firstSummand, secondSumamnd);
			std::string expectSum = "0000000000001100";
			Assert::AreEqual(expectSum, outputSum);
		}
		TEST_METHOD(TestBinaryDif)
		{
			BinaryConverter converter;
			BinaryCalculator calculator;
			int minuend = 18;
			int subtrahend = -6;
			std::string outputDif = calculator.binaryDifference(minuend, subtrahend);
			std::string expectDif = "0000000000011000";
			Assert::AreEqual(expectDif, outputDif);
		}
		TEST_METHOD(TestBinaryProduct)
		{
			BinaryConverter converter;
			BinaryCalculator calculator;
			int multiplicand = 18;
			int multiplier = -6;
			std::string outputProduct = calculator.binaryProduct(multiplicand, multiplier);
			std::string expectProduct = "1000000001101100";
			Assert::AreEqual(expectProduct, outputProduct);
		}
		TEST_METHOD(TestBinaryDivision)
		{
			BinaryConverter converter;
			BinaryCalculator calculator;
			int dividend = 12;
			int divisor = 8;
			std::pair<std::string, std::string>outputDivision = calculator.binaryDivision(dividend, divisor);
			Assert::AreEqual(std::string("000000000000000001"), outputDivision.first);
			Assert::AreEqual(std::string("10000"), outputDivision.second);
		}
		TEST_METHOD(TestIEEE) 
		{
		IEEE754 converter;
		float firstSummand = 12.5;
		float secondSummand = 4.9;
		
		std::string firstSummandBinary = converter.floatToIEEE754(firstSummand);
		std::string secondSummandBinary = converter.floatToIEEE754(secondSummand);

		std::string result = converter.addIEEE754(firstSummandBinary, secondSummandBinary);
		float resultDecimal = converter.IEEE754ToFloat(result); 

		std::string expectFirstSummandBinary = "01000001010010000000000000000000";
		std::string expectSecondSummandBinary = "01000000100111001100110011001101";
		std::string expectResult = "01000001100010110011001100110011";
		float expectResultDecimal = 17.4;
		
		Assert::AreEqual(expectFirstSummandBinary, firstSummandBinary);
		Assert::AreEqual(expectSecondSummandBinary, secondSummandBinary);
		Assert::AreEqual(expectResult, result);
		Assert::AreEqual(expectResultDecimal, resultDecimal);
		}
	};
}
