#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

struct oneLin {
	int id;
	char * name;
	oneLin * next;
};

struct twoCycl {
	int id;
	char * name;
	twoCycl * next;
	twoCycl * prev;
};

void whyIsItSoBad(int);

void addFirst(oneLin * &, int, char *);
void addLast(oneLin * &, int, char *);
bool addSmwh(oneLin * &, int, char *, int);
bool write(oneLin *);
bool deleteElement(oneLin * &, int);
bool swapElements(oneLin * &, int, int); // Õ¿ –≈ ŒÕ—“–” ÷»»
void deleteAll(oneLin * &);
bool dlFromFile(oneLin * &, char, int, int = 0);

void addFirst(twoCycl * &, int, char *);
void addLast(twoCycl * &, int, char *);
bool addSmwh(twoCycl * &, int, char *, int);
bool write(twoCycl *);
bool deleteElement(twoCycl * &, int);
bool swapElements(twoCycl * &, int, int); // Õ¿ –≈ ŒÕ—“–” ÷»»
void deleteAll(twoCycl * & el);
bool dlFromFile(twoCycl * &, char, int, int = 0);