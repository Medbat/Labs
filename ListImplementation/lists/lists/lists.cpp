#include "lists.h"

void whyIsItSoBad(int a) {
	if (a == 4) {
		cout << "ќшибка! Ёлемент не был добавлен. Ёто могло произойти по следующим причинам:\n";
		cout << " - список пуст\n";
		cout << " - элемент, после которого должна произойти вставка, не существует\n";
	}
	else
		if (a == 5) {
			cout << "ќшибка! Ёлемент не был удален. Ёто могло произойти по следующим причинам:\n";
			cout << " - список пуст\n";
			cout << " - такого элемента не существует\n";
		}
	if (a == 7) {
		cout << "ќшибка! Ёлементы не были перестановлены. Ёто могло произойти по следующим причинам:\n";
		cout << " - в списке менее двух элементов\n";
		cout << " - элементы с введенными ID не существуют";
	}

}

void addFirst(oneLin * & el, int a, char * b) {
	oneLin * t = new oneLin;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	if (el == NULL)
		t -> next = NULL;
	else
		t -> next = el;
	el = t;
}

void addLast(oneLin * & el, int a, char * b) {
	oneLin * t = new oneLin;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	t -> next = NULL;
	if (el == NULL) {
		el = t;
	}
	else {
		oneLin * next = el;
		while (next -> next != NULL) {
			next = next -> next; // GENIUS
		}
		next -> next = t;
	}
}

bool addSmwh(oneLin * & el, int a, char * b, int c) {
	if (el == NULL)
		return false;
	oneLin * prev = el;
	while (prev -> id != c && prev -> next != NULL)
		prev = prev -> next;
	if (prev -> id != c)
		return false;
	oneLin * t = new oneLin;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	t -> next = prev -> next;
	prev -> next = t;
	return true;
}

bool write(oneLin * el) {
	if (el == NULL)
		return false;
	oneLin * t = el;
	do {
		cout << t -> id << " " << t -> name << endl;
		t = t -> next;
	} while (t != NULL);
	return true;
}

bool deleteElement(oneLin * & el, int a) {
	if (el == NULL)
		return false;
	if (el -> id == a) {
		oneLin * toDel = el;
		el = el -> next;
		delete [] toDel -> name;
		delete [] toDel;
		return true;
	}
	oneLin * t = el;
	while (t -> next -> id != a && t -> next -> next != NULL)
		t = t -> next;
	if (t -> next -> id != a)
		return false;
	oneLin * toDel = t -> next;
	if (el == toDel)
		el = toDel -> next;
	t -> next = toDel -> next;
	delete [] toDel -> name;
	delete [] toDel;
	return true;
}

bool swapElements(oneLin * & el, int a, int b) {
	if (el == NULL)
		return false;
	if (el -> next == NULL)
		return false;
	if (a == b)
		return true;
	oneLin * first = el, * second = el, * t;
	int i = 1, j = 1;

	if (first -> id != a) {
		while (first != NULL && first -> id != a && i++)
			first = first -> next;
		if (first -> id != a)
			return false;
	}

	if (second -> id != b) {
		while (second != NULL && second -> id != b && j++)
			second = second -> next;
		if (second -> id != b)
			return false;
	}

	if (i > j)
		swap(first, second);
	
	if (first == el && second == el -> next) {
		el = second;
		oneLin * r = second -> next;
		first -> next = r;
		second -> next = first;
		return true;
	}
	
	if (first == el && second != el -> next) {
		t = el -> next;
		if (el -> id == b)
			swap(a, b);
		while (t -> next -> id != b)
			t = t -> next;
		el = second;
		swap(first -> next, second -> next);
		t -> next = first;
		return true;
	}

	if (first != el && second == first -> next) {
		t = el;
		if (second -> id == a)
			swap(a, b);
		while (t -> next -> id != a)
			t = t -> next;
		 
		t -> next = second;
		first -> next = second -> next;
		second -> next = first;
		return true;
	}

	if (first != el && second != first -> next) {
		oneLin * pf = el;
		oneLin * ps = el;
		if (first -> id == b)
			swap(a, b);
		while (pf -> next -> id != a)
			pf = pf -> next;
		while (ps -> next -> id != b)
			ps = ps -> next;
		pf -> next = second;
		ps -> next = first;
		swap(first -> next, second -> next);
		return true;
	}

}

void deleteAll(oneLin * & el) {
	if (el == NULL)
		return;
	oneLin * del = el;
	while (del != NULL) {
		del = el -> next;
		delete [] el -> name;
		delete [] el;
		el = del;
	}
}

bool dlFromFile(oneLin * & el, char file, int wh, int c) {
	char filename[11] = "data .txt";
	filename[4] = file;
	ifstream input(filename);
	if (!input) {
		cout << "‘айл " << filename << " не найден.\n";
		return true;
	}
	int id;
	char * buf = new char[1024];
	char * add;
	bool out = false;
	while (!input.eof() && !out) {
		input >> id;
		input >> buf;
		add = new char[strlen(buf) + 1];
		strcpy(add, buf);
		switch (wh) {
		case 0: 
			addFirst(el, id, add);
			break;
		case 1:
			addLast(el, id, add);
			break;
		case 2:
			if (!addSmwh(el, id, add, c)) {
				whyIsItSoBad(4);
				out = true;
			}
		}
	}
	delete [] buf;
	input.close();
	return out;
}

void addFirst(twoCycl * & el, int a, char * b) {
	twoCycl * t = new twoCycl;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	if (el == NULL) {
		t -> next = t;
		t -> prev = t;
	}
	else {
		t -> next = el;
		t -> prev = el -> prev;
		el -> prev -> next = t;
		el -> prev = t;
	}
	el = t;
}

void addLast(twoCycl * & el, int a, char * b) {
	twoCycl * t = new twoCycl;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	if (el == NULL) {
		el = t;
		el -> next = t;
		el -> prev = t;
		return;
	}
	t -> prev = el -> prev;
	t -> next = el;
	if (el -> next == el)
		el -> next = t;
	else
		el -> prev -> next = t;
	
	el -> prev = t;
}

bool addSmwh(twoCycl * & el, int a, char * b, int c) {
	if (el == NULL)
		return false;
	twoCycl * prev = el;
	while (prev -> id != c && prev -> next != NULL)
		prev = prev -> next;
	if (prev -> id != c)
		return false;
	twoCycl * t = new twoCycl;
	t -> id = a;
	t -> name = new char[strlen(b)+1];
	strcpy(t -> name, b);
	t -> next = prev -> next;
	t -> prev = prev;
	prev -> next -> prev = t;
	prev -> next = t;
	return true;
}

bool write(twoCycl * el) {
	if (el == NULL)
		return false;
	twoCycl * t = el;
		do {
			cout << t -> id << " " << t -> name << " " << t -> prev -> id << endl;
			t = t -> next;
		} while (t != el);
	return true;
}

bool deleteElement(twoCycl * & el, int a) {
	if (el == NULL)
		return false;
	twoCycl * t = el -> next;
	while (t -> id != a && t != el)
		t = t -> next;
	if (t -> id != a)
		return false;
	if (el -> next == el)
		el = NULL;
	if (el == t)
		el = t -> next;
	t -> prev -> next = t -> next;
	t -> next -> prev = t -> prev;
	delete [] t -> name;
	delete [] t;
	return true;
}

bool swapElements(twoCycl * & el, int a, int b) {
	if (el == NULL)
		return false;
	if (el -> next == NULL)
		return false;
	if (a == b)
		return true;
	twoCycl * first = el, * second = el, * t;
	int i = 1, j = 1;

	if (first -> id != a) {
		while (first != NULL && first -> id != a && i++)
			first = first -> next;
		if (first -> id != a)
			return false;
	}

	if (second -> id != b) {
		while (second != NULL && second -> id != b && j++)
			second = second -> next;
		if (second -> id != b)
			return false;
	}

	if (i > j) {
		swap(first, second);
		swap(a, b);
	}
	
	if (first == el && second == first -> next) {
		t = el -> prev;
		el = second;
		first -> next = second -> next;
		first -> prev = second;
		second -> next = first;
		second -> prev = t;
		first -> next -> prev = first;
		t -> next = second;
		return true;
	}
	
	if (first == el && second != el -> next) {
		twoCycl * last = el -> prev;
		twoCycl * s = el -> next;
		twoCycl * sp = second -> prev;
		twoCycl * sn = second -> next;

		el = second;
		first -> next = sn;
		first -> prev = sp;
		s -> prev = second;
		sn -> prev = first;
		sp -> next = first;
		second -> prev = last;
		last -> next = second;
		second -> next = s;
		return true;
}

	
	if (first != el && second == first -> next) {
		twoCycl * left = first -> prev;
		twoCycl * right = second -> next;

		left -> next = second;
		first -> prev = second;
		first -> next = right;
		right -> prev = first;
		second -> next = first;
		second -> prev = left;
		return true;
	}

	if (first != el && second != first -> next) {
		twoCycl * fl = first -> prev;
		twoCycl * fr = first -> next;
		twoCycl * sl = second -> prev;
		twoCycl * sr = second -> next;

		fl -> next = second;
		first -> prev = sl;
		second -> next = fr;
		sr -> prev = first;
		second -> prev = fl;
		sl -> next = first;
		fr -> prev = second;
		first -> next = sr;
		return true;

	}


}

void deleteAll(twoCycl * & el) {
	if (el == NULL)
		return;
	twoCycl * del = el, * ell = el;
	do {
		del = el -> next;
		delete [] el -> name;
		delete [] el;
		el = del;
	} while (del != ell);
	el = NULL;
}

bool dlFromFile(twoCycl * & el, char file, int wh, int c) {
	char filename[11] = "data .txt";
	filename[4] = file;
	ifstream input(filename);
	if (!input) {
		cout << "‘айл " << filename << " не найден.\n";
		return true;
	}
	int id;
	char * buf = new char[1024];
	char * add;
	bool out = false;
	while (!input.eof() && !out) {
		input >> id;
		input >> buf;
		add = new char[strlen(buf) + 1];
		strcpy(add, buf);
		switch (wh) {
		case 0: 
			addFirst(el, id, add);
			break;
		case 1:
			addLast(el, id, add);
			break;
		case 2:
			if (!addSmwh(el, id, add, c)) {
				whyIsItSoBad(4);
				out = true;
			}
		}
	}
	delete [] buf;
	input.close();
	return out;
}