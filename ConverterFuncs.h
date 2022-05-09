#ifndef CONVERTERFUNCS_H
#define CONVERTERFUNCS_H
#include "references.h"
class ConverterFuncs {
public:
	string equation;
	sPtr eqPtr;
	ConverterFuncs(sPtr);
	string GetSimpleFunc();
	void SetFuncValue(sLink, double);
	double CalcArg(string);
	int ArgumentsCorrect(char, double);
	int CalcFunc(sLink, double*);

	int CalcAllFunctions();
}; 
#endif