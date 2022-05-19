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
using namespace std;

typedef string& sLink;
typedef string* sPtr;
int RegexFind(string s, string pattern);
void Replace(sLink s, string pattern, string replacer);
vector<string> SaveSplit(string str, string pattern);
vector<string> Split(string str, string pattern);

int Quit();


/*
	string a = "a";
	double v = 1.123123123123;
	std::ostringstream str;
	str << fixed;
	str << setprecision(14);
	str << v;
	std::string str2 = str.str();
	cout << (a + str2) << "\n";
*/
#endif
