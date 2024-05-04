#pragma once
#include <iostream>
#include <vector>
#include <string>

class Matrix {
private:
    static const int row = 16;
    static const int col = 16;
    int matrix[row][col];

public:
    Matrix();
    void printMatrix() const;
    void set(int x, int y, int value);
    int get(int x, int y) const;
    std::string getWord(int index);
    std::string getAddressRow(int index);
    void printWord(int index);
    void printAddressRow(int index);
    void setColumnWord(const std::string& word, int col);
    std::string constZero(const std::string& word);
    std::string constOne(const std::string& word);
    std::string repeatAndNegSecond(const std::string& firstArg, const std::string& secArg);
    std::vector<std::string> findWordsByPrefix(const std::string& key);
    std::vector<std::string> processWords(const std::vector<std::string>& words);
    void setWordsInColumns(const std::vector<std::string>& words);
    std::vector<std::string> findMaxClose(const std::string& key);
};

