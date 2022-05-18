#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <windows.h>

using namespace std;

int hCounter = 0;

int findCounter() {
	ifstream calcFile("Calculator History.txt");
	
	SetFileAttributes("Calculator History.txt", FILE_ATTRIBUTE_HIDDEN);
	
	if (!calcFile.is_open())  {
		cout << "\n   #File opening error accused#   \n";
		return 0;
	}
	
	if (calcFile.peek() == EOF) {
		cout << "\n   #The file is empty#   \n";
		return 0;
	}
	
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
	
	SetFileAttributes("Calculator History.txt", FILE_ATTRIBUTE_HIDDEN);
	
	if (!calcFile.is_open())  {
		cout << "\n   #File opening error accused!#   \n";
		return 0;
	}
	
	hCounter++;
	
	calcFile << hCounter << ". "<< initExp << ' ' << result << "\n";
	
	calcFile.close();
}

int ScanInt(int* valuePtr) {
	int scanCount = scanf("%d", valuePtr);
	if (scanCount) return 1;
		getc(stdin) != '\n';
	return 0;
}
int getNeeded() {
	int needed = -1;
	printf("\nEnter the number of operation you want to get from history: ");
	while (ScanInt(&needed) == 0 || needed < 0) {
		system("cls");
		printf("\nEnter the correct number of operation you want to get from history: ");
	};
	return needed;
}


int getInit(string *neededLine) { //  функция, находящая нужное выражение по номеру в истории	
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open()) {
		cout << "\n   #File opening error or non existing#   \n";
		return 0;
	}
	
	if (calcFile.peek() == EOF) {
		cout << "\n   #The file is empty#   \n";
		return 0;
	}
	
	int needed = getNeeded();
	
	while (needed < 0 || needed > hCounter) {
		printf("\n   ###Such operation's number doesn't exist, try again###   \n");
		
		needed = getNeeded();
	}
	
	
	string tmpLine;
		
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
			(*neededLine) = tmpLine;
			break;
		}		
	}	
	
	calcFile.close();
}

void seeHistory() { // вывод на экран всей истории
	ifstream calcFile("Calculator History.txt");
	
	if (!calcFile.is_open()) cout << "\n   #The history was cleaned or non existing#   \n";
	
	else {
		while (calcFile) {
			string line;
			
			getline(calcFile, line);
			
			if (line == "") break;
			cout << line << "\n";
		}
	}
	
	calcFile.close();
}

void clearHistory() { //полная очистка истории
	ofstream calcFile("Calculator History.txt", ios_base::trunc);
	SetFileAttributes("Calculator History.txt", FILE_ATTRIBUTE_HIDDEN);
	hCounter = 0;
}
