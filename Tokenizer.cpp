#include "tokenizer.h"
#include "mathOperations.h"

vector<string> Tokenizer::tokenize(const string &expression)
{
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < expression.size(); ++i)
    {
        char ch = expression[i];
        if (isspace(ch))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        }
        else if (isalpha(ch))
        {
            token += ch;
            while (i + 1 < expression.size() && isalpha(expression[i + 1]))
            {
                token += expression[++i];
            }
            if (MathOperations::isValidFunction(token))
            {
                tokens.push_back(token);
                token.clear();
                continue;
            }
        }
        else if (isdigit(ch) || ch == '.')
        {
            token += ch;
            while (i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.'))
            {
                token += expression[++i];
            }
        }
        else if (ch == '(' || ch == ')')
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        }
        else if (ch == '0' && (i + 1 < expression.size() && (expression[i + 1] == 'x' || expression[i + 1] == 'X'))) // Hexadecimal
        {
            token += ch;
            token += expression[++i];
            while (i + 1 < expression.size() && isxdigit(expression[i + 1]))
            {
                token += expression[++i];
            }
            tokens.push_back(token);
            token.clear();
        }
        else if (ch == '1' || ch == '0')
        {
            token += ch;
            while (i + 1 < expression.size() && (expression[i + 1] == '1' || expression[i + 1] == '0'))
            {
                token += expression[++i];
            }
            if (i + 1 < expression.size() && expression[i + 1] == 'b')
            {
                token += expression[++i];
                tokens.push_back(token);
                token.clear();
            }
            else
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
        {
            token += ch;
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
    for (string &tok : tokens)
    {
        if (tok.substr(0, 2) == "0x" || tok.substr(0, 2) == "0X")
        {
            tok = to_string(stoi(tok, nullptr, 16));
        }
        else if (tok.size() > 1 && tok.back() == 'b')
        {
            tok = to_string(stoi(tok.substr(0, tok.size() - 1), nullptr, 2));
        }
    }
    return tokens;
}