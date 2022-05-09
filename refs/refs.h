#ifndef REFERENCES_H
#define REFERENCES_H
#include <iostream>
#include <cmath>
#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>
using namespace std;

const double deg = 3.1415926535 / 180.0;
typedef string& sLink;
typedef string* sPtr;
int RegexFind(string s, string pattern) {
	smatch m;
	regex rgxx(pattern);
	regex_search(s, m, rgxx);
	return !m.empty();
}
void Replace(sLink s, string pattern, string replacer) {
	s = regex_replace(s, regex{ pattern }, replacer);
}


#endif