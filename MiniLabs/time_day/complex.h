#define _CRT_SECURE_NO_WARNINGS


#include <iostream>

using namespace std;

class Complex {
	double re, im;
public:
	Complex(): im(0), re(0) { };
	Complex(double re, double im)
	{
		this->im = im;
		this->re = re;
	}

	void set(double re, double im)
	{
		this->re = re;
		this->im = im;
	}

	const Complex &operator++()
	{
		this->re++;
		return *this;
	}

	const Complex &operator++(int trash)
	{	
		this->re++;
		return Complex(re - 1, im);
	}

	const Complex &operator=(const Complex &a)
	{
		this->re = a.re;
		this->im = a.im;
		return *this;
	}

	const bool &operator==(const Complex &a)
	{
		if (a.re == re && a.im == im)
			return true;
		else
			return false;
	}

	const Complex &operator+(const Complex &a)
	{
		int i = im + a.im;
		int r = re + a.re;
		return Complex(r, i);
	}

	const Complex &operator-(const Complex &a)
	{
		int i = im - a.im;
		int r = re - a.re;
		return Complex(r, i);
	}
	
	friend const Complex &operator*(const Complex &a, const Complex &b)
	{
		return Complex(a.re * b.re - a.im * b.im, a.im * b.re + a.re * b.im);
	}

	friend const Complex &operator/(const Complex &a, const Complex &b)
	{
		return Complex((a.re * b.re + a.im * b.im)/(b.re * b.re + b.im * b.im), (a.im*b.re-a.re*b.im)/(b.im * b.im + b.re * b.re));
	}

	friend ostream& operator<<(ostream& out, const Complex& p)
	{
		out << "(" << p.re << ", " << p.im << "i)";
		return out;
	}

};