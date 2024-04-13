#include"Output.h"
#include"KarnaughMapCNF.h"
#include"KarnaughMapDNF.h"
#include"ReducedFormsBuilder.h"

std::string Output::userInput() {
	setlocale(LC_ALL, "ru");
	std::string expression;
	std::cout << "������� ���������� ���������: "; std::cin >> expression;
	std::cout << "������� ���������: " << expression << std::endl;
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
	std::cout << "����������� ������������ ���������� ����� (����): " << mcnf << std::endl;
	std::cout << "����������� ������������ ���������� ����� (����): " << mdnf << std::endl;
	std::cout << "���� � ��������� �����: " << mcnfNum << std::endl;
	std::cout << "���� � ��������� �����: " << mdnfNum << std::endl;
	std::cout << "���������� ������� � ��������� �����: " << numForm << std::endl;
	std::cout << "����������� ���:" << std::endl;
	KarnaughMapCNF kMapCNF(combinations, results);
	kMapCNF.generateMap();
	std::cout << "����� ����� ��� ���������: " << expression << ":" << std::endl;
	kMapCNF.printMap();
	std::cout << "\n����� �������� 2^n:" << std::endl;
	kMapCNF.findAllRegions();
	kMapCNF.findAndSaveMaxRegions();
	kMapCNF.printMaxRegions();
	kMapCNF.convertMaxRegionsToExpressions();
	std::cout << "����������� ���:" << std::endl;
	KarnaughMapDNF kMapDNF(combinations, results);
	kMapDNF.generateMap();
	std::cout << "\n����� �������� 2^n:" << std::endl;
	kMapDNF.findAllRegions();
	kMapDNF.findAndSaveMaxRegions();
	kMapDNF.printMaxRegions();
	kMapDNF.convertMaxRegionsToExpressions();

	std::cout << "����������� ���.���������-��������� �����:" << std::endl;
	ReducedFormsBuilder build;
	build.TCNFCalcTable(mcnf);
	std::cout << "����������� ���.���������-��������� �����:" << std::endl;
	build.TDNFCalcTable(mdnf);

	std::cout << "����������� ���.���������� �����:" << std::endl;
	build.TCNFCalc(mcnf);
	std::cout << "����������� ���.���������� �����:" << std::endl;
	build.TDNFCalc(mdnf);
}
