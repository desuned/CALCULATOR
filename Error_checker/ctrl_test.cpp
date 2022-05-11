#include"ctrl_Handler.h"
int main(){
    while(1){
        signal(SIGINT, siginthandler);
        cout<<"enter: ";
        string s;
        cin.ignore();
        getline(cin,s);
        cin.clear();
    };
}