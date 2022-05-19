#include "refs.h"
#include "FoolProof.h"
#include "ctrl_Handler.h"
#include "Calculator.h"
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
        << "12)processing brackets \n";
}
void command_list() {
    cout << "(~e)Calculate    (~e)\n"
        << "(~p)Print_Result (~p)\n"
        << "(~i)Info_Programm(~i)\n"
        << "(~c)Clear_Console(~c)\n"
        << "(~s)Exit         (~s)\n";
}
void info_history_menu() {
    cout << "(1)   All   (1)\n"
        << "(2)Number_Op(2)\n";
}
int main() {
    while (true) {
        command_list();
        signal(SIGINT, siginthandler);
        cout << "Enter expression\n";
        string s;
        getline(cin, s);
        if (s.length() > 2) {
            FoolProof FoolProof; // конструктор
            // string equation, её вроде надо объявить, потому что s у тебя отвечает за команду, а не за уравнение
            if (!FoolProof.AllCorrect(&s)) {
                printf("\n\n Equation's wrong!");
                system("pause");
                // тут выход из функции типо, крути цикл с менюшкой дальше, уравнение неправильное
            }
            else {
                double result=0;
                Calculator a;
                if(a.Calculate(s,&result))cout << "Result: " << result << endl;
            }
        }
        else if (s == "~s") { break; }
        else if (s == "~p") {
            info_history_menu();
            if (_getch() == '1') {
                //code zvor
            }
            else if (_getch() == '2') {
                //code zvor
            }
            else cout << "command not found\n";
        }
        else if (s == "~i") {
            operation_list();
        }
        else if (s == "~c") {
            system("cls");
        }
        cin.clear();
    }
    return 0;
}