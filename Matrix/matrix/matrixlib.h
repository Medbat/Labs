#pragma once

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;

void Enter_Matrix(int ** &a, int &m, int &n);
void Show_Matrix(int ** m, int a, int b, int c, int d);
void Give_Memory(int ** & a, int m, int n);
void Delete_Matrix(int ** & a, int m);
void Load_Matrix_From_File(int ** & a, int &m, int &n, char file);
void Transponate_Matrix(int **& m, int a, int b, int c);
void Turn_Matrix(int **& m, int a, int b, int c);
void Calculate_B(int **& a, int m, int n, int &ba, int &bb, int &bdl);
void Go(int ** m, int a, int b, int c);
void Bubble_Sort(int **& m, int a, int b, int c);