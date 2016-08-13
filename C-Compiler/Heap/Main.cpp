
#include "stdafx.h"
#include "Compiler.h"
#include "locale.h"

int main()
{
	setlocale(LC_ALL, "rus");
	Compiler* compiler = new Compiler();
	compiler->Compile("test.txt");
}
