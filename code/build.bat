g++ -c ctrl_Handler.cpp FoolProof.cpp main.cpp Calculator.cpp refs.cpp
g++ -o main ctrl_Handler.o FoolProof.o main.o Calculator.o refs.o
del ctrl_Handler.o FoolProof.o main.o Calculator.o refs.o
pause