#include <iostream>
#include <fstream>
#include <sstream>
#include "Evaluator.h"
#include "Tokenizer.h"

int main()
{
    map<string, double> variables;
    string filename, line;
    cout << "Enter the filename containing expressions (e.g functions.txt): ";
    cin >> filename;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "\033[31mError: File name doesn't exist " << filename << "\033[0m" << endl;
        return 1;
    }
    cout << "\033[32mProcessing expressions from " << filename << "...\033[0m" << endl;
    while (getline(file, line))
    {
        if (line.find_first_not_of("=+-*/^'"
                                   "&<,\\|_.;:>`!~") == string::npos ||
            line.empty())
        {
            continue;
        }
        try
        {
            if (line.find('=') != string::npos)
            {
                Evaluator::processAssignment(line, variables);
            }
            else
            {
                vector<string> tokens = Tokenizer::tokenize(line);
                double result = Evaluator::evaluate(tokens, variables);
                cout << "\033[32mResult: " << result << "\033[0m" << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "\033[31mError: " << e.what() << "\033[0m" << endl;
        }
    }
    file.close();
    return 0;
}