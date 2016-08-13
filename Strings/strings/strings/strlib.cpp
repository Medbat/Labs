#include "strlib.h"

bool Check(char * s) {
	unsigned int i, chr;
	if (s[0] == '-') 
		s++;
	// hex
	if ( s[0] == '0' && s[1] == 'x' ) {
		if (strlen(s) == 2) 
			return false;
		for (i = 2; i < strlen(s); i++) {
			chr = (int)s[i];
			// A..F || 0..9
			if ( (chr > 64 && chr < 71) || (chr > 47 && chr < 58) )
				continue;
			return false;
		}
	}
	// oct
	else
		if (s[0] == '0') 
			for (i = 1; i < strlen(s); i++) {
				chr = (int)s[i];
				// 0..8
				if (chr > 47 && chr < 56)
					continue;
				return false;
			}
	// dec
	else {
		if (strlen(s) == 0) 
			return false;
		for (i = 0; i < strlen(s); i++) {
			chr = (int)s[i];
			// 0..9
			if (chr > 47 && chr < 58)
				continue;
			return false;
		}
	}
	return true;
}

SoN Find_SoN(char * s) {
	if (s[0] == '-') 
		s++;
	if (s[1] == 'x')
		return HEX;
	if (s[0] == '0')
		return OCT;
	else
		return DEC;
}

int Digits(int a) {
	int b = 0;
	while (a != 0) {
		a /= 10;
		b++;
	}
	return b;
}

bool Transfer(int &b, char * s) {
	if (!Check(s))
		return false;
	int a = 0, add, mod;
	unsigned int i;
	bool minus = false;
	SoN son = Find_SoN(s);
	// сохраняем минус, если он есть
	if (s[0] == '-')
		minus = true;
	// игнорируем определители СС и минус
	while (s[0] == '-' || s[0] == '0' || s[0] == 'x')
		s++;
	// если число слишком большое - возвращаем false
	if ( (son == 16 && Digits(a) > 4) || ( (son == 8 || son == 10) && Digits(a) > 5) )
		return false;
	mod = pow(double(son), (double)strlen(s));
	if (son == 10) {
		for (i = 0; i < strlen(s); i++) {
			mod /= son;
			a += ((int)s[i] - 48) * mod; 
		}
	}
	else 
		for (i = 0; i < strlen(s); i++) {
			int chr = (int) s[i];
			if (chr > 64 && chr < 71)
				add = chr - 55;
			if (chr > 47 && chr < 58)
				add = chr - 48;
			mod /= son;
			add *= mod;
			a += add;
		}
	if (minus)
		a = -a;
	b = a;
	if (b < -32768 || b > 32767)
		return false;
	return true;
}

void Give_Memory(int ** & a, int m, int n) {
	a = new int* [m];
	for (int i = 0; i < m; i++)
		a[i] = new int[n];
}

void Show_Matrix(int ** m, int a, int b) {
	int i, j;
	for (i = 0; i < a; i++) {
		for (j = 0; j < b; j++)
			cout << setw(8) << m[i][j];
		cout << endl;
	}
}

void Delete_Matrix(int ** & a, int m) {
	for (int i = 0; i < m; i++ )
        delete [] a[i];
    delete [] a;
}

void SuperCin(char * s, int &b) {
	bool first = false;
	do {
		if (first) 
			cout << "Неверный ввод. Попробуйте ещё раз.\n";
		first = true;
		cin >> s;
	}
	while (!Transfer(b, s));
}

void Qsort(int **& a, int constant, bool direction, int l, int r) {
	int i = l, j = r, m = a[(i + j) / 2][constant];
	do {
		if (direction) {
			while (a[i][constant] < m) 
				i++;
			while(a[j][constant] > m)
				j--;
		}
		else {
			while (a[i][constant] > m) 
				i++;
			while(a[j][constant] < m)
				j--;
		}
		if (i <= j) {
			swap(a[i][constant], a[j][constant]);
			i++;
			j--;
		}
  } while (i < j);
  if (l < j) 
	  Qsort(a, constant, direction, l, j);
  if (i < r) 
	  Qsort(a, constant, direction, i, r);
}