#include "Evaluator.h"
#include "MathOperations.h"
#include "Conversion.h"
#include "Tokenizer.h"
using namespace std;

double Evaluator::evaluate(const vector<string> &tokens, map<string, double> &variables)
{
    stack<double> values;
    stack<string> operators;
    vector<string> subExpressionTokens;
    map<string, int> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const string &token = tokens[i];
        if (token == "-" && (i == 0 || tokens[i - 1] == "(" || MathOperations::isValidOperator(tokens[i - 1][0])))
        {
            if (i + 1 < tokens.size() && (isdigit(tokens[i + 1][0]) || tokens[i + 1][0] == '.'))
            {
                double negativeValue = -Conversion::parseNumber(tokens[i + 1]);
                values.push(negativeValue);
                ++i;
            }
            else
            {
                throw runtime_error("Invalid use of unary minus");
            }
            continue;
        }

        if (isdigit(token[0]) || token[0] == '.' || (token[0] == '0' && token.size() > 1))
        {
            values.push(Conversion::parseNumber(token));
        }

        else if (variables.count(token))
        {
            values.push(variables[token]);
        }
        else if (MathOperations::isValidFunction(token))
        {
            if (i + 1 < tokens.size() && tokens[i + 1] == "(")
            {
                ++i;
                stack<string> subExpression;
                int openParentheses = 1;
                while (i + 1 < tokens.size() && openParentheses > 0)
                {
                    ++i;
                    if (tokens[i] == "(")
                    {
                        ++openParentheses;
                    }
                    else if (tokens[i] == ")")
                    {
                        --openParentheses;
                        if (openParentheses == 0)
                            break;
                    }
                    subExpression.push(tokens[i]);
                }
                if (openParentheses != 0)
                {
                    throw runtime_error("Mismatched parentheses");
                }
                while (!subExpression.empty())
                {
                    subExpressionTokens.insert(subExpressionTokens.begin(), subExpression.top());
                    subExpression.pop();
                }
                double argumentValue = evaluate(subExpressionTokens, variables);
                values.push(MathOperations::applyFunction(token, argumentValue));
            }
            else
            {
                throw runtime_error("Enclosed in parentheses: " + token);
            }
        }
        else if (token == "(")
        {
            operators.push(token);
        }
        else if (token == ")")
        {
            while (!operators.empty() && operators.top() != "(")
            {
                string op = operators.top();
                operators.pop();
                if (MathOperations::isValidFunction(op))
                {
                    double value = values.top();
                    values.pop();
                    values.push(MathOperations::applyFunction(op, value));
                }
                else
                {
                    double b = values.top();
                    values.pop();
                    double a = values.top();
                    values.pop();
                    values.push(MathOperations::applyOperator(a, b, op[0]));
                }
            }
            if (!operators.empty() && operators.top() == "(")
            {
                operators.pop();
            }
        }
        else if (MathOperations::isValidOperator(token[0]))
        {
            while (!operators.empty() && operators.top() != "(" && precedence[operators.top()] >= precedence[token])
            {
                string op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(MathOperations::applyOperator(a, b, op[0]));
            }
            operators.push(token);
        }
        else
        {
            throw runtime_error("Invalid operator or function: " + token);
        }
    }
    while (!operators.empty())
    {
        string op = operators.top();
        operators.pop();
        if (MathOperations::isValidFunction(op))
        {
            double value = values.top();
            values.pop();
            values.push(MathOperations::applyFunction(op, value));
        }
        else
        {
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            values.push(MathOperations::applyOperator(a, b, op[0]));
        }
    }
    if (values.size() != 1)
    {
        throw runtime_error("Error in evaluation");
    }
    return values.top();
}
void Evaluator::processAssignment(const string &line, map<string, double> &variables)
{
    size_t equalsPos = line.find('=');
    if (equalsPos == string::npos)
    {
        throw runtime_error("Invalid assignment: " + line);
    }
    string variable = line.substr(0, equalsPos);
    string valueStr = line.substr(equalsPos + 1);
    variable.erase(remove(variable.begin(), variable.end(), ' '), variable.end());
    valueStr.erase(remove(valueStr.begin(), valueStr.end(), ' '), valueStr.end());
    vector<string> tokens = Tokenizer::tokenize(valueStr);
    double value = Evaluator::evaluate(tokens, variables);
    variables[variable] = value;
}