#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H
#include "../refs/refs.h" 
class FunctionEvaluator {
public:
	string equation;
	sPtr eqPtr;
	FunctionEvaluator(sPtr);

	string GetSimpleFunc(); 
	string GetArgument(string); 

	int ArgumentsCorrect(char, double);
	int CalcFunc(sLink, double*);
	void ReplaceFuncValue(sLink, double);

	int CalcAllFunctions();
}; 
#endif