#include "Calculator.h"
int ArrayFind(vector<string>* arr, char elem) {
	for (int i = 0; i < (*arr).size(); i++)
		if (((*arr)[i])[0] == elem) return i;
	return -1;
}
// constructor 
Calculator::Calculator(sPtr eqPtr) {
	this->equation = *eqPtr;
	this->eqPtr = eqPtr;
}

string Calculator::GetSimpleFunc() {
	smatch sm;
	// if there's cstnbr then there's ( so I just check ( instead of cst..
	regex_search(this->equation, sm,
		regex{ "[^(]{0,1}[(][^()]{1,}[)]" });
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
string Calculator::GetArgument(string equation) {
	Replace(equation, "^.{0,1}[(]+|[)]+$", "");
	Replace(equation, "^-", "0-"); 
	vector<string> nums = Split(equation, "[^.0-9]+");
	vector<string> signs = Split(equation, "[.0-9]+");
	if (signs[0] == "") signs.erase(signs.begin() + 0);
	double res = 0;

	cout << "\n  Nums:";
	for each (string num in nums)
		cout << "\n    " << num;
	cout << "\n  Signs:";
	for each (string sign in signs)
		cout << "\n    " << sign;
	cout << "\n  Steps:"; 

	char const_signs[] = { '^', '*', '/', '-', '+' };
	int cnt = 0;
	while (signs.size() != 0) {
		char loopSign = const_signs[cnt];
		// calc all nums around loopSign
		int i = ArrayFind(&signs, loopSign);
		while (i >= 0) {
			double left = stod(nums[i]);
			double right = stod(nums[i + 1]);
			cout << "\n\t" << left
				<< " " << signs[i]
				<< " " << right << " = ";
			if (signs[i] == "/" && right == 0) return ""; 
			// *-, /-, --, +-, ^- cases
			if (signs[i].size() == 2) right *= -1;
			if (loopSign == '^')
				nums[i] = to_string(pow(left, right));
			else if (loopSign == '*')
				nums[i] = to_string(left * right);
			else if (loopSign == '/')
				nums[i] = to_string(left / right);
			else if (loopSign == '-')
				nums[i] = to_string(left - right);
			else if (loopSign == '+')
				nums[i] = to_string(left + right);
			cout << nums[i] << " ;";
			signs.erase(signs.begin() + i);
			nums.erase(nums.begin() + i + 1);
			i = ArrayFind(&signs, loopSign);
		}
		cnt++;
	}
	cout << "\n  --------------------";
	return nums[0];
}

int Calculator::ArgumentCorrect(char equation, double arg) {
	// 4th digit round;
	if (equation == 't')
		if (int(10000 * cos(arg)) / 1000 == 0) {
			cout << "\n  error(c1.1): tg from pi*k/2 (k belongs R) is not defined";
			return 0;
		}
	if (equation == 'n')
		if (arg <= 0) {
			if (arg == 0) cout << "\n  error (c1.22): ln(0) is not defined";
			else cout << "\n   error(c1.21): ln from negative argument is not defined";
			return 0;
		}
	if (equation == 'b')
		if (arg <= 0) {
			if (arg == 0) cout << "\n  error (c1.22): lb(0) is not defined";
			else cout << "\n  error(c1.22): lb from negative argument is not defined";
			return 0;
		}
	if (equation == 'r')
		if (arg < 0) {
			cout << "\n  error(c1.3): root from negative argument is not defined";
			return 0;
		}
	return 1;
}
int Calculator::CalcFunc(sLink simpleFunc, double* arg) {
	cout << "\n\n\n  simpleFunc: " << simpleFunc;
	string funcArgStr = this->GetArgument(simpleFunc);
	if (funcArgStr == "") {
		cout << "\n  error(c0): division by zero.";
		return 0;
	}
	double funcArg = stod(funcArgStr);
	cout << "\n  funcArg: " << funcArg;
	double result; char func = simpleFunc[0];
	if (!this->ArgumentCorrect(func, funcArg)) return 0;
	
	if		(func == 's') result = sin(funcArg);
	else if (func == 'c') result = cos(funcArg);
	else if (func == 't') result = tan(funcArg);
	else if (func == 'n') result = log(funcArg);
	else if (func == 'b') result = log2(funcArg);
	else if (func == 'r') result = sqrt(funcArg);
	else result = funcArg;
	cout << " -> value: " << result;
	*arg = result;
	return 1;
}
void Calculator::ReplaceFuncValue(sLink simpleFunc, double value) {
	string replacer = "";
	if (!RegexFind(simpleFunc, "^[sctnbr(]")) replacer += simpleFunc[0];
	replacer += to_string(value); 
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

int Calculator::Calculate() {
	this->equation = *(this->eqPtr); 
	cout << "\n oi:" << this->equation;
	cout << "\n b: " << *(this->eqPtr);
	while (1) {
		double funcValue; 
		string simpleFunc = this->GetSimpleFunc();  
		if (simpleFunc == "") break;
		if (!this->CalcFunc(simpleFunc, &funcValue)) return 0;
		cout << "\n  Previous equation: " << this->equation;
		this->ReplaceFuncValue(simpleFunc, funcValue);
		cout << "\n  Current equation: " << this->equation;
	}
	cout << "\n\n";
	*(this->eqPtr) = GetArgument(this->equation); 
	return !(*(this->eqPtr) == "");
}




