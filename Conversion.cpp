#include "Conversion.h"
using namespace std;

double Conversion::parseNumber(const string &s)
{
    regex hexPattern(R"(^0x[0-9a-fA-F]+$)");
    regex binPattern(R"(^[01]+b$)");
    regex decPattern(R"(^[0-9]*\.?[0-9]+$)");
    if (regex_match(s, hexPattern))
    {
        return stoll(s.substr(2), nullptr, 16);
    }
    else if (regex_match(s, binPattern))
    {
        return stoll(s.substr(0, s.length() - 1), nullptr, 2);
    }
    else if (regex_match(s, decPattern))
    {
        return stod(s);
    }
    else
    {
        throw invalid_argument("Invalid number format: " + s);
    }
}