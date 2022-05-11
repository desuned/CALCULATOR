#include "FoolProof.h"
FoolProof::FoolProof(sPtr eqPtr) {
	this->equation = *eqPtr; 
	this->eqPtr = eqPtr;
}
int FoolProof::GlobalReplace() {
	while (RegexFind(this->equation, "[(][)]"))
		Replace(this->equation, "[(]{1}[)]{1}", "");
	Replace(this->equation, "[ ]{1,}", "");
	Replace(this->equation, "[)][(]", ")*(");
	Replace(this->equation, ":", "/");
	Replace(this->equation, ",", ".");

	Replace(this->equation, "sin", "s");
	Replace(this->equation, "cos", "c");
	Replace(this->equation, "tg", "t");
	Replace(this->equation, "ln", "n");
	Replace(this->equation, "lb", "b");
	Replace(this->equation, "root", "r");

	Replace(this->equation, "pi", "3.141592653");
	Replace(this->equation, "e", "2.7182818284");

	// 5(1+1) -> 5*(1+1);
	smatch sm;
	regex pattern("[0-9]{1,}[(]{1}");
	regex_search(this->equation, sm, pattern); 
	while (1) {
		if (!sm.empty()) {
			string thisPart = sm.str();
			string regexPart = sm.str();
			Replace(thisPart, "[(]{1}", "*(");
			Replace(regexPart, "\\(", "\\("); 
			this->equation = regex_replace(this->equation,
				regex{regexPart}, thisPart, regex_constants::format_first_only);
			regex_search(this->equation, sm, pattern);
		}
		else break;
	}  

	return 1;
}
int FoolProof::IsntEmpty() {
	int error = 0;
	if (this->equation == "")
		error = printf("error(fp0): string's empty");
	else if (!RegexFind(this->equation, "[0-9]"))
		error = printf("error(fp0): string's has no numbers :/");
	return (error == 0);
}
int FoolProof::NoIncorrectSymbols(bool needRemove) { 
	string pattern = "[^0-9-+/*^()sctnbr.]{1,}";
	int error = 0;
	if (needRemove)
		Replace(this->equation, pattern, "");
	else if (RegexFind(this->equation, pattern)) {
		smatch sm;
		regex rgxx(pattern);
		regex_search(this->equation, sm, rgxx);
		error = printf("\n  error(fp1) : equation has incorrect symbol-- % s.", 
				sm.str().c_str());
	}
	return (error == 0);
}
int FoolProof::PointsCorrect(bool needToRemove) {
	string pattern = "[.]{2,}";
	int error = 0;
	if (needToRemove) 
		Replace(this->equation, pattern, ".");
	else if (RegexFind(this->equation, pattern)) 
		error = printf("\n  error(fp6.1): there's two or more following points sings");
	return (error == 0);
}
int FoolProof::EqualBrackets() {
	int cnt = 0;
	for (char symbol : this->equation) {
		if (symbol == '(') cnt++;
		if (symbol == ')') cnt--;
	}
	if (cnt != 0) {
		char bracket = cnt > 0 ? ')' : '(';
		printf("\n  error(fp2): equation has bracket inequality:\n");
		printf("\t\tthere's %d %c less than needed", abs(cnt), bracket);
	}
	return (cnt == 0);
}
int FoolProof::SignsCorrect() {
	int error = 0;
	if (RegexFind(this->equation, "[-+/*^]\\)"))
		error = printf("\n  error(fp3.1): there's operation sign right before closing bracket.");
	else if (RegexFind(this->equation, "\\([+/*^]"))
		error = printf("\n  error(fp3.2): there's operation sign right after opening bracket.");  
	else if (RegexFind(this->equation, "[-+/*^]{2,}"))
		error = printf("\n  error(fp3.3): there's two or more following operation sings.");
	else if (RegexFind(this->equation, "^[+/*^]+"))
		error = printf("\n  error(fp3.4): there's operation sign in the start of equation");
	else if (RegexFind(this->equation, "[+/*^]+$"))
		error = printf("\n  error(fp3.5): there's operation sign in the end of equation");
	return (error == 0);
}
int FoolProof::ArgumentsExist() {
	string pattern = "[sctnbr][^(]";
	if (RegexFind(this->equation, pattern)) {
		smatch sm;
		regex_search(this->equation, sm, regex{pattern});
		string func = sm.str();
		if (func[0] == 's') func = "sin";
		if (func[0] == 'c') func = "cos";
		if (func[0] == 't') func = "tg";
		if (func[0] == 'n') func = "ln";
		if (func[0] == 'b') func = "lb";
		if (func[0] == 'r') func = "root";
		printf("\n  error(fp4): function %s has no argument.", func.c_str());
		return 0;
	}
	return 1;
}
int FoolProof::CorrectZeros() {
	int error = 0;
	if (RegexFind(this->equation, "[/*-+^]0[0-9]{1,}"))
		error = printf("\n  error(fp5.1): number can't has 2 digits before '.' starting with a zero.");
	else if (RegexFind(this->equation, "/0[^.]{1}|/0$"))
		error = printf("\n  error(fp5.2): division by zero."); 
	else if (RegexFind(this->equation, "/0\\.[0]{1,}[/*-+^]|/0\\.[0]{1,}$"))
		error = printf("\n  error(fp5.2): division by zero."); 
	return (error == 0);
}
int FoolProof::AllCorrect() {
	this->GlobalReplace();
	if (!(this->IsntEmpty())) return 0;
	if (!(this->NoIncorrectSymbols(1))) return 0; 
	if (!(this->PointsCorrect(1))) return 0; 
	if (!(this->EqualBrackets())) return 0; 
	if (!(this->SignsCorrect())) return 0; 
	if (!(this->ArgumentsExist())) return 0; 
	if (!(this->CorrectZeros())) return 0;
	*(this->eqPtr) = this->equation; 
	return 1;
}