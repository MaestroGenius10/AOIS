#pragma once
#include <vector>
#include <map>
#include <set>
#include<string>
class KarnaughMapDNF {
private:
    std::vector<std::map<char, bool>> combinations;
    std::vector<bool> results;
    std::vector<std::vector<bool>> map;
    std::set<std::set<std::pair<int, int>>> uniqueRegions;
    std::vector<std::set<std::pair<int, int>>> maxRegions;
    std::vector<std::set<std::pair<int, int>>> unincludedRegions;
    std::vector<std::set<std::pair<int, int>>> substringRegion;
    int variablesCount = 0;
    std::string grayCodeToString(int code, int length);
    void initializeMap(int varCount);
    void fillMap();
    void findRegions1x1();
    void findRegions1x2();
    void findRegions2x1();
    void findRegions2x2();
    void findRegions1x4();
    void findRegions4x1();
    void findRegions2x4();
    void findRegions4x2();
    void addRegion(std::set<std::pair<int, int>> region);
    void filterAndPrintUniqueRegions();
    std::vector<int> generateGrayCode(int bits);
    int grayCodeToBinary(int gray);
    int grayCodeToIndex(int gray, const std::vector<int>& grayCodes);
    void printRegion(const std::set<std::pair<int, int>>& region);
    std::vector<std::string> regionToExpression(const std::set<std::pair<int, int>>& region, int varCount);
    void analyzeChanges(const std::vector<bool>& changes, int varCount, bool isRow, std::vector<bool>& varChange);
    bool determineState(const std::pair<int, int>& cell, int varIndex, int varCount);
    void markUnincluded1x1Regions();
    void findMaxRegionsContainingSingleCells();
public:
    KarnaughMapDNF(const std::vector<std::map<char, bool>>& combinations, const std::vector<bool>& results);
    void generateMap();
    void printMap();
    void findAllRegions();
    void findAndSaveMaxRegions();
    void printMaxRegions();
    void convertMaxRegionsToExpressions();
    std::vector<std::string> variables = { "A", "B", "C", "D", "E" };
    
};
