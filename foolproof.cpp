#include <iostream>
#include <cmath>
#include <string>
#include <regex>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>
using namespace std;
const double deg = 3.1415926535/180.0;
typedef string& sLink;
int RegexFind(string s, string elem) {
	smatch m;
	regex rgxx (elem); 
	regex_search(s, m, rgxx);
	return !m.empty();
}
vector<string> Split(string s, string elem) {
	regex rgxx = regex{ elem };
	sregex_token_iterator splitter{ s.begin(), s.end(), rgxx, -1 };
	vector<string> vect{ splitter, {} };
	return vect;
}
void Replace(string& s, string pattern, string replacer) {
	s = regex_replace(s, regex{ pattern }, replacer );
}


void GlobalReplace(sLink equation) {
	while (RegexFind(equation, "[(][)]"))
		Replace(equation, "[(][)]", ""); 
	Replace(equation, "[ ]{1,}", "");
	Replace(equation, "[)][(]", ")*(");
	Replace(equation, ":", "/");


	Replace(equation, "sin", "s");
	Replace(equation, "cos", "c");
	Replace(equation, "tg", "t");
	Replace(equation, "ln", "n");
	Replace(equation, "lb", "b");
	Replace(equation, "sqrt", "r"); 
	Replace(equation, "pi", "p");
}
// warning with error + return
	/* READ ME
		maybe do a message with position of unclosed brackets
	*/

int NoIncorrectSymbols(sLink equation, bool needRemove) {
	string pattern = "[^0-9-+/*^()sctnbrep]"; 
	if (needRemove) 
		equation = regex_replace(equation, regex{pattern}, "");
	return !RegexFind(equation, pattern);
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
	string pattern; 
	// (x+)*y
	pattern = "[-+/*^])"; 
	if (RegexFind(equation, pattern)) return 0;
	// (+x)-y
	pattern = "([-+/*^]"; 
	if (RegexFind(equation, pattern)) return 0;
	// following signs
	pattern = "[-+/*^]{2,}"; 
	return !RegexFind(equation, pattern);
}
int ArgumentsExist(sLink equation) { 
	string pattern; 
	pattern = "[sctnbr][^(]"; 
	return !RegexFind(equation, pattern);
}

int NoDividingByZero(sLink equation) {
	return !RegexFind(equation, "/0");
}
int ArgumentsCorrect(char equation, double arg) {
	if (equation == 't')
		if (cos(arg) == 0) return 0; 
	if (equation == 'n')
		if (arg <= 0) return 0; 
	if (equation == 'b')
		if (arg <= 0) return 0;
	if (equation == 'r')
		if (arg < 0) return 0;
	return 1;
}



 


int GetPriority(char c) {
	if (c == '^') return 3;
	if (c == '/' || c == '*') return 2;
	if (c == '+' || c == '-') return 1;
	return -1;
}
string infixToPostfix(string infix) {
	stack<char> st;
	string result;
	for (int i = 0; i < infix.length(); i++) {
		char c = infix[i];
		if (isalpha(c) || isdigit(c))
			result += c;
		else if (c == '(') st.push(c);
		else if (c == ')') {
			while (st.top() != '(') {
				result += st.top();
				st.pop();
			}
			st.pop();
		}
		else {
			while (!st.empty() &&
				GetPriority(infix[i]) <= GetPriority(st.top())) {
				if (c == '^' && st.top() == '^')
					break;
				else {
					result += st.top();
					st.pop();
				}
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		result += st.top();
		st.pop();
	}
	return result;
}
string infixToPrefix(string infix) {
	reverse(infix.begin(), infix.end());
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(') {
			infix[i] = ')';
			i++;
		}
		else if (infix[i] == ')') {
			infix[i] = '(';
			i++;
		}
	}
	string prefix = infixToPostfix(infix);
	reverse(prefix.begin(), prefix.end());
	return prefix;
}
double evaluatePrefix(string equation) {
	stack<double> Stack;
	for (int i = equation.size() - 1; i >= 0; i--) {
		char c = equation[i];
		if (isdigit(c)) Stack.push((double)c - '0');
		else {
			double o1 = Stack.top();
			Stack.pop();
			double o2 = Stack.top();
			Stack.pop();
			switch (c) {
			case '+':
				Stack.push(o1 + o2);
				break;
			case '-':
				Stack.push(o1 - o2);
				break;
			case '*':
				Stack.push(o1 * o2);
				break;
			case '/':
				Stack.push(o1 / o2);
				break;
			case '^':
				Stack.push(pow(o1,o2));
				break;
			} 
		}
	}

	return Stack.top();
}


double CalcArgument(string func) {
	// some magic where I get from (1+1) 2  
	// and (e+1) gives me e+1 I hope it's possible
	Replace(func, "[sctnbr][(]{1}|[)]{1}$", "");
	func = infixToPrefix(func); 
	return evaluatePrefix(func);
}
double CalcFunc(char func, double arg) {
	double result;
	if		(func == 's') result = sin(arg*deg);
	else if (func == 'c') result = cos(arg*deg);
	else if (func == 't') result = tan(arg*deg);
	else if (func == 'n') result = log(arg);
	else if (func == 'b') result = log2(arg);
	else if (func == 'r') result = sqrt(arg);
	return result;
}


int main() {
	string equation = "sin(tg(3*(2^3)))*cos(ln(7))-tg(8)+20"; 
	string equationSaver = equation;
	GlobalReplace(equation);   

	smatch sm; 
	regex_search(equation, sm, 
		regex{ "[sctnbr][(][^sctnbr]{1,}[)]" });
	 
	string simpleFunc = sm.str(); 
	// hard fix of [^sctnbr]{1,}[)] 
	while (!EqualBrackets(simpleFunc)) Replace(simpleFunc, "[)]$", ""); 

	double funcArg = CalcArgument(simpleFunc);
	// if !ArgumentsCorrect(simpleFunc[0], funcArg) return
	double funcValue = CalcFunc(simpleFunc[0], funcArg); 
	Replace(simpleFunc, "\\(", "\\(");
	Replace(simpleFunc, "\\)", "\\)");
	Replace(simpleFunc, "\\*", "\\*");
	Replace(simpleFunc, "\\^", "\\^");
	Replace(equation, simpleFunc, to_string(funcValue));




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

	// string funcArg = CalcArgument(lastFunc);
	// string funcValue = CalcFunc(lastFunc, funcArg);
	// Replace(equation, lastFunc, funcValue); 


	system("pause");
}