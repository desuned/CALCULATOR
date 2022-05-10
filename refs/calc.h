#ifndef CALC_H
#define CALC_H
#include "refs.h"

vector<string> SaveSplit(string str, string pattern) {
	smatch m;
	regex rgx = regex{ pattern };
	sregex_token_iterator splitter{ str.begin(), str.end(), rgx, -1 };
	vector<string> strArr { splitter, {} };
	int vecSize = strArr.size();
	for (int i = 0; i < vecSize-1; i++) {
		regex_search(str, m, rgx); 
		strArr.insert(strArr.begin() + i * 2 + 1, m.str());
		str = regex_replace(str, rgx, "", regex_constants::format_first_only);
	}
	return strArr;
}
vector<string> Split(string str, string pattern) {
	regex rgx = regex{ pattern };
	sregex_token_iterator splitter{ str.begin(), str.end(), rgx, -1 };
	vector<string> strArr{ splitter, {} };
	return strArr;
}

int ArrayFind(vector<string>* arr, char elem) {
	for (int i = 0; i < (*arr).size(); i++)
		if (((*arr)[i])[0] == elem) return i;
	return -1;
}


string GetSimpleValue(sLink equation) {
	Replace(equation, "^-", "0-");
	vector<string> nums = Split(equation, "[^.0-9]+");
	vector<string> signs = Split(equation, "[.0-9]+");
	if (signs[0] == "") signs.erase(signs.begin() + 0);
	double res = 0;


	cout << "\n  Nums:";
	for each (string num in nums)
		cout << "\n    " << num;
	cout << "\n  Signs:";
	for each (string sign in signs)
		cout << "\n    " << sign;

	// cout << "\n  ";  system("pause");
	// return 0; 

	char const_signs[] = { '^', '*', '/', '-', '+' };
	int cnt = 0;
	while (signs.size() != 0) {
		char loopSign = const_signs[cnt];
		// calc all nums around loopSign
		int i = ArrayFind(&signs, loopSign);
		while (i >= 0) {
			cout << "\n  h: " << signs[i];
			int left = stoi(nums[i]);
			int right = stoi(nums[i + 1]);
			// *-, /-, --, +-, ^- cases
			if (signs[i].size() == 2) right *= -1;

			if (loopSign == '^')
				nums[i] = to_string(pow(left, right));
			else if (loopSign == '*')
				nums[i] = to_string(left * right);
			else if (loopSign == '/')
				nums[i] = to_string(left / right);
			else if (loopSign == '-')
				nums[i] = to_string(left - right);
			else if (loopSign == '+')
				nums[i] = to_string(left + right);
			signs.erase(signs.begin() + i);
			nums.erase(nums.begin() + i + 1);
			i = ArrayFind(&signs, loopSign);
		}
		cnt++;
	}

	return nums[0];

}






int GetPriority(string c) {
	if (c == "^") return 3;
	if (c == "/" || c == "*") return 2;
	if (c == "+" || c == "-") return 1;
	return -1;
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