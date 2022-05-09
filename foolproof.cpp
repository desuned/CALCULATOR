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
int RegexFind(string s, string elem) {
	smatch m;
	regex rgxx(elem);
	regex_search(s, m, rgxx);
	return !m.empty();
}
void Replace(string& s, string pattern, string replacer) {
	s = regex_replace(s, regex{ pattern }, replacer);
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
				Stack.push(pow(o1, o2));
				break;
			}
		}
	}

	return Stack.top();
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

	Replace(equation, "pi", "3.1415926535");
	Replace(equation, "e", "2.7182818284");
}
// warning with error + return
// maybe do a message with position of unclosed brackets
class FoolProof {
public:
	string equation;
	sPtr eqPtr;
	FoolProof(sPtr);
	int NoIncorrectSymbols(bool);
	int EqualBrackets();
	int SignsCorrect();
	int ArgumentsExist();
	int NoDividingByZero();
	// int ArgumentsCorrect(char equation, double arg);

	int AllCorrect();
};
FoolProof::FoolProof(sPtr eqPtr) {
	this->equation = *eqPtr; 
	this->eqPtr = eqPtr;
}
int FoolProof::NoIncorrectSymbols(bool needRemove) {
	string pattern = "[^0-9-+/*^()sctnbrep]";
	if (needRemove)
		this->equation = regex_replace(this->equation, regex{pattern}, "");
	return !RegexFind(this->equation, pattern);
}
int FoolProof::EqualBrackets() {
	int cnt = 0;
	for (int i = 0; i < this->equation.size(); i++) {
		if (this->equation[i] == '(') cnt++;
		if (this->equation[i] == ')') cnt--;
	}
	return cnt == 0;
}
int FoolProof::SignsCorrect() { 
	string pattern;
	pattern = "[-+/*^]\\)";
	if (RegexFind(this->equation, pattern)) return 0;
	pattern;
	// (x+)*y
	pattern = "[-+/*^]\\)";
	if (RegexFind(this->equation, pattern)) return 0;
	// (+x)-y
	pattern = "\\([+/*^]";
	if (RegexFind(this->equation, pattern)) return 0;
	// following signs
	pattern = "[-+/*^]{2,}";
	return !RegexFind(this->equation, pattern);
}
int FoolProof::ArgumentsExist() {
	string pattern;
	pattern = "[sctnbr][^(]";
	return !RegexFind(this->equation, pattern);
}
int FoolProof::NoDividingByZero() {
	this->equation = *(this->eqPtr);
	if (RegexFind(this->equation, "/0[^/*-+^.]")) return 0;
	if (RegexFind(this->equation, "/0\\.[0]{1,}[/*-+^]")) return 0;
	return 1;
}
int FoolProof::AllCorrect() {
	if (!(this->NoIncorrectSymbols(0))) return 0;
	if (!(this->EqualBrackets())) return 0;
	if (!(this->SignsCorrect())) return 0;
	if (!(this->ArgumentsExist())) return 0;
	if (!(this->NoDividingByZero())) return 0;
	return 1;
}


class ConverterFuncs {
public: 
	string equation;
	sPtr eqPtr;
	ConverterFuncs(sPtr);
	string GetSimpleFunc();
	void SetFuncValue(sLink, double);
	double CalcArg(string);
	int ArgumentsCorrect(char, double);
	int CalcFunc(sLink, double*);

	int CalcAllFunctions();
};
ConverterFuncs::ConverterFuncs(sPtr eqPtr) {
	this->equation = *eqPtr;
	this->eqPtr = eqPtr;
}
void ConverterFuncs::SetFuncValue(sLink simpleFunc, double value) {
	Replace(simpleFunc, "\\(", "\\(");
	Replace(simpleFunc, "\\)", "\\)");
	Replace(simpleFunc, "\\*", "\\*");
	Replace(simpleFunc, "\\^", "\\^");
	Replace(this->equation, simpleFunc, to_string(value));
	// for outer equation variable
	*(this->eqPtr) = this->equation;
}
string ConverterFuncs::GetSimpleFunc() {
	smatch sm;
	regex_search(this->equation, sm,
		regex{ "[sctnbr][(][^sctnbr]{1,}[)]" });
	if (sm.empty()) return "";
	string simpleFunc = sm.str();
	int cnt = 0;
	for (int i = 0; i < simpleFunc.size(); i++) {
		if (simpleFunc[i] == '(') cnt++;
		if (simpleFunc[i] == ')') cnt--;
	}
	// hard fix of [^sctnbr]{1,}[)] 
	while (cnt != 0) {
		Replace(simpleFunc, "[)]$", "");
		cnt++;
	}
	return simpleFunc;
}
double ConverterFuncs::CalcArg(string func) {
	// some magic where I get from (1+1) 2  
	// and (e+1) gives me e+1 I hope it's possible
	Replace(func, "[sctnbr][(]{1}|[)]{1}$", "");
	func = infixToPrefix(func);
	return evaluatePrefix(func);
}
int ConverterFuncs::ArgumentsCorrect(char equation, double arg) {
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
int ConverterFuncs::CalcFunc(sLink simpleFunc, double* arg) {
	double funcArg = CalcArg(simpleFunc);
	if (!ArgumentsCorrect(simpleFunc[0], funcArg)) return 0;
	double result; char func = simpleFunc[0];
	if (func == 's') result = sin(funcArg * deg);
	else if (func == 'c') result = cos(funcArg * deg);
	else if (func == 't') result = tan(funcArg * deg);
	else if (func == 'n') result = log(funcArg);
	else if (func == 'b') result = log2(funcArg);
	else if (func == 'r') result = sqrt(funcArg);

	*arg = result;
	return 1;
}
int ConverterFuncs::CalcAllFunctions() {
	while (1) {
		double funcValue;
		string simpleFunc = this->GetSimpleFunc();
		if (simpleFunc == "") break;
		if (!this->CalcFunc(simpleFunc, &funcValue)) return 0;
		this->SetFuncValue(simpleFunc, funcValue);
	}
	return 1;
}



int main() {
	string equation = "sin(tg(3*(2^3)))*cos(ln(7))+ln(1)+20*sqrt(3)";
	GlobalReplace(equation);

	FoolProof FoolProof(&equation); 
	ConverterFuncs Converter(&equation);

	int correct = FoolProof.AllCorrect();
	if (correct) Converter.CalcAllFunctions();
	correct = FoolProof.NoDividingByZero();


	if (correct) cout << "\n  Equation's totally correct!";
	else cout << "\n  Equation's wrong!";
	cout << "\n  " << equation << "\n";

	free(&equation);
	free(&correct);
	free(&FoolProof);
	free(&Converter);

	system("pause");
}











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