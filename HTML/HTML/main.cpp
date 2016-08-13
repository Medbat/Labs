

#include "HTML.h"

ostream &operator<<(ostream &out, Elem &e)
{
	out << e.str();
	return out;
}

int main()
{
	setlocale(LC_ALL, "rus");
	P example;
	Text t("Privet, ");
	example.push_back(&t);

	Em e;
	e.push_back(new Text("mir"));
	example.push_back(&e);

	A a("http://asd.qw");
	a.push_back(new Text("ssylko"));
	example.push_back(&a);

	Strong *ss;

	example.push_back(new Text("text"))
		.push_back(&((ss = new Strong)
		->push_back(new Text("vydelenie"))
		.push_back(&((new Em)->push_back(new Text("escho")))))); 


	ss->push_back(new Text("AZAZAZA"));

	
	cout << example.str();
	
	cout << endl;
	system("pause");
	return 0;
}
