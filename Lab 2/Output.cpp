#include"Output.h"
void Output::printAllInfo() {
	setlocale(LC_ALL, "ru");
	std::string expression;
	std::cout << "Введите логическое выражение: "; std::cin >> expression;
	std::cout << "Введено выражение: " << expression << std::endl;

	TruthTableGenerator generator;
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

	std::cout << "Совершенная конъюктивная нормальная форма (СКНФ): " << mcnf << std::endl;
	std::cout << "Совершенная дизъюктивная нормальная форма (СДНФ): " << mdnf << std::endl;

	std::cout << "СКНФ в численной форме: " << mcnfNum << std::endl;
	std::cout << "СДНФ в численной форме: " << mdnfNum << std::endl;

	std::cout << "Логическая функция в численной форме: " << numForm << std::endl;
}
