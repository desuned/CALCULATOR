#include"ctrl_Handler.h"
//CTRL_C
void siginthandler(int s){
    system("cls");   
    cout<<"###################"
        <<"#\nConsole_Cleared#\n"
        <<"###################\n";
}
// BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
// {
//     if (dwCtrlType == CTRL_CLOSE_EVENT)
//     {
//         return TRUE;
//     }

//     return FALSE;
// }