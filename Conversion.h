#ifndef CONVERSION_H
#define CONVERSION_H
#include <cctype>
#include <regex>
#include <stdexcept>
#include <string>

class Conversion
{
public:
    static double parseNumber(const std::string& s);
};

#endif