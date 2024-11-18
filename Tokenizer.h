#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string>
#include <algorithm> 
#include <cctype>

using namespace std;

class Tokenizer
{
public:
    static vector<string> tokenize(const string &expression); 
};

#endif