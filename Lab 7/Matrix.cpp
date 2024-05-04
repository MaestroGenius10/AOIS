#include "Matrix.h"
#include <bitset>
#include <stdexcept>

Matrix::Matrix() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void Matrix::printMatrix() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::set(int x, int y, int value) {
    matrix[x][y] = value;
}

int Matrix::get(int x, int y) const {
    return matrix[x][y];
}

std::string Matrix::getWord(int index) {
    std::string word;
    for (int i = 0; i < col; ++i) {
        int x = (index + i) % col;
        word += std::to_string(matrix[x][index]);
    }
    return word;
}

std::string Matrix::getAddressRow(int index) {
    std::string row;
    for (int i = 0; i < col; ++i) {
        int rowIndex = (index + i) % col;
        row += std::to_string(matrix[rowIndex][i]);
    }
    return row;
}

void Matrix::printWord(int index) {
    std::cout << "Word " << index << ": " << getWord(index) << std::endl;
}

void Matrix::printAddressRow(int index) {
    std::cout << "Address Row " << index << ": " << getAddressRow(index) << std::endl;
}

void Matrix::setColumnWord(const std::string& word, int col) {
    int len = word.length();
    for (int i = 0; i < len; ++i) {
        int rowIndex = (col + i) % row;
        int value = word[i] - '0';
        matrix[rowIndex][col] = value;
    }
}

std::string Matrix::constZero(const std::string& word) {
    return std::string(16, '0');
}

std::string Matrix::constOne(const std::string& word) {
    return std::string(16, '1');
}

std::string Matrix::repeatAndNegSecond(const std::string& firstArg, const std::string& secArg) {
    std::string negatedSecArg;
    negatedSecArg.reserve(secArg.size());
    for (char ch : secArg) {
        negatedSecArg.push_back(ch == '0' ? '1' : '0');
    }
    return negatedSecArg;
}

std::vector<std::string> Matrix::findWordsByPrefix(const std::string& key) {
    std::vector<std::string> matchedWords;
    for (int i = 0; i < col; ++i) {
        std::string word = getWord(i);
        if (word.substr(0, key.size()) == key) {
            matchedWords.push_back(word);
        }
    }
    return matchedWords;
}

std::vector<std::string> Matrix::processWords(const std::vector<std::string>& words) {
    std::vector<std::string> processedWords;
    for (const std::string& word : words) {
        std::bitset<4> A(word.substr(3, 4));
        std::bitset<4> B(word.substr(7, 4));
        std::bitset<5> S(A.to_ulong() + B.to_ulong());

        std::string newWord = word.substr(0, 11) + S.to_string().substr(0, 5);
        processedWords.push_back(newWord);
    }
    return processedWords;
}

void Matrix::setWordsInColumns(const std::vector<std::string>& words) {
    for (size_t i = 0; i < words.size(); ++i) {
        int startCol = i;
        const std::string& word = words[i];
        for (size_t j = 0; j < word.length(); ++j) {
            int rowIndex = (i + j) % row;
            matrix[rowIndex][startCol] = word[j] - '0';
        }
    }
}

std::vector<std::string> Matrix::findMaxClose(const std::string& key) {
    int maxMatches = 0;
    std::vector<std::string> maxWords;
    for (int i = 0; i < col; ++i) {
        std::string word = getWord(i);
        int matches = 0;
        for (size_t j = 0; j < word.size() && j < key.size(); ++j) {
            bool a = key[j] == '1';
            bool S = word[j] == '1';

            bool g = !a && S;
            bool l = a && !S;

            if (g == l) {
                matches++;
            }
        }

        if (matches > maxMatches) {
            maxMatches = matches;
            maxWords.clear();
            maxWords.push_back(word);
        }
        else if (matches == maxMatches) {
            maxWords.push_back(word);
        }
    }

    return maxWords;
}