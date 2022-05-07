#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;
typedef string& sLink;
smatch RegexFind(string s, string elem) {
	smatch m;
	regex rgxx = regex{ elem };
	regex_search(s, m, rgxx);
	return m;
}
vector<string> Split(string s, string elem) {
	regex rgxx = regex{ elem };
	sregex_token_iterator splitter{ s.begin(), s.end(), rgxx, -1 };
	vector<string> vect{ splitter, {} };
	return vect;
}



void GlobalReplace(sLink equation) {
	equation = regex_replace(equation, regex{ ":" }, "/");
	equation = regex_replace(equation, regex{ "sin" }, "s");
	equation = regex_replace(equation, regex{ "cos" }, "c");
	equation = regex_replace(equation, regex{ "tg" }, "t");
	equation = regex_replace(equation, regex{ "ln" }, "n");
	equation = regex_replace(equation, regex{ "lb" }, "b");
	equation = regex_replace(equation, regex{ "sqrt" }, "r");
	equation = regex_replace(equation, regex{ "pi" }, "p");
}
// warning with error + return
	/* READ ME
		maybe do a message with position of unclosed brackets
	*/
int NoIncorrectSymbols(sLink equation, bool needRemove) {
	string pattern = "[^0-9-+*/^()sctnbrep]";
	smatch sm = RegexFind(equation, pattern);
	if (needRemove) 
		equation = regex_replace(equation, regex{pattern}, "");
	return sm.empty();
}
int EqualBrackets(sLink equation) { 
	int cnt = 0;
	for (int i = 0; i < equation.size(); i++) {
		if (equation[i] == '(') cnt++;
		if (equation[i] == ')') cnt--;
	}
	return cnt == 0;
}
int SignsCorrect(sLink equation) {
	string pattern; smatch sm;
	// (x+)*y
	pattern = "[-+*/^])";
	sm = RegexFind(equation, pattern);
	if (!sm.empty()) return 0;
	// (+x)-y
	pattern = "([-+*/^]";
	sm = RegexFind(equation, pattern);
	if (!sm.empty()) return 0;
	// following signs
	pattern = "[-+*/^]{2,}";
	sm = RegexFind(equation, pattern); 
	return sm.empty();
}
int ArgumentsExist(sLink equation) { 
	string pattern; smatch sm; 
	// sin^) was in SingsCorrect();
	// sin^+ was in SingsCorrect();
	// sin^( or sin^3 or sin^ln.. is ok 
	// so here only case sin3 or sinln or sin+
	pattern = "[sctnbr][^(^]";
	sm = RegexFind(equation, pattern); 
	return sm.empty();
}

int NoDividingByZero(sLink equation) {
	// check x/ln(1)
	// check x/lb(1)
	// check x/0
	// check x/sin(k*pi)
	// check x/cos(k*pi/2)
	return 1;
}
int ArgumentsCorrect(sLink equation) {
	// positive args in sqrt 
	// arg > 0 in ln, lb, 
	// tg with args != pi*k/2

	// do it after calc args in func, it's easier
	return 1;
}


// hard thing is ln(ln(ln(2))) or something like that
int main() {
	string equation = "5 + sin(3)";
	string equationSaver = equation;
	GlobalReplace(equation);

	cout << equation << "\n";
	cout << ArgumentsExist(equation) << "\n";

	system("pause");
}