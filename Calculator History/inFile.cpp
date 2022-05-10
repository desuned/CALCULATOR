#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void inFile(string initExp, int result) { //ввод в файл изначального выражения(initial expression) и результата(result)
	ofstream  fout("Calculator History.txt");
	
	fout << initExp << ' ' << result << "\n";
	fout << "string" << 5;
}

int main() {
	inFile("sfaf", 6);
	
}


