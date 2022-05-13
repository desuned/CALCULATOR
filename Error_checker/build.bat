g++ -c ctrl_Handler.cpp
g++ -c menu.cpp
g++ -o menu ctrl_Handler.o menu.o
del ctrl_Handler.o
del menu.o