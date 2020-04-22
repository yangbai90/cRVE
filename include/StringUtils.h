#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

string StrToLower(string instr);
string StrToUpper(string instr);

// for string to number convert
vector<double> SplitStrNum(string &instr);