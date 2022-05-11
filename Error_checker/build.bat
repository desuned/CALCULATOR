g++ -c ctrl_Handler.cpp
g++ -c ctrl_test.cpp
g++ -o test ctrl_Handler.o ctrl_test.o
del ctrl_Handler.o
del ctrl_test.o