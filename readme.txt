1. 	Have done funcArgs() and funcValue() that returns calculated argument 
	and value of the first 'simple' function in equation. 
	(simlpe means that agrument has no funcs, only based operations +-*/^)
2. 	Did replace simpleFunc to a funcValue in equation.
3. 	Also added in code evaluatePrefix() and other funcs for calc strings 
	just for a convenience. 
4.	Re-wrote regex_replace(), now it's separated function in the top of file.
5. 	Finished ArgumentsCorrect() and NoDividingByZero()
6. 	Re-writed RegexFind(), now it returns bool instead of smatch cuz there's 
	a problem with equal smatches with different addreses: .prefix(), .str()
	and other smatch methods are broken.

7. 	Next gonna do a loop for every function in equation. 
8. 	+ maybe help with prefix infix cuz it's kinda comlicated with '.' doubles