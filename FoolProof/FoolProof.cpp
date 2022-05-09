#include "FoolProof.h"
FoolProof::FoolProof(sPtr eqPtr) {
	this->equation = *eqPtr; 
	this->eqPtr = eqPtr;
}
void FoolProof::GlobalReplace() {
	while (RegexFind(this->equation, "[(][)]"))
		Replace(this->equation, "[(][)]", "");
	Replace(this->equation, "[ ]{1,}", "");
	Replace(this->equation, "[)][(]", ")*(");
	Replace(this->equation, ":", "/");


	Replace(this->equation, "sin", "s");
	Replace(this->equation, "cos", "c");
	Replace(this->equation, "tg", "t");
	Replace(this->equation, "ln", "n");
	Replace(this->equation, "lb", "b");
	Replace(this->equation, "root", "r");

	Replace(this->equation, "pi", "3.141592653");
	Replace(this->equation, "e", "2.7182818284");

	*(this->eqPtr) = this->equation;
}
int FoolProof::NoIncorrectSymbols(bool needRemove) {
	string pattern = "[^0-9-+/*^()sctnbrep.]";
	if (needRemove) Replace(this->equation, pattern, "");
	if (RegexFind(this->equation, pattern)) {
		smatch sm;
		regex rgxx(pattern);
		regex_search(this->equation, sm, rgxx);
		cout << "\n  error (fp1): equation has incorrect symbol -- " << sm.str() << ".";
		return 0;
	}
	return 1;
}
int FoolProof::EqualBrackets() {
	int cnt = 0;
	for (int i = 0; i < this->equation.size(); i++) {
		if (this->equation[i] == '(') cnt++;
		if (this->equation[i] == ')') cnt--;
	}
	if (cnt != 0) {
		cout << "\n  error (fp2): equation has bracket inequality, "; 
		cout << "there's " << abs(cnt);
		if (cnt > 0) cout << " ) less"; 
		else cout << " ( less";
		cout << " then needed.";
		return 0;
	}
	return 1;
}
int FoolProof::SignsCorrect() { 
	string pattern; 
	// (x+)*y
	pattern = "[-+/*^]\\)"; 
	if (RegexFind(this->equation, pattern)) {
		cout << "\n  error (fp3): there's operation sign right before closing bracket.";
		return 0;
	}
	// (+x)-y
	pattern = "\\([+/*^]";
	if (RegexFind(this->equation, pattern)) {
		cout << "\n  error (fp3): there's operation sign right after opening bracket.";
		return 0;
	}
	// following signs
	pattern = "[-+/*^]{2,}";
	if (RegexFind(this->equation, pattern)) {
		cout << "\n  error (fp3): there's two or more following operation sings.";
		return 0;
	}
	return 1;
}
int FoolProof::ArgumentsExist() {
	string pattern;
	pattern = "[sctnbr][^(]";
	if (RegexFind(this->equation, pattern)) {
		smatch sm;
		regex rgxx(pattern);
		regex_search(this->equation, sm, rgxx);
		string func = sm.str();
		if (func[0] == 's') func = "sin";
		if (func[0] == 'c') func = "cos";
		if (func[0] == 't') func = "tg";
		if (func[0] == 'n') func = "ln";
		if (func[0] == 'b') func = "lb";
		if (func[0] == 'r') func = "root";
		cout << "\n  error (fp4): function " << func << "has no argument.";
		return 0;
	}
	return 1;
}
int FoolProof::NoDivisionByZero() {
	this->equation = *(this->eqPtr);
	if (RegexFind(this->equation, "/0[^/*-+^.]")) { 
		cout << "\n  error (fp5): division by zero.";
		return 0;
	};
	if (RegexFind(this->equation, "/0\\.[0]{1,}[/*-+^]")) {
		cout << "\n  error (fp5): division by zero.";
		return 0;
	}; 
	return 1;
}
int FoolProof::AllCorrect() {
	this->GlobalReplace(); 
	if (!(this->NoIncorrectSymbols(0))) return 0;
	if (!(this->EqualBrackets())) return 0;
	if (!(this->SignsCorrect())) return 0;
	if (!(this->ArgumentsExist())) return 0;
	if (!(this->NoDivisionByZero())) return 0;
	return 1;
}