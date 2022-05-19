#include"ctrl_Handler.h"
//CTRL_C
void siginthandler(int s) {
    system("cls");
    std::cout << "###################"
        << "#\nConsole_Cleared#\n"
        << "###################\n";
}
