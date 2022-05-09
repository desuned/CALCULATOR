#include "FunctionEvaluator.h"
FunctionEvaluator::FunctionEvaluator(sPtr eqPtr) {
	this->equation = *eqPtr;
	this->eqPtr = eqPtr;
}
int FunctionEvaluator::ArgumentsCorrect(char equation, double arg) {
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
void FunctionEvaluator::SetFuncValue(sLink simpleFunc, double value) {
	string replacer = "";
	if (!RegexFind(simpleFunc, "[sctnbr]{1,}")) replacer += simpleFunc[0];
	replacer += to_string((int)value);
	cout << "\n eee: " << value;
	
	Replace(simpleFunc, "\\\\", "\\\\");
	Replace(simpleFunc, "\\(", "\\(");
	Replace(simpleFunc, "\\)", "\\)");
	Replace(simpleFunc, "\\*", "\\*"); 
	Replace(simpleFunc, "\\+", "\\+");
	Replace(simpleFunc, "\\-", "\\-");
	Replace(simpleFunc, "\\^", "\\^");
	
	Replace(this->equation, simpleFunc, replacer);
	// for outer equation variable
	*(this->eqPtr) = this->equation;
}
string FunctionEvaluator::GetSimpleFunc() {
	smatch sm; 
	regex_search(this->equation, sm,
		regex{ ".{1}[(][^sctnbr()]{1,}[)]" });
	if (sm.empty()) return "";
	string simpleFunc = sm.str();
	// hard fix of [^sctnbr]{1,}[)] 
	int cnt = 0;
	for (int i = 0; i < simpleFunc.size(); i++) {
		if (simpleFunc[i] == '(') cnt++;
		if (simpleFunc[i] == ')') cnt--;
	}
	while (cnt != 0) {
		Replace(simpleFunc, "[)]$", "");
		cnt++;
	}
	return simpleFunc;
}
double FunctionEvaluator::CalcArg(string func) {
	Replace(func, ".{1}[(]{1}|[)]{1}$", "");  
	func = infixToPrefix(func); 
	return evaluatePrefix(func);
}
int FunctionEvaluator::CalcFunc(sLink simpleFunc, double* arg) {
	double funcArg = CalcArg(simpleFunc); 
	double result; char func = simpleFunc[0];
	if (!ArgumentsCorrect(func, funcArg)) return 0;
	cout << "\n\t  " << funcArg;
	if		(func == 's') result = sin(funcArg * deg);
	else if (func == 'c') result = cos(funcArg * deg);
	else if (func == 't') result = tan(funcArg * deg);
	else if (func == 'n') result = log(funcArg);
	else if (func == 'b') result = log2(funcArg);
	else if (func == 'r') result = sqrt(funcArg);
	else result = funcArg;

	*arg = result;
	return 1;
}
int FunctionEvaluator::CalcAllFunctions() {
	this->equation = *(this->eqPtr);
	while (1) {
		double funcValue;
		string simpleFunc = this->GetSimpleFunc();
		cout << "\n  " << simpleFunc << ", \t" << this->equation;
		if (simpleFunc == "") break;
		if (!this->CalcFunc(simpleFunc, &funcValue)) return 0;
		this->SetFuncValue(simpleFunc, funcValue);
	}
	return 1;
}