#ifndef CONVERSION_H
#define CONVERSION_H
#include <cctype>
#include <regex>
#include <stdexcept>
#include <string>

//using namespace std;

class Conversion
{
public:
    static double parseNumber(const std::string& s);
};

#endif