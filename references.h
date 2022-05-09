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

#endif