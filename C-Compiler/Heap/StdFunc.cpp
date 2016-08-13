#pragma once
#include "StdFunc.h"
#include "stdafx.h"
long long int fact(int x)
{
	if (x == 0) return 1;
	return x*fact(x - 1);
}
double pow(double num, int degree)// ћожно сделать быстрое возведение в степень
{
	double ans = 1;
	for (int i = 0; i < degree; i++)
		ans *= num;
	return ans;
}


double sin(double x)
{
	int i = 0;
	double ans = 0;
	while (i != 10)
	{
		ans += (i % 2 == 0 ? 1 : -1)*pow(x, 2 * i + 1) / fact(2 * i + 1);
		i++;
	}
	return ans;
}
double cos(double x)
{
	int i = 0;
	double ans = 0;
	while (i != 10)
	{
		ans += (i % 2 == 0 ? 1 : -1)*pow(x, 2 * i) / fact(2 * i);
		i++;
	}
	return ans;
}

int max(int a, int b)
{
	return (a > b ? a : b);
}
double max(double a, double b)
{
	return (a > b ? a : b);
}

int min(int a, int b)
{
	return (a < b ? a : b);
}
double min(double a, double b)
{
	return (a < b ? a : b);
}
