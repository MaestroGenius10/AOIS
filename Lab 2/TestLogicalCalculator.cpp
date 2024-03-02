#include "pch.h"
#include "CppUnitTest.h"
#include"..\LogicalCalculator\BooleanExpression.h"
#include"..\LogicalCalculator\InfixToPostfixConverter.h"
#include"..\LogicalCalculator\NormalFormsBuilder.h"
#include"..\LogicalCalculator\Output.h"
#include"..\LogicalCalculator\PostfixEvaluator.h"
#include"..\LogicalCalculator\TruthTableGenerator.h"
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

			std::string mcnfNumExpected = "{2, 4, 6}&";
			std::string mdnfNumExpected = "{1, 3, 5, 7, 8}+";
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

			std::string mcnfNumExpected = "{9, 10, 12}&";
			std::string mdnfNumExpected = "{1, 2, 3, 4, 5, 6, 7, 8, 11, 13, 14, 15, 16}+";
			long long int numFormExpected = 65327;
			Assert::AreEqual(mcnfNumExpected, mcnfNum);
			Assert::AreEqual(mdnfNumExpected, mdnfNum);
			Assert::AreEqual(numFormExpected, numFormExpected);
		}
		TEST_METHOD(TestFumctionOfFiveVars)
		{
			TruthTableGenerator generator;
			std::string expression = "(!(A&B))=(C+(D>E))";
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

			std::string mcnfNumExpected = "{3, 11, 19, 25, 26, 28, 29, 30, 31, 32}&";
			std::string mdnfNumExpected = "{1, 2, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 24, 27}+";
			long long int numFormExpected = 3755990816;
			Assert::AreEqual(mcnfNumExpected, mcnfNum);
			Assert::AreEqual(mdnfNumExpected, mdnfNum);
			Assert::AreEqual(numFormExpected, numFormExpected);
		}
	};
}