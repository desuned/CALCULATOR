#include "refs/refs.h"
#include "refs/calc.h"
#include "FoolProof/FoolProof.cpp"
#include "FunctionEvaluator/FunctionEvaluator.cpp"



int main() {
	// string equation = "sin(tg(3*(2^3)))*cos(ln(7))+ln(1)^ln(e)+20*root(3)*cos(120)";
	// string equation = "root(5*5)*(6+3*(8-7)+1)+sin(tg(3*(2^3)))*cos(ln(7))+ln(1)^ln(e)";
	// string equation = "root(5*5)*(6+3*(8-7)+1)/sin(2)";
	string equation = "5*(-3)+5-ln(e)"; 
	FoolProof FoolProof(&equation);
	FunctionEvaluator Converter(&equation);
	 
	// cout << "\n  Answer: " << GetSimpleValue(equation);
	  
	int correct = FoolProof.AllCorrect(); 
	if (correct) {
		Converter.CalcAllFunctions();
		correct = FoolProof.CorrectZeros();
		equation = GetSimpleValue(equation);
	}

	if (correct) cout << "\n  Equation's totally correct!";
	else cout << "\n  Equation's wrong!";
	cout << "\n  " << equation << "\n";


	cout << "\n  ";  system("pause");
	return 0; 
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