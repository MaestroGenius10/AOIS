#include"IEEE754.h"
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

std::string IEEE754::floatToIEEE754(float value) {
    int sign = value < 0 ? 1 : 0;
    value = fabs(value);

    int exponent = 0;
    while (value >= 2.0) {
        value /= 2.0;
        ++exponent;
    }
    while (value < 1.0 && exponent > -126) {
        value *= 2.0;
        --exponent;
    }
    exponent += 127;

    value -= 1.0;
    std::string mantissa = "";
    for (int i = 0; i < 23; ++i) {
        value *= 2;
        if (value >= 1.0) {
            mantissa += "1";
            value -= 1.0;
        }
        else {
            mantissa += "0";
        }
    }

    std::string exponentBinary = "";
    for (int i = 0; i < 8; ++i) {
        exponentBinary = std::to_string(exponent % 2) + exponentBinary;
        exponent /= 2;
    }

    return std::to_string(sign) + exponentBinary + mantissa;
}

std::string IEEE754::addIEEE754(std::string first, std::string second) {
    int exponentFirst = std::stoi(first.substr(1, 8), nullptr, 2);
    int exponentSecond = std::stoi(second.substr(1, 8), nullptr, 2);
    std::string mantissaFirst = "1" + first.substr(9);
    std::string mantissaSecond = "1" + second.substr(9);

    while (exponentFirst < exponentSecond) {
        mantissaFirst = "0" + mantissaFirst.substr(0, mantissaFirst.length() - 1);
        exponentFirst++;
    }
    while (exponentSecond < exponentFirst) {
        mantissaSecond = "0" + mantissaSecond.substr(0, mantissaSecond.length() - 1);
        exponentSecond++;
    }

    int carry = 0;
    std::string sumMantissa = "";
    for (int i = 23; i >= 0; --i) {
        int bitFirst = mantissaFirst[i] - '0';
        int bitSecond = mantissaSecond[i] - '0';
        int sum = bitFirst + bitSecond + carry;
        sumMantissa = std::to_string(sum % 2) + sumMantissa;
        carry = sum / 2;
    }

    if (carry) {
        sumMantissa = "1" + sumMantissa.substr(0, sumMantissa.length() - 1);
        exponentFirst++;
    }

    std::string resultExponent = "";
    for (int i = 0; i < 8; ++i) {
        resultExponent = std::to_string(exponentFirst % 2) + resultExponent;
        exponentFirst /= 2;
    }
    std::string result = first.substr(0, 1) + resultExponent + sumMantissa.substr(1);

    return result;
}

float IEEE754::IEEE754ToFloat(std::string binary) {
    if (binary.length() != 32) return 0;

    int sign = binary[0] == '1' ? -1 : 1;
    int exponent = std::stoi(binary.substr(1, 8), nullptr, 2) - 127;
    std::string mantissaBinary = binary.substr(9);

    float mantissa = 1.0;
    for (int i = 0; i < 23; ++i) {
        if (mantissaBinary[i] == '1') {
            mantissa += std::pow(2, -i - 1);
        }
    }

    return sign * mantissa * std::pow(2, exponent);
}