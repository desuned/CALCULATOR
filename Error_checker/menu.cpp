#include"menu.h"
void operation_list(){
    cout<<"1)Addition             \n"
        <<"2)Subtraction          \n"
        <<"3)Multiplication       \n"
        <<"4)Division             \n"
        <<"5)Exponentiation       \n"
        <<"6)square root          \n"
        <<"7)sin                  \n"
        <<"8)cos                  \n"
        <<"9)tg                   \n"
        <<"10)natural logarithm   \n"
        <<"11)base 2 logarithm    \n"
        <<"12)processing brackets \n";
}
void command_list(){
    cout<<"(~e)Calculate    (~e)\n"
        <<"(~p)Print_Result (~p)\n"
        <<"(~i)Info_Programm(~i)\n"
        <<"(~c)Clear_Console(~c)\n"
        <<"(~s)Exit         (~s)\n";
}
void info_history_menu(){
    cout<<"(1)   All   (1)\n"
        <<"(2)Number_Op(2)\n";
}
void menu(){
    while(true){
        // BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
        signal(SIGINT, siginthandler);
        cout<<"Enter expression\n";
        string s;
        cin.ignore();
        getline(cin,s);
        if(s.length()==2){
            if(s=="~e"){
                //code
            }
            else if(s=="~p"){
                info_history_menu();
                if(getch()=='1'){
                    //code
                }
                else if(getch()=='2'){
                    //code
                }
                else cout<<"Command not found\n";
            }
            else if(s=="~i"){
                operation_list();
            }
            else if(s=="~c"){
                system("cls");
            }
            else if(s=="~s"){break;}
        }
        cin.clear();
    };
}