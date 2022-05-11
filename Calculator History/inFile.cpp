#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <windows.h>

using namespace std;

int hCounter = 0;

int findCounter() {
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open())  {
		cout << "\n   #File opening error accused!#   \n";
		return 0;
	}
	
	if (calcFile.peek() == EOF) return 0;
	
	while(calcFile) {
		string tmpLine;
		getline(calcFile, tmpLine);
		hCounter++;
	}
	
	hCounter--;
}

void Replace(string& s, string pattern, string replacer) {
	s = regex_replace(s, regex{ pattern }, replacer);
}

int inFile(string initExp, string result) { // ввод в файл изначального выражения(initial expression) и результата(result)
	ofstream  calcFile("Calculator History.txt", ios_base::app);
	
	if (!calcFile.is_open())  {
		cout << "\n   #File opening error accused!#   \n";
		return 0;
	}
	
	hCounter++;
	
	calcFile << hCounter << ". "<< initExp << ' ' << result << "\n";
	
	calcFile.close();
}

string getLast() { // вывод на экран последнего действия 
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open()) cout << "\n   #File opening error or non existing#   \n";
	
	else {
		string tmpLine, lastLine;
		
		while (calcFile) {	
			getline(calcFile, tmpLine);
			
			smatch m;
			regex rgx("^[0-9]{1,}[.]{1}");
			regex_search(tmpLine, m, rgx);
			string n = m.str();
			Replace(n, "[.]{1}", "");
			int number = stoi(n);
			
			if (number == hCounter) {
				Replace(tmpLine, "[0-9.]+$|^[0-9]+[.]{1}[ ]{1}", "");
				lastLine = tmpLine;
				break;
			}	
		}
		
		return lastLine;
	}
}

string getInit() { //  функция, находящая нужное выражение по номеру в истории!!!	
	cout << "\nEnter the ordinal number of needed element: ";
	int needed;
	cin >> needed;

	while (needed > hCounter || needed <= 0) {
		cout << "\n   ###The number of needed expression doesn't exist, try once more###   \n";
		cout << "\nEnter the ordinal number of needed element: ";
		
		cin >> needed;
	}
		
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open()) cout << "\n   #File opening error or non existing#   \n";
	
	else {
		string tmpLine, neededLine;
		
		while (calcFile) {	
			getline(calcFile, tmpLine);
			
			smatch m;
			regex rgx("^[0-9]{1,}[.]{1}");
			regex_search(tmpLine, m, rgx);
			string n = m.str();
			Replace(n, "[.]{1}", "");
			int number = stoi(n);
			
			if (number == needed) {
				Replace(tmpLine, "[0-9.]+$|^[0-9]+[.]{1}[ ]{1}", "");
				neededLine = tmpLine;
				break;
			}		
		}	
		
		return neededLine;
	}
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
	
	SetFileAttributes("Calculator History.txt", FILE_ATTRIBUTE_HIDDEN);
	
	if (!calcFile.is_open()) {
		cout << "\n   ###CRITICAL ERROR: THE FILE CANNOT BE OPENED###   \n";
		exit(0);
	}
		
	calcFile.close();
}

void clearHistory() { //полная очистка истории
	ofstream calcFile("Calculator History.txt", ios_base::trunc);
	hCounter = 0;
}
