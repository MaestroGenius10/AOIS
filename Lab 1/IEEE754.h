#pragma once
#include<string>
class IEEE754 {
public:
	std::string floatToIEEE754(float value);
	std::string addIEEE754(std::string first, std::string second);
	float IEEE754ToFloat(std::string binary);
private:

};
