#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <regex>
#include <iterator>
#include <numeric>
#include <limits>

using std::endl;
using std::string;
using std::map;
using std::queue;
using std::vector;
using std::regex;
using std::smatch;
using std::pair;

enum Pattern
{
    assignment,
    print,
    invalid
};

enum ErrorMsg
{
    vaild,
    badSyntax,
    undefined
};

bool is_number(const std::string &s)
{
    std::regex number_regex("\\d+");
    return std::regex_match(s, number_regex);
}

bool is_variable(const string &s)
{
    std::regex variable_regex("[xyz]");
    return std::regex_match(s, variable_regex);
}

vector<string> splitExpression (const string &expression)
{
    vector<string> result;
    string s(expression);
    int start = int(s.size() - 1);
    for (int i = int(s.size() - 1); i >= 0; i--) {
        if (s[i] == '+' || s[i] == '-') {
            result.push_back(s.substr(i, start - i + 1));
            start = i - 1;
            s = s.substr(0, i);
        }
    }
    result.push_back("+" + s);
    
    return result;
}


pair<vector<string>, string> splitAssignment(string &s, regex r)
{
    vector<string> splits;
    smatch m;
    string splitBy;
    
    while (regex_search(s, m, r)) {
        int split_on = int(m.position());
        splits.push_back(s.substr(0, split_on));
        splitBy = s.substr(split_on, 1);
        s = s.substr(split_on + m.length());
        break;
    }
    
    if(!s.empty()) {
        splits.push_back(s);
    }
    
    return make_pair(splits, splitBy);
}


int getResultFromTerm (const string &expression, map<string, int> &variables)
{
    int result;
    
    if (is_number(expression)) {
        result = std::stoi(expression);
    }
    else {
        result = variables[expression];
    }
    
    return result;
}

ErrorMsg validateSplit(vector<string>& splittedExpression, map<string, int>& variables, int &result, queue<string> &messageQueue)
{
    ErrorMsg msg(vaild);
    
    regex term_regex("[\\+-][xyz]");
    for (int i = 0; i < splittedExpression.size() && msg == vaild; ++i) {
        if (std::regex_match(splittedExpression[i], term_regex)) {
            string var(splittedExpression[i]);
            if (variables.count(var.substr(1, 1)) == 0) {
                messageQueue.push(var.substr(1, 1) + " is undefined");
                msg = undefined;
                result = std::numeric_limits<int>::max();
            }
            else {
                if (var.substr(0, 1) == "+") {
                    result += getResultFromTerm(var.substr(1, 1), variables);
                }
                else {
                    result -= getResultFromTerm(var.substr(1, 1), variables);
                }
            }
        }
        else {
            messageQueue.push("Bad syntax");
            msg = badSyntax;
            result = std::numeric_limits<int>::max();
        }
    }
    
    return msg;
}

int evaluateExpression(string &expression, map<string, int> &variables, queue<string> &messageQueue)
{
    int result = 0;
    regex term_regex("[0-9xyz]");
    if (std::regex_match(expression, term_regex)) {
        // It is a term
        if (is_number(expression) || (is_variable(expression) && variables.count(expression) > 0)){
            result = getResultFromTerm(expression, variables);
        }
        else {
            messageQueue.push(expression + " is undefined");
            result = +std::numeric_limits<int>::max();
        }
    }
    else {
        vector<string> splitted = splitExpression(expression);
        validateSplit(splitted, variables, result, messageQueue);
    }
        
    return result;
}

Pattern matchPatterns(const string &s)
{
    Pattern result;
    std::regex patternOfPrint("PRINT\\([xyz]\\)");
    std::regex patternOfAssignment("[xyz]=");

    if (std::regex_search(s, patternOfPrint)) {
        result = print;
    }
    else if (std::regex_search(s, patternOfAssignment)) {
        result = assignment;
    }
    else {
        result = invalid;
    }
    
    return result;
}

string removeSpace(string &s)
{
    string result = "";
    for(size_t i = 0; i < s.size(); ++i) {
        if (s[i] != ' ') {
            result += s[i];
        }
    }
    return result;
}

int main(int argc, const char * argv[])
{
    std::ifstream fin("bnf.in");
    if (fin.good()) {
        std::ofstream fout("bnf.out");
        string line;
        getline(fin, line);
        map<string, int> variables;
        
        while (line != "HALT") {
            string ori(line);
            size_t statementLength = line.size();
            line = removeSpace(line);
            queue<string> message;
            Pattern pattern = matchPatterns(line);
            
            if (pattern == invalid) {
                message.push("Bad syntax");
            }
            else if (pattern == print) {
                string var = line.substr(6, 1);
                if (variables.count(var) == 0) {
                    message.push(var + " is undefined");
                }
                else {
                    message.push(std::to_string(variables[var]));
                }
            }
            else {
                // It is an assignment pattern
                regex equal("=");
                vector<string> split_into_expression = splitAssignment(line, equal).first;
                string var = split_into_expression[0];
                string expression = split_into_expression[1];
                
                int result = evaluateExpression(expression, variables, message);
                if (result != std::numeric_limits<int>::max()) {
                    if (variables.count(var) == 0) {
                        variables.insert(std::make_pair(var, result));
                    }
                    else {
                        variables[var] = result;
                    }
                }
            }
            
            if (message.size() != 0) {
                fout << ori << std::internal << std::setw(31 - statementLength + message.front().size()) << message.front() << endl;;
                std::cout << ori << std::internal << std::setw(31 - statementLength + message.front().size()) << message.front() << endl;
                message.pop();
            }
            else {
                fout << ori << endl;
                std::cout << ori << endl;
            }
            
            getline(fin, line);
        }
    }
}
