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
int RegexFind(string s, string pattern) {
	smatch m;
	regex rgxx(pattern);
	regex_search(s, m, rgxx);
	return !m.empty();
}
void Replace(sLink s, string pattern, string replacer) {
	s = regex_replace(s, regex{ pattern }, replacer);
}
vector<string> SaveSplit(string str, string pattern) {
	smatch m; 
	Replace(pattern, "\\\\", "\\\\"); 
	Replace(pattern, "\\*", "\\*");
	Replace(pattern, "\\+", "\\+");
	Replace(pattern, "\\-", "\\-");
	Replace(pattern, "\\^", "\\^"); 
	Replace(pattern, "\\(", "\\(");
	Replace(pattern, "\\)", "\\)");
	regex rgx = regex{ pattern };
	sregex_token_iterator splitter{ str.begin(), str.end(), rgx, -1 };
	vector<string> strArr{ splitter, {} }; 
	int vecSize = strArr.size();
	for (int i = 0; i < vecSize; i++) {
		regex_search(str, m, rgx);
		strArr.insert(strArr.begin() + i * 2 + 1, m.str());
		str = regex_replace(str, rgx, "", regex_constants::format_first_only);
	}
	for (int i = 0; i < strArr.size(); i++)
		if (strArr[i] == "") strArr.erase(strArr.begin() + i);
	return strArr;
}
vector<string> Split(string str, string pattern) {
	regex rgx = regex{ pattern };
	sregex_token_iterator splitter{ str.begin(), str.end(), rgx, -1 };
	vector<string> strArr{ splitter, {} };
	return strArr;
}

int Quit() {
	printf("\n\n  "); system("pause"); return 0;
}
#endif