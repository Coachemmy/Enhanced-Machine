#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <map>
#include <stdexcept>

using namespace std;

class Evaluator
{
public:
    static double evaluate(const vector<string> &tokens, map<string, double>& variables);
    static void processAssignment(const string &line, map<string, double> &variables); 
};

#endif
