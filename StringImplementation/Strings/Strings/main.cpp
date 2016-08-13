#include "headers.h"

int main()
{
	setlocale(LC_ALL, "rus");
	// Объявление объектов через различные конструкторы и их вывод
	MedString a, b("string"), c(15), d(1.2), e(b);
	cout << a << endl << b << endl << c << endl << d << endl << e << endl;
	// Присоединение и приравнивание
	a = 16;
	b = 12.4;
	c = "Stroka";
	d = b;
	cout << a << endl << b << endl << c << endl << d << endl;
	a += 9;
	a += 1.3;
	a += "qwe";
	a += a;
	cout << a << endl;
	// []
	try
	{
		for (int i = 0; i < Tlen(c) + 1; i++)
			cout << i << ": " << c[i] << endl;
	}
	catch (char *s)
	{
		cout << s << endl;
	}
	// Tcopy, len
	a.Tcopy("to copy");
	cout << a << " (" << a.len() << ")" << endl;
	// +, swap
	b = "1234";
	c = "5678";
	a = b + c;
	MedSwap(b, c);
	cout << a << endl << b << " " << c << endl;
	// Ttrim
	a = " \t   qwer  qer cad \n";
	a = Ttrim(a);
	cout << a << endl;
	// <, >, ==
	a = "qwerty";
	b = "qwer";
	c = "qwer";
	cout << (b == c) << " " << (a < b) << " " << (a > b) << endl;
	// pos, del, nextpos, del[2], delall, ins
	a = "qwer";
	b = "e";
	cout << a.pos(b) << endl;
	a.del(b);
	cout << a << endl;
	a = "string string";
	b = "ri";
	cout << a.nextpos(b) << endl;
	a.del(2, 4);
	cout << a << endl;
	try
	{
		a.del(4, 144);
	}
	catch (char *s)
	{
		cout << s << endl;
	}
	a = "string string";
	b = "ri";
	a.delall(b);
	cout << a << endl;
	a.ins(b, 0);
	cout << a << endl;
	// replace, replaceall
	a = "we we wewe r t we";
	b = "we";
	c = 15;
	a.replace(b, c);
	cout << a << endl;
	a.replaceall(b, c);
	cout << a << endl;
	// lower, upper
	a = "ASDASFASDFASDF";
	a.lower();
	cout << a << endl;
	a.upper();
	cout << a << endl;
	// reverse
	d = 15623.12;
	d.reverse();
	cout << d << endl;


	system("pause");
	return 0;
}
