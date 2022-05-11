#ifndef FOOLPROOF_H
#define FOOLPROOF_H
#include "../refs/refs.h"
class FoolProof {
public:
	string equation;
	sPtr eqPtr;
	FoolProof(sPtr);
	int GlobalReplace();
	int IsntEmpty();
	int NoIncorrectSymbols(bool);
	int EqualBrackets();
	int SignsCorrect();
	int PointsCorrect(bool);
	int ArgumentsExist();
	int CorrectZeros();

	int AllCorrect();
}; 
#endif