#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

enum SoN { 
	OCT = 8,
	DEC = 10,
	HEX = 16
};

void SuperCin(char * s, int &b);
void Qsort(int **& a, int constant, bool direction, int l, int r);

void Show_Matrix(int ** m, int a, int b);
void Give_Memory(int ** & a, int m, int n);
void Delete_Matrix(int ** & a, int m);