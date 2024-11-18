#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H
#include <cmath>
#include <stdexcept>
#include <string>
#include <regex>

class MathOperations
{
public:    
    static double applyOperator(double a, double b, char op);
    static double applyFunction(const std::string &func, double value);
    static bool isValidOperator(char op);
    static bool isValidFunction(const std::string &func);
};

#endif