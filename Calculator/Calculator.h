//
// Created by danya on 13.05.2022.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include "../refs/refs.h"

class Calculator {

public:
    int ArgumentCorrect(char, double);
    int GetPriority(string);
    vector<string> InfixToPostfix(sLink);
    double Calculate(sLink &equation, double *result);

};

#endif //CALCULATOR_CALCULATOR_H
