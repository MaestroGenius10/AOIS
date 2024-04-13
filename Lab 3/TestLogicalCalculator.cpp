#include "pch.h"
#include "CppUnitTest.h"
#include"..\LogicalCalculator\BooleanExpression.h"
#include"..\LogicalCalculator\InfixToPostfixConverter.h"
#include"..\LogicalCalculator\NormalFormsBuilder.h"
#include"..\LogicalCalculator\Output.h"
#include"..\LogicalCalculator\PostfixEvaluator.h"
#include"..\LogicalCalculator\TruthTableGenerator.h"
#include"..\LogicalCalculator\ReducedFormsBuilder.h"
#include"..\LogicalCalculator\KarnaughMapDNF.h"
#include"..\LogicalCalculator\KarnaughMapCNF.h"
#include<algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLogicalCalculator
{
	TEST_CLASS(TestLogicalCalculator)
	{
	public:

		TEST_METHOD(TestFuncionOfThreeVars)
		{
			TruthTableGenerator generator;
			std::string expression = "(A&B)+(!(C))";
			generator.generateTruthTable(expression);
			auto combinations = generator.getCombinations();
			auto results = generator.getResults();
			NormalFormsBuilder normalFormsBuilder(combinations, results);

			std::string mcnf = normalFormsBuilder.buildMCNF();
			std::string mdnf = normalFormsBuilder.buildMDNF();

			std::string mcnfNum = normalFormsBuilder.buildNumericMCNF();
			std::string mdnfNum = normalFormsBuilder.buildNumericMDNF();

			long long int numForm = 0;

			numForm = normalFormsBuilder.numericFunctionForm();

			std::string mcnfNumExpected = "{1, 3, 5}&";
			std::string mdnfNumExpected = "{0, 2, 4, 6, 7}+";
			long long int numFormExpected = 171;
			Assert::AreEqual(mcnfNumExpected, mcnfNum);
			Assert::AreEqual(mdnfNumExpected, mdnfNum);
			Assert::AreEqual(numFormExpected, numFormExpected);

		}
		TEST_METHOD(TestFumctionOfFourVars)
		{
			TruthTableGenerator generator;
			std::string expression = "(A>B)+(C&(!(D)))";
			generator.generateTruthTable(expression);
			auto combinations = generator.getCombinations();
			auto results = generator.getResults();
			NormalFormsBuilder normalFormsBuilder(combinations, results);

			std::string mcnf = normalFormsBuilder.buildMCNF();
			std::string mdnf = normalFormsBuilder.buildMDNF();

			std::string mcnfNum = normalFormsBuilder.buildNumericMCNF();
			std::string mdnfNum = normalFormsBuilder.buildNumericMDNF();

			long long int numForm = 0;

			numForm = normalFormsBuilder.numericFunctionForm();

			std::string mcnfNumExpected = "{8, 9, 11}&";
			std::string mdnfNumExpected = "{0, 1, 2, 3, 4, 5, 6, 7, 10, 12, 13, 14, 15}+";
			long long int numFormExpected = 65327;
			Assert::AreEqual(mcnfNumExpected, mcnfNum);
			Assert::AreEqual(mdnfNumExpected, mdnfNum);
			Assert::AreEqual(numFormExpected, numFormExpected);
		}
		TEST_METHOD(TestSplitExpression) {
			ReducedFormsBuilder build;
			std::string expression = "(A + B + C)";
			std::string expectedExpression = "ABC";
			std::vector<std::string> trueExpression = build.splitExpression(expression);
			std::string trueExpressionString;
			for (size_t i = 0; i < trueExpression.size(); ++i) {
				trueExpressionString += trueExpression[i];
			}
			Assert::AreEqual(expectedExpression, trueExpressionString);
		}

        TEST_METHOD(TestFindUniqueVariables)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> expressions = { "a", "b", "c", "a" };
            auto result = builder.findUniqueVariables(expressions);
            std::vector<std::string> expected = { "a", "b", "c" };
            Assert::AreEqual(expected.size(), result.size());
            Assert::IsTrue(std::is_permutation(expected.begin(), expected.end(), result.begin()));
        }

        TEST_METHOD(TestCountUniqueVariables)
        {

            ReducedFormsBuilder builder;
            std::vector<std::string> expressions = { "a", "b", "c", "a", "d", "e" };
            int count = builder.countUniqueVariables(expressions);
            Assert::AreEqual(5, count);
        }

        TEST_METHOD(TestConvertLogicToNumeric)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> logicStrings = { "!X", "Y", "Z" };
            std::vector<std::string> uniqueVars = { "X", "Y", "Z" };
            std::vector<std::string> expected = { "022", "212", "221" };
            std::vector<std::string> result = builder.convertLogicToNumeric(logicStrings, uniqueVars);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestFindMerges)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> strings = { "010", "011", "001" };
            std::vector<std::string> expected = { "012", "021" };
            std::vector<std::string> result = builder.findMerges(strings, 3);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestNumericStringsToVariables)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> numericStrings = { "122", "220" };
            std::vector<std::string> uniqueVars = { "A", "B", "C" };
            std::vector<std::string> expected = { "A", "!C" };
            std::vector<std::string> result = builder.numericStringsToVariables(numericStrings, uniqueVars);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestIsContained)
        {
            ReducedFormsBuilder builder;
            std::string candidate1 = "!AB";
            std::string target1 = "A!B";
            builder.TDNFCalcTable(candidate1);
            bool result1 = builder.isContained(candidate1, target1);
            Assert::IsFalse(result1);

            std::string candidate2 = "AB";
            std::string target2 = "A!B";
            bool result2 = builder.isContained(candidate2, target2);
            Assert::IsFalse(result2);

            std::string candidate3 = "A";
            std::string target3 = "AB";
            bool result3 = builder.isContained(candidate3, target3);
            Assert::IsTrue(result3);
        }

        TEST_METHOD(TestFindExtraStrings)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> rows = { "!A", "B" };
            std::vector<std::vector<bool>> coverageMatrix = { {false, false}, {false, true} };
            auto extras = builder.findExtraStrings(rows, coverageMatrix);

            std::vector<std::string> expected = { "!A" };
            Assert::IsTrue(extras == expected);
        }

        TEST_METHOD(TestRemoveStrings)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> input = { "!A", "B", "C" };
            std::vector<std::string> toRemove = { "B", "C" };
            auto result = builder.removeStrings(input, toRemove);

            std::vector<std::string> expected = { "!A" };
            Assert::IsTrue(result == expected);
        }
        TEST_METHOD(TestVectorToStringDNF)
        {
            ReducedFormsBuilder builder;
            std::vector<std::string> input = { "A", "B" };
            std::string expected = "(A) + (B)";
            std::string actual = builder.vectorToStringDNF(input);
            Assert::AreEqual(expected, actual);
        }
        TEST_METHOD(TestTDNFTable) {
            ReducedFormsBuilder build;
            Output printer;
            std::string expression = "(A & B) + C";
            printer.printAllInfo(expression);
            std::string mcnf = "(A + B + C) & (A + !B + C) & (!A + B + C)";
            std::vector<std::string> splittedString = build.splitExpression(mcnf);
            int counter = build.countUniqueVariables(splittedString);
            std::vector<std::string> variables = build.findUniqueVariables(splittedString);
            std::vector<std::string> numericString = build.convertLogicToNumeric(splittedString, variables);
            std::vector<std::string> mergedString = build.findMerges(numericString, counter);
            std::vector<std::string> charString = build.numericStringsToVariables(mergedString, variables);
            std::string splittedStringExpected;
            std::string charStringExpected;
            for (size_t i = 0; i < splittedString.size(); ++i) {
                splittedStringExpected += splittedString[i];
            }
            for (size_t i = 0; i < charString.size(); ++i) {
                charStringExpected += charString[i];
            }
            Assert::AreNotEqual(splittedStringExpected, charStringExpected);
        }
	};
}
