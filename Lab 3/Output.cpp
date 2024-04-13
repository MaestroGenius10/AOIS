#include"Output.h"
#include"KarnaughMapCNF.h"
#include"KarnaughMapDNF.h"
#include"ReducedFormsBuilder.h"

std::string Output::userInput() {
	setlocale(LC_ALL, "ru");
	std::string expression;
	std::cout << "Введите логическое выражение: "; std::cin >> expression;
	std::cout << "Введено выражение: " << expression << std::endl;
	return expression;
}

void Output::printAllInfo(std::string& expression) {
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
	std::cout << "Минимизация КНФ:" << std::endl;
	KarnaughMapCNF kMapCNF(combinations, results);
	kMapCNF.generateMap();
	std::cout << "Карта Карно для выражения: " << expression << ":" << std::endl;
	kMapCNF.printMap();
	std::cout << "\nПоиск регионов 2^n:" << std::endl;
	kMapCNF.findAllRegions();
	kMapCNF.findAndSaveMaxRegions();
	kMapCNF.printMaxRegions();
	kMapCNF.convertMaxRegionsToExpressions();
	std::cout << "Минимизация ДНФ:" << std::endl;
	KarnaughMapDNF kMapDNF(combinations, results);
	kMapDNF.generateMap();
	std::cout << "\nПоиск регионов 2^n:" << std::endl;
	kMapDNF.findAllRegions();
	kMapDNF.findAndSaveMaxRegions();
	kMapDNF.printMaxRegions();
	kMapDNF.convertMaxRegionsToExpressions();

	std::cout << "Минимизация КНФ.Рассчётно-табличный метод:" << std::endl;
	ReducedFormsBuilder build;
	build.TCNFCalcTable(mcnf);
	std::cout << "Минимизация КНФ.Рассчётно-табличный метод:" << std::endl;
	build.TDNFCalcTable(mdnf);

	std::cout << "Минимизация КНФ.Рассчётный метод:" << std::endl;
	build.TCNFCalc(mcnf);
	std::cout << "Минимизация ДНФ.Рассчётный метод:" << std::endl;
	build.TDNFCalc(mdnf);
}
