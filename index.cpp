#include "refs/refs.h"
#include "FoolProof/FoolProof.cpp"
#include "FunctionEvaluator/FunctionEvaluator.cpp"
int main() {
	string equation = "sin(tg(3*(2^3)))*cos(ln(7))+ln(1)+20*root(3)*cos(120)";

	FoolProof FoolProof(&equation);
	FunctionEvaluator Converter(&equation);

	int correct = FoolProof.AllCorrect();
	if (correct) {
		Converter.CalcAllFunctions();
		correct = FoolProof.NoDivisionByZero();
	}

	cout << "\n  " << cos(120 * deg);

	if (correct) cout << "\n  Equation's totally correct!";
	else cout << "\n  Equation's wrong!";
	cout << "\n  " << equation << "\n";


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