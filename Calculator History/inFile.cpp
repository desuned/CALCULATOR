#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int hCounter = 0;

int inFile(string initExp, string result) { // ввод в файл изначального выражения(initial expression) и результата(result)
	ofstream  calcFile("Calculator History.txt", ios_base::app);
	
	if (!calcFile.is_open())  {
		cout << "\nFile opening error accused!\n";
		return 0;
	}
	
	hCounter++;
	
	calcFile << hCounter << ". "<< initExp << ' ' << result << "\n";
	
	calcFile.close();
}

void seeLast() { // вывод на экран последнего действия 
	
}

string getInit() { //  функция, находящая нужное выражение по номеру в истории!!!
	//
}

void seeHistory() { // вывод на экран всей истории
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open()) cout << "\n   #The history was cleaned or non existing#   \n";
	
	else {
		while (calcFile) {
			string line;
			
			getline(calcFile, line);
			
			if (line == "") break;
			else cout << line << "\n";
		}
		
		calcFile.close();
	}
}

int createFile() { // функция первоначального создания файла(необязательна)
	ofstream calcFile("Calculator History.txt");
	calcFile.close();
}

void clearFile() { //полная очистка истории
	ofstream calcFile("Calculator History.txt", ios_base::trunc);
}



int main() { // основная функция для тестирования
	return 0;
}


