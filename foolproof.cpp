#include <iostream>
#include <string>
#include <regex>
using namespace std;
typedef string& sLink;

smatch RegexFind(string s, string elem) {
	smatch m;
	regex rgxx = regex{ elem };
	regex_search(s, m, rgxx);
	return m;
}


int EqualBrackets(sLink equation) {
	int cnt = 0;
	for (int i = 0; i < equation.size(); i++) {
		if (equation[i] == '(') cnt++;
		if (equation[i] == ')') cnt--; 
	}
	return cnt == 0; 
}
int NoIncorrectSymbols(sLink equation) {
	// [^0-9-+^*().] + sin, cos, ln, lb
	return 1;
}
int NoFollowingOperations(sLink equation) {
	// [+*-/^]{2,} ig
	return 1;
}
int TrigonometryIsCorrect(sLink equation) {
	// [{sin}{cos}{tg}{ln}{lb}][^(] -- sin4 for example
	// idk, it's comlicated
	return 1;
}
int NoDividingByZero(sLink equation) {
	// check x/ln(1)
	// check x/lb(1)
	// check x/0
	// check x/sin(k*pi)
	// check x/cos(k*pi/2)
	return 1;
}
int NoSignsWithBracket(sLink equation) {
	// (x+)*y
	// (+x)-y
	return 1;
} 
int CorrectArguments(sLink equation) {
	// positive args on ln, lb, sqrt 
	// tg with args != pi*k/2
	// 
	return 1;
}



int main() {
	string testEquation = "sin(f)+cos(5)-sin51\n";
	
	smatch test = RegexFind(testEquation, "sin[^(]"); 
	cout << test.empty() << "\n";

	system("pause");
}