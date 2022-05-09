#include "ConverterFuncs.h"
ConverterFuncs::ConverterFuncs(sPtr eqPtr) {
	this->equation = *eqPtr;
	this->eqPtr = eqPtr;
}
int ConverterFuncs::ArgumentsCorrect(char equation, double arg) {
	if (equation == 't')
		if (cos(arg) == 0) return 0;
	if (equation == 'n')
		if (arg <= 0) return 0;
	if (equation == 'b')
		if (arg <= 0) return 0;
	if (equation == 'r')
		if (arg < 0) return 0;
	return 1;
}
void ConverterFuncs::SetFuncValue(sLink simpleFunc, double value) {
	Replace(simpleFunc, "\\(", "\\(");
	Replace(simpleFunc, "\\)", "\\)");
	Replace(simpleFunc, "\\*", "\\*");
	Replace(simpleFunc, "\\^", "\\^");
	Replace(this->equation, simpleFunc, to_string(value));
	// for outer equation variable
	*(this->eqPtr) = this->equation;
}
string ConverterFuncs::GetSimpleFunc() {
	smatch sm;
	regex_search(this->equation, sm,
		regex{ "[sctnbr][(][^sctnbr]{1,}[)]" });
	if (sm.empty()) return "";
	string simpleFunc = sm.str();
	int cnt = 0;
	for (int i = 0; i < simpleFunc.size(); i++) {
		if (simpleFunc[i] == '(') cnt++;
		if (simpleFunc[i] == ')') cnt--;
	}
	// hard fix of [^sctnbr]{1,}[)] 
	while (cnt != 0) {
		Replace(simpleFunc, "[)]$", "");
		cnt++;
	}
	return simpleFunc;
}
double ConverterFuncs::CalcArg(string func) {
	Replace(func, "[sctnbr][(]{1}|[)]{1}$", "");
	func = infixToPrefix(func);
	return evaluatePrefix(func);
}
int ConverterFuncs::CalcFunc(sLink simpleFunc, double* arg) {
	double funcArg = CalcArg(simpleFunc);
	if (!ArgumentsCorrect(simpleFunc[0], funcArg)) return 0;
	double result; char func = simpleFunc[0];
	if (func == 's') result = sin(funcArg * deg);
	else if (func == 'c') result = cos(funcArg * deg);
	else if (func == 't') result = tan(funcArg * deg);
	else if (func == 'n') result = log(funcArg);
	else if (func == 'b') result = log2(funcArg);
	else if (func == 'r') result = sqrt(funcArg);

	*arg = result;
	return 1;
}
int ConverterFuncs::CalcAllFunctions() {
	this->equation = *(this->eqPtr);
	while (1) {
		double funcValue;
		string simpleFunc = this->GetSimpleFunc();
		if (simpleFunc == "") break;
		if (!this->CalcFunc(simpleFunc, &funcValue)) return 0;
		this->SetFuncValue(simpleFunc, funcValue);
	}
	return 1;
}