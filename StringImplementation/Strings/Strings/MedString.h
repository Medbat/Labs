#pragma once
#include <iostream>
using namespace std;

class MedString
{
private:
	char *String;
public:
	// конструкторы
	MedString(void);
	MedString(MedString &From);
	MedString(char *From);
	MedString(int From);
	MedString(double From);
	// деструктор
	~MedString();
	// перегрузки операций +=, = для char*, int, double, MedString
	MedString &operator += (char *add);
	MedString &operator += (int add);
	MedString &operator += (double add);
	MedString &operator += (MedString add);

	MedString &operator = (char *add);
	MedString &operator = (int add);
	MedString &operator = (double add);
	MedString &operator = (MedString add);
	//перегрузка оператора []
	char& operator[](int count) throw(...);
	// методы
	void Tcopy(char *Source);
	int len();
	int pos(MedString& what);
	void del(MedString& what);
	int nextpos(MedString& what);
	void del(int begin, int length) throw(...);
	void delall(MedString& what);
	void ins(MedString& what, int whereto) throw(...);
	void replace(MedString& what, MedString& replace_with);
	void replaceall(MedString& what, MedString& replace_with);
	void trim();
	void lower();
	void upper();
	int to_int() throw(...);
	double to_double() throw(...);
	void reverse();
	// дружественные функции
	friend void Copy(MedString& Dest, MedString& Source);
	friend int Tlen(MedString& Copy);
	friend MedString operator+(MedString& first, MedString& second);
	friend void MedSwap(MedString& first, MedString &second);
	friend MedString Ttrim(MedString& from);
	friend bool operator>(MedString& first, MedString& second);
	friend bool operator<(MedString& first, MedString& second);
	friend bool operator==(MedString& first, MedString& second);
	friend ostream& operator<<(ostream& out, MedString& p);
	
};

int CharLen(char *s);
void CharCpy(char *&Dest, char *Source);
char* validDouble(char *s);
