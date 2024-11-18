#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class Tokenizer
{
public:
    static std::vector<std::string> tokenize(const std::string &expression);
};

#endif