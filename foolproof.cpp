#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;
typedef string& sLink;
smatch RegexFind(string s, string elem) {
	smatch m;
	regex rgxx (elem); 
	regex_search(s, m, rgxx);
	cout << &m << "\n";
	return m;
}
vector<string> Split(string s, string elem) {
	regex rgxx = regex{ elem };
	sregex_token_iterator splitter{ s.begin(), s.end(), rgxx, -1 };
	vector<string> vect{ splitter, {} };
	return vect;
}



void GlobalReplace(sLink equation) {
	while (!RegexFind(equation, "[(][)]").empty())
		equation = regex_replace(equation, regex{ "[(][)]" }, "");
	equation = regex_replace(equation, regex{ "[ ]{1,}" }, "");
	equation = regex_replace(equation, regex{ "[)][(]" }, ")*(");
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
	pattern = "[sctnbr][^(]";
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
	// string equation = "sin(sin(4+3*(1+1)))*8+(34-7)"; 
	// string equationSaver = equation;
	// GlobalReplace(equation); 

	/*
	string equation = "s(3+30)*c(n(7))-t(8)+20";
	smatch sm = RegexFind(equation, "[sctnbr][(].{1,}[)]"); 
	*/
	string equation = "hjfas5464sad11s2";
	smatch sm = RegexFind(equation, "[0-9]+");
	smatch sm2 = RegexFind(equation, "[0-9]+");
	smatch* smPtr = &RegexFind(equation, "[0-9]+");
	cout << "----\n";
	cout << smPtr << "\n";
	cout << sm.prefix() << "\n";
	cout << sm.suffix() << "\n";
	cout << sm.str() << "\n";
	cout << &sm << "\n"; 
	 

	// sin(sin(4+3*(1+1)))*8+(34-7) 

	// get last "[sctnbr][(].{1,}[)]",
	// maybe try split with [^]

	// so last for example is string lastFunc

	// string funcArg = CalcArgument(lastFunc);
	// string funcValue = CalcFunc(lastFunc, funcArg);
	// equation = regex_replace(lastFunc, funcValue);


	system("pause");
}