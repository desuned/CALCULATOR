#icnlude "refs/refs.h"
#include "calc_tree.cpp"
int main() {
	string equation = "...";
	double result;
	CalcTree Calculator();
	if (Calculator.CalculatePostfix(equation, &result)) 
		cout << "\n  " << result;
}