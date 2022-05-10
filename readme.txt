fixes + debug mode
all tests in main.cpp passed.
edit:
	1. Added division by 0 for GetSimpleValue() in class FunctionEvaluator
	2. Added debug couts
	3. Added z(x+y) -> z*(x+y) replace on GlobalReplace()
	4. Moved GetArgument() to the FunctionEvaluator class, now it's called GetArgument()
	5. Rename: SetFuncValue() -> ReplaceFuncValue()
ToDo: 
 	1. Warnings in FunctionEvaluator()
	2. Check & Change naming maybe
	3. Somewhere get str for infix/prefix mode, where calculated only 
	   ard funcs
	4. Maybe do rounding 4-6th digit everywhere