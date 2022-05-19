#ifndef REFS_H
#define REFS_H

#include <iostream>
#include <cmath>
#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

typedef string& sLink;
typedef string* sPtr;
int RegexFind(string s, string pattern);
void Replace(sLink s, string pattern, string replacer);
vector<string> SaveSplit(string str, string pattern);
vector<string> Split(string str, string pattern);

int Quit();

#endif