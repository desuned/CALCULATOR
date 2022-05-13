#include "refs/refs.h" 
#include "FoolProof/FoolProof.cpp"
#include "Calculator/Calculator.cpp"  
int main() { 
	// string equation = "sin(tg(pi/2.2+0/3*(2^3)))*cos(ln(7))+ln(1)^ln(e)+20*root(3)*cos(120)";
	// string equation = "root(5*5)*(6+3*(8-7)+1)+sin(tg(3*(2^3)))*cos(ln(7))+ln(1)^ln(e)";
	string equation = "sqrt(5*5)*(6+3*(8-7)+1)/sin(2)";
	// string equation = "5*(-3)+5/ln(1+1+1+1+11+2*sin(0))"; 
	// string equation = "(-(cos(5+1))plplloppl%%%)";
	// string equation = "1/0.00";
	// string equation = "8+.5+1";
    // string equation = "-5*(-3)+5/ln(1+1+1+1+1+2*sin(0))";

	FoolProof FoolProof;
	Calculator Calculator;
	
	// First stage of FoolProof
	if (!FoolProof.AllCorrect(&equation)) {
		printf("\n\n  Equation's wrong!");
		return Quit();
	}
	// Second stage of FoolProof + Calculate equation
	if (!Calculator.Calculate(&equation)) {
		printf("\n\n  Equation's wrong!");
		return Quit();
	}
	// Output calculated equation
	printf("\n\n  Equation's totally correct!\n  %s\n", 
			equation.c_str());

	Quit();
	return 0; 
}
 