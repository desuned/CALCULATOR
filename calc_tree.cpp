//
// Created by danya on 13.05.2022.
//

#include "calc_tree.h"
#include "refs/refs.h"

int CalcTree::ArgumentCorrect(char equation, double arg) {

    int error = 0;

    if (equation == 't') {

        if (int(10000 * cos(arg)) / 1000 == 0) // 4th digit round;
            error = printf("\n  error: tg from pi*k/2 (k belongs R) is not defined");

    }

    if (equation == 'n' || equation == 'b') {

        if (arg <= 0) {

            if (arg == 0) error = printf("\n  error: l%c(0) is not defined", equation);
            else error = printf("\n   error: l%c from negative argument is not defined", equation);

        }

    }

    if (equation == 'r' && arg < 0) error = printf("\n  error: root from negative argument is not defined");

    if (equation == '/' && arg == 0) error = printf("\n  error: division by zero.");

    return (error == 0);

}

int CalcTree::GetPriority(string item) {

    if (RegexFind(item, "[sctnbr]")) return 4;
    if (item == "^") return 3;
    if (item == "/" || item == "*") return 2;
    if (item == "+" || item == "-") return 1;
    return -1;

}

vector<string> CalcTree::InfixToPostfix(sLink equation) {

    vector<string> infix = SaveSplit(equation, "[+-*/^()]{1}");
    stack<string> st;
    vector<string> result = {};

    for (int i = 0; i < infix.size(); i++) {

        string item = infix[i];

        if (RegexFind(item, "[0123456789]")) result.push_back(item);   // Check, if current symbol is digit
        else if (item == "(") st.push(item);
        else if (item == ")") {

            while (st.top() != "(") {       // Going back to '('

                result.push_back(st.top());
                st.pop();

            }
            st.pop();

        }
        else {

            while (!st.empty() && this->GetPriority(infix[i]) <= this->GetPriority(st.top())) {

                if (item == "^" && st.top() == "^") break;
                else {

                    result.push_back(st.top());
                    st.pop();

                }

            }

            st.push(item);

        }

    }

    while (!st.empty()) {

        result.push_back(st.top());
        st.pop();

    }

    return result;

}

double CalcTree::CalculatePostfix(sLink equation, double* result) {

    vector<string> postfix = this->InfixToPostfix(equation);
    stack<double> Stack;

    for (int i = 0; i < postfix.size(); i++) {

        string item = postfix[i];

        if (RegexFind(item, "[0-9]")) Stack.push(stod(item));
        else if (RegexFind(item, "[sctnbr]")) {

            double peak = Stack.top();

            if (!this->ArgumentCorrect(item[0], peak)) return 0;
            if (item == "s") peak = sin(peak);
            else if (item == "c") peak = cos(peak);
            else if (item == "t") peak = tan(peak);
            else if (item == "n") peak = log(peak);
            else if (item == "b") peak = log2(peak);
            else if (item == "r") peak = sqrt(peak);
            Stack.pop();
            Stack.push(peak);

        }
        else {

            double peakRight = Stack.top();
            Stack.pop();
            double peakLeft = Stack.top();
            Stack.pop();
            //printf("\n  Operation: %lf %s %lf", peakLeft, item.c_str(), peakRight);

            if (!this->ArgumentCorrect(item[0], peakRight)) return 0;
            if (item == "+") Stack.push(peakLeft + peakRight);
            else if (item == "-") Stack.push(peakLeft - peakRight);
            else if (item == "*") Stack.push(peakLeft * peakRight);
            else if (item == "/") Stack.push(peakLeft / peakRight);
            else if (item == "^") Stack.push(pow(peakLeft, peakRight));

        }

    }
    // free(Stack);
    *result = Stack.top();
    return 1;

}