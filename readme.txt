Now it seems that all can be calculated
1.	Main change is in calc.h, added GetSimpleValue() that calcs 
	value of simple equations without brackets (operations only).
	+
	Wrote Split() and ArrayFind() for easier working in GetSimplevalue().
	Wrote SaveSplit, but didn't use it, idk, maybe'll remove it.
	+
	Little changes in FunctionEvaluator functions for GetSimpleValue();

