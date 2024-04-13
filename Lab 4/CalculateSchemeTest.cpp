#include "pch.h"
#include "CppUnitTest.h"
#include"..\CalculateScheme\FinalFormsBuilder.h"
#include"..\CalculateScheme\ManualTruthTable.h"
#include"..\CalculateScheme\NormalFormsBuilder.h"
#include <algorithm>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculateSchemeTest
{
	TEST_CLASS(CalculateSchemeTest)
	{
	public:
        TEST_METHOD(TestManualInputAndCombinations)
        {
            ManualTruthTable mtt;
            std::vector<std::string> inputData = { "101", "110", "111" };
            std::vector<std::string> names = { "A", "B", "C" };
            mtt.manualInput(inputData, names);
            auto combinations = mtt.getCombinations();
            Assert::AreEqual(size_t(3), combinations.size());
            Assert::IsTrue(combinations[0].at("A"));
            Assert::IsFalse(combinations[0].at("B"));
            Assert::IsTrue(combinations[0].at("C"));
            Assert::IsTrue(combinations[1].at("A"));
            Assert::IsTrue(combinations[1].at("B"));
            Assert::IsFalse(combinations[1].at("C"));
            Assert::IsTrue(combinations[2].at("A"));
            Assert::IsTrue(combinations[2].at("B"));
            Assert::IsTrue(combinations[2].at("C"));
        }

        TEST_METHOD(TestGetResultsForVariable)
        { 
            ManualTruthTable mtt;
            std::vector<std::string> inputData = { "101", "110", "111" };
            std::vector<std::string> names = { "A", "B", "C" };
            mtt.manualInput(inputData, names);
            auto resultsA = mtt.getResultsForVariable("A");
            auto resultsB = mtt.getResultsForVariable("B");
            auto resultsC = mtt.getResultsForVariable("C");
            Assert::AreEqual(size_t(3), resultsA.size());
            Assert::AreEqual(size_t(3), resultsB.size());
            Assert::AreEqual(size_t(3), resultsC.size());
            Assert::IsTrue(resultsA[0]);
            Assert::IsTrue(resultsA[1]);
            Assert::IsTrue(resultsA[2]);
            Assert::IsFalse(resultsB[0]);
            Assert::IsTrue(resultsB[1]);
            Assert::IsTrue(resultsB[2]);
            Assert::IsTrue(resultsC[0]);
            Assert::IsFalse(resultsC[1]);
            Assert::IsTrue(resultsC[2]);
        }
        TEST_METHOD(TestBuildMDNF)
        {
            std::vector<std::map<std::string, bool>> combinations = {
                {{"A", true}, {"B", false}},
                {{"A", false}, {"B", true}},
                {{"A", true}, {"B", true}}
            };
            std::vector<bool> results = { true, false, true };
            std::vector<std::string> variables = { "A", "B" };
            std::string resultVariable = "Result";
            NormalFormsBuilder nfb(combinations, results, variables, resultVariable);
            std::string mdnf = nfb.buildMDNF();
            Assert::AreEqual(std::string("(A & !B) + (A & B)"), mdnf);
        }
        TEST_METHOD(TestSplitExpression) {
            FinalFormsBuilder builder;
            std::string expression = "(A + B + C)";
            std::string expectedExpression = "ABC";
            std::vector<std::string> trueExpression = builder.splitExpression(expression);
            std::string trueExpressionString;
            for (size_t i = 0; i < trueExpression.size(); ++i) {
                trueExpressionString += trueExpression[i];
            }
            Assert::AreEqual(expectedExpression, trueExpressionString);
        }

        TEST_METHOD(TestFindUniqueVariables)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> expressions = { "a", "b", "c", "a" };
            auto result = builder.findUniqueVariables(expressions);
            std::vector<std::string> expected = { "a", "b", "c" };
            Assert::AreEqual(expected.size(), result.size());
            Assert::IsTrue(std::is_permutation(expected.begin(), expected.end(), result.begin()));
        }

        TEST_METHOD(TestCountUniqueVariables)
        {
        
            FinalFormsBuilder builder;
            std::vector<std::string> expressions = { "a", "b", "c", "a", "d", "e" };
            int count = builder.countUniqueVariables(expressions);
            Assert::AreEqual(5, count);
        }
    
        TEST_METHOD(TestConvertLogicToNumeric)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> logicStrings = { "!X", "Y", "Z" };
            std::vector<std::string> uniqueVars = { "X", "Y", "Z" };
            std::vector<std::string> expected = { "022", "212", "221" };
            std::vector<std::string> result = builder.convertLogicToNumeric(logicStrings, uniqueVars);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestFindMerges)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> strings = { "010", "011", "001" };
            std::vector<std::string> expected = { "012", "021"};
            std::vector<std::string> result = builder.findMerges(strings, 3);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestNumericStringsToVariables)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> numericStrings = { "122", "220" };
            std::vector<std::string> uniqueVars = { "A", "B", "C" };
            std::vector<std::string> expected = { "A", "!C" };
            std::vector<std::string> result = builder.numericStringsToVariables(numericStrings, uniqueVars);
            Assert::IsTrue(expected == result);
        }

        TEST_METHOD(TestIsContained)
        {
            FinalFormsBuilder builder;
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
            FinalFormsBuilder builder;
            std::vector<std::string> rows = { "!A", "B" };
            std::vector<std::vector<bool>> coverageMatrix = { {false, false}, {false, true} };
            auto extras = builder.findExtraStrings(rows, coverageMatrix);

            std::vector<std::string> expected = { "!A" };
            Assert::IsTrue(extras == expected); 
        }

        TEST_METHOD(TestRemoveStrings)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> input = { "!A", "B", "C" };
            std::vector<std::string> toRemove = { "B", "C" };
            auto result = builder.removeStrings(input, toRemove);

            std::vector<std::string> expected = { "!A" };
            Assert::IsTrue(result == expected); 
        }
        TEST_METHOD(TestVectorToStringDNF)
        {
            FinalFormsBuilder builder;
            std::vector<std::string> input = { "A", "B" };
            std::string expected = "(A) + (B)";
            std::string actual = builder.vectorToStringDNF(input);
            Assert::AreEqual(expected, actual);
        }
    };
}
