#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <map>
#include <stdexcept>

class Evaluator
{
public:
    static double evaluate(const std::vector<std::string> &tokens, std::map<std::string, double>& variables);
    static void processAssignment(const std::string &line, std::map<std::string, double> &variables); 
};

#endif
