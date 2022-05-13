//
// Created by danya on 13.05.2022.
//

#include "calc_tree.h"
#include "refs/refs.h"

CalcTree::CalcTree(sPtr eqPtr) {        // Constructor

    this->equation = *eqPtr;
    this->eqPtr = eqPtr;

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
