#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H
#include "../refs/refs.h"
#include "../refs/calc.h"
class FunctionEvaluator {
public:
	string equation;
	sPtr eqPtr;
	FunctionEvaluator(sPtr);
	string GetSimpleFunc();
	void SetFuncValue(sLink, double);
	double CalcArg(string);
	int ArgumentsCorrect(char, double);
	int CalcFunc(sLink, double*);

	int CalcAllFunctions();
}; 
#endif