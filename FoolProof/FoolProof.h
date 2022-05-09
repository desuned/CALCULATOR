#ifndef FOOLPROOF_H
#define FOOLPROOF_H
#include "../refs/refs.h"
class FoolProof {
public:
	string equation;
	sPtr eqPtr;
	FoolProof(sPtr);
	void GlobalReplace();
	int NoIncorrectSymbols(bool);
	int EqualBrackets();
	int SignsCorrect();
	int ArgumentsExist();
	int NoDivisionByZero();

	int AllCorrect();
}; 
#endif