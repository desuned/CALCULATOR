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
	replacer += to_string(value); 
	cout << "\n  value: " << value;
	cout << "\n  simpleFuncBefore: " << simpleFunc;
	Replace(simpleFunc, "\\\\", "\\\\");
	Replace(simpleFunc, "\\(", "\\(");
	Replace(simpleFunc, "\\)", "\\)");
	Replace(simpleFunc, "\\*", "\\*"); 
	Replace(simpleFunc, "\\+", "\\+");
	Replace(simpleFunc, "\\-", "\\-");
	Replace(simpleFunc, "\\^", "\\^");
	cout << "\n  simpleFuncAfter: " << simpleFunc;
	cout << "\n  replacer: " << replacer;
	Replace(this->equation, simpleFunc, replacer);
	// for outer equation variable
	*(this->eqPtr) = this->equation;
}
string FunctionEvaluator::GetSimpleFunc() {
	smatch sm; 
	// if there's cstnbr then there's ( so I just check ( instead of cst..
	regex_search(this->equation, sm,
		regex{ ".{1}[(][^()]{1,}[)]" });
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
	return stod(GetSimpleValue(func));
}
int FunctionEvaluator::CalcFunc(sLink simpleFunc, double* arg) {
	double funcArg = CalcArg(simpleFunc); 
	cout << "\n  funcArg: " << funcArg;
	double result; char func = simpleFunc[0];
	if (!ArgumentsCorrect(func, funcArg)) return 0; 
	if		(func == 's') result = sin(funcArg * deg);
	else if (func == 'c') result = cos(funcArg * deg);
	else if (func == 't') result = tan(funcArg * deg);
	else if (func == 'n') result = log(funcArg);
	else if (func == 'b') result = log2(funcArg);
	else if (func == 'r') result = sqrt(funcArg);
	else result = funcArg;
	cout << "\n  result: " << result;
	*arg = result;
	return 1;
}
int FunctionEvaluator::CalcAllFunctions() {
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