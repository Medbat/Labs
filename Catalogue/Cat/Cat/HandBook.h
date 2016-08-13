#pragma once
#include "BaseField.h"

class HandBook
{
protected:
	BaseField ***data;
	int count;
	char *name;
	char **colName;
	void getMemory(BaseField***);
public:
	HandBook(int);
	~HandBook(void);
	void deleteData();
	void read();
	void show();
	void sort(int);
	void add(char *);
	bool del(char *, int);
	bool edit(char *toReplace, char *New);
	void Report1();
	void Report2(char *code);
	void reWrite();
	bool validate(char *s, int type);
	int find(char *toFind, int Col); 
	// находит элемент с содержанием toFind в столбце Col; -1 при отстутствии, инчае индекс в data
};

