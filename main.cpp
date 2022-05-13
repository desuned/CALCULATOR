//
// Created by danya on 13.05.2022.
//

#include "refs/refs.h"
#include "calc_tree.cpp"

/*
tests:
0-5*(0-3)+5/n(1+1+1+1+1+2*s(0)) ==  18.1067
8+.5+1 == 9.5
(0-(c(5+1))) == -0.96017
r(5*5)*(6+3*(8-7)+1)/s(2) == 54.9875
r(5*5)*(6+3*(8-7)+1)+s(t(3*(2^3)))*c(n(7))+n(1)^n(2.7182818284) == 50.3096
s(t(3.141592653/2.2+0/3*(2^3)))*c(n(7))+n(1)^n(2.7182818284)+20*r(3)*c(120) == 27.976
*/

int main() {

    string equation = "0-5*(0-3)+5/n(1+1+1+1+1+2*s(0))";
    double result;
    CalcTree Calculator(&equation);

    if (Calculator.CalculatePostfix(equation, &result)) cout << "\n  " << result;

}