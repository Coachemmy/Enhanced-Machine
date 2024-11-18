#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H
#include <cmath>
#include <stdexcept>
#include <string>
#include <regex>

using namespace std;

class MathOperations
{
public:    
    static double applyOperator(double a, double b, char op);
    static double applyFunction(const string &func, double value);
    static bool isValidOperator(char op);
    static bool isValidFunction(const string &func);
};

#endif