#include "MathOperations.h"

bool MathOperations::isValidOperator(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}
bool MathOperations::isValidFunction(const string &func)
{
    return func == "sin" || func == "cos";
}
double MathOperations::applyOperator(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw runtime_error("Division by zero");
        return a / b;
    case '^':
        return pow(a, b);
    default:
        throw runtime_error("Unknown operator");
    }
}
double MathOperations::applyFunction(const string &func, double value)
{
    if (func == "sin")
    {
        return sin(value);
    }
    else if (func == "cos")
    {
        return cos(value);
    }
    throw runtime_error("Invalid function: " + func);
}