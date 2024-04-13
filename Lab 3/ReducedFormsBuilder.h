#pragma once
#include<vector>
#include<map>
#include<string>
#include<set>
class ReducedFormsBuilder {
public:
	std::vector<std::string> splitExpression(std::string& expression);
	std::vector<std::string> findUniqueVariables(std::vector<std::string>& expressions);
	int countUniqueVariables(std::vector<std::string>& expressions);
	std::vector<std::string> convertLogicToNumeric
	(std::vector<std::string>& logicStrings, std::vector<std::string>& uniqueVars);
	bool canMerge(std::string& a,  std::string& b, int N);
	std::string mergeStrings(std::string& a, std::string& b, int N);
	std::vector<std::string> findMerges(std::vector<std::string>& strings, int N);
	void TDNFCalcTable(std::string& input);
	void TCNFCalcTable(std::string& input);
	std::vector<std::string> numericStringsToVariables
	(std::vector<std::string>& numericStrings,  std::vector<std::string>& uniqueVariables);
	bool isContained(std::string& candidate, std::string& target);
	std::vector<std::vector<bool>> buildCoverageMatrix
	(std::vector<std::string>& before,  std::vector<std::string>& after);
	void displayTable
	(std::vector<std::string>& before, std::vector<std::string>& after,  std::vector<std::vector<bool>>& coverageMatrix);
	std::vector<std::string> findExtraStrings(std::vector<std::string>& after,  std::vector<std::vector<bool>>& coverageMatrix);
	std::vector<std::string>removeStrings(std::vector<std::string>& input, std::vector<std::string>& toRemove);

	std::vector<std::string> transformExpressionsDNF(const std::vector<std::string>& expressions);
	std::vector<std::string> transformExpressionsCNF(const std::vector<std::string>& expressions);
	std::vector<std::string> substituteValuesForAllExpressions
	(const std::vector<std::string>& expressions, const std::vector<std::string>& truthValues);
	std::vector<std::string> findRedundantStringsDNF
	(const std::vector<std::string>& originalStrings, const std::vector<std::string>& truthStrings);
	std::vector<std::string> findRedundantStringsCNF
	(const std::vector<std::string>& originalStrings, const std::vector<std::string>& truthStrings);

	std::string substituteValues(const std::string& expression, const std::string& truthSet);

	void TCNFCalc(std::string& input);
	void TDNFCalc(std::string& input);
	std::string vectorToStringDNF(std::vector<std::string>& vec);
	std::string vectorToStringCNF(std::vector<std::string>& vec);
private:
	
};