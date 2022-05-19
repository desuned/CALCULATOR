#ifndef INFILE_H
#define INFILE_H
#define _CRT_SECURE_NO_WARNINGS
#include"refs.h"

using namespace std;

extern int hCounter;

int findCounter();



int inFile(string initExp, string result);

int ScanInt(int* valuePtr);
int getNeeded();


int getInit(string& neededLine);

void seeHistory();

void clearHistory();

#endif