#include"Output.h"
void Output::printAllInfo() {
	setlocale(LC_ALL, "ru");
	std::string expression;
	std::cout << "������� ���������� ���������: "; std::cin >> expression;
	std::cout << "������� ���������: " << expression << std::endl;

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
}
