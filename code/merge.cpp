#define _CRT_SECURE_NO_WARNINGS
#include "refs.h"
#include "FoolProof.h"
#include "ctrl_Handler.h"
#include "Calculator.h"
#include"inFile.h"

void operation_list() {
    cout << "1)Addition             \n"
        << "2)Subtraction          \n"
        << "3)Multiplication       \n"
        << "4)Division             \n"
        << "5)Exponentiation       \n"
        << "6)square root          \n"
        << "7)sin                  \n"
        << "8)cos                  \n"
        << "9)tg                   \n"
        << "10)natural logarithm   \n"
        << "11)base 2 logarithm    \n"
        << "12)processing brackets \n\n";
}
void command_list() {
    cout<< "(~p)Print_Result  (~p)\n"
        << "(~i)Info_Programm (~i)\n"
        << "(~c)Clear_Console (~c)\n"
        << "(~d)Delete_history(~d)\n"
        << "(~s)Exit          (~s)\n";
}
void info_history_menu() {
    cout << "(1)   All   (1)\n"
        << "(2)Number_Op(2)\n";
}
int main() {
    while (true) {
        findCounter();
        command_list();
        signal(SIGINT, siginthandler);
        cout << "Enter expression\n";
        string s;
        getline(cin, s);
        if (s.length() > 2) {
            FoolProof FoolProof;
            if (!FoolProof.AllCorrect(&s)) {
                printf("\n\n Equation's wrong!");
                system("pause");
            }
            else {
                double result=0;
                Calculator a;
                if(a.Calculate(s,&result))cout << "Result: " << result << endl;
                inFile(s, to_string(result));
            }
        }
        else if (s == "~s") { break; }
        else if (s == "~p") {
            info_history_menu();
            char ch= _getch();
            if (ch == '1') {
                cout << '\n' + string(80, '#')+'\n';
                seeHistory();
                cout <<string(80, '#')+'\n';
            }
            else if (ch == '2') {
                string x="";
                getInit(x);
                cout << x<<endl;
            }
            else cout << "command not found\n";
        }
        else if (s == "~i") {
            operation_list();
        }
        else if (s == "~c") {
            system("cls");
        }
        else if (s == "~d") { clearHistory(); }
        cin.clear();
    }
    return 0;
}