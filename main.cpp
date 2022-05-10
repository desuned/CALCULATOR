#include "refs/refs.h" 
#include "FoolProof/FoolProof.cpp"
#include "FunctionEvaluator/FunctionEvaluator.cpp"

int main() {
	string equation = "sin(tg(pi/2.2+0/3*(2^3)))*cos(ln(7))+ln(1)^ln(e)+20*root(3)*cos(120)";
	// string equation = "root(5*5)*(6+3*(8-7)+1)+sin(tg(3*(2^3)))*cos(ln(7))+ln(1)^ln(e)";
	// string equation = "root(5*5)*(6+3*(8-7)+1)/sin(2)";
	// string equation = "5*(-3)+5/ln(1+1+1+1+11+2*sin(0))"; 
	// string equation = "5(5+1)";
	FoolProof FoolProof(&equation);
	FunctionEvaluator Converter(&equation);
	  
	if (FoolProof.AllCorrect()) 
		if(Converter.CalcAllFunctions())
			cout << "\n\n\n  Equation's totally correct!\n  " << equation;
		else cout << "\n\n\n  Equation's wrong!";
	else cout << "\n\n\n  Equation's wrong!";



	cout << "\n  ";  system("pause");
	return 0; 
}