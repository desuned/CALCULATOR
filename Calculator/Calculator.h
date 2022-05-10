#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "../refs/refs.h" 
class Calculator {
public:
	string equation;
	sPtr eqPtr;
	Calculator(sPtr);

	string GetSimpleFunc(); 
	string GetArgument(string); 

	int ArgumentCorrect(char, double);
	int CalcFunc(sLink, double*);
	void ReplaceFuncValue(sLink, double);

	int Calculate();
}; 
#endif