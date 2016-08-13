#include "headers.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>

char **split(char *s)
{
	char **ss;
	ss = new char*[5];
	for (int i = 0; i < 5; i++)
		ss[i] = new char[100];
	int it = 0, w = 0, lit = 0;
	while (it <= strlen(s))
	{
		if (s[it] != ',')
			ss[w][lit++] = s[it];
		else
		{
			ss[w++][lit] = '\0';
			lit = 0;
		}
		it++;
	}
	return ss;
}
bool validator(char *s, char type)
{
	switch (type)
	{
	case '0':
		return true;
	case '1':
		for (int i = 0; i < strlen(s); i++)
			if (!isdigit(s[i]))
				return false;
		return true;
	case '2':
		if (strlen(s) != 10)
			return false;
		for (int i = 0; i < 10; i++)
		{
			if (i == 2 || i == 5)
				if (s[i] != '.')
					return false;
				else
					continue;
			if (!isdigit(s[i]))
				return false;
		}
		return true;
	case '3':
		if (strcmp(&s[strlen(s)-3],"EUR") != 0 && strcmp(&s[strlen(s)-3],"RUR") != 0)
			return false;
		for (int i = 0; i < strlen(s) - 3; i++)
			if (!isdigit(s[i]))
				return false;
		return true;
	}
	return false;
}
bool HandBook :: validate(char *s, int type)
{
	if (strlen(s) < 10)
		return false;
	if (s[strlen(s) - 1] == ',')
		return false;
	int comma = 0;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == ',')
		{
			comma++;
			if (i != 0 && s[i - 1] == ',')
				return false;
		}
	}
	if (comma != 4)
		return false;
	char **words = split(s);
	char *types = new char[1024];
	// 0 - строка, 1 - число, 2 - дата, 3 - деньги
	switch (type)
	{
	case 1:
		strcpy(types, "00001");
		break;
	default:
		strcpy(types, "10213");
	}
	for (int i = 0; i < 5; i++)
		if (!validator(words[i], types[i]))
			return false;
	return true;
}
int getRurValue(char *s)
{
	bool rurEur;
	if (s[strlen(s) - 3]=='E') 
		rurEur = true;
	else 
		rurEur = false;
	int value = atoi(s);
	if (rurEur)
		value *= 40;
	return value;
}
HandBook::HandBook(int type)
{
	data = NULL;
	count = 0;
	name = new char[12];
	colName = new char*[5];
	for (int i = 0; i < 5; i++)
		colName[i] = new char[10];
	switch (type)
	{
	case 1:
		strcpy(name, "catalog.csv");
		strcpy(colName[0], "код");
		strcpy(colName[1], "им€");
		strcpy(colName[2], "номенкл");
		strcpy(colName[3], "габариты");
		strcpy(colName[4], "масса");
		break;
	case 2:
		strcpy(name, "buy.csv");
		strcpy(colName[0], "номер");
		strcpy(colName[1], "код");
		strcpy(colName[2], "дата");
		strcpy(colName[3], "кол-во");
		strcpy(colName[4], "цена");
		break;
	case 3:
		strcpy(name, "sale.csv");
		strcpy(colName[0], "номер");
		strcpy(colName[1], "код");
		strcpy(colName[2], "дата");
		strcpy(colName[3], "кол-во");
		strcpy(colName[4], "цена");
		break;
	case 4:
		strcpy(name, "ќтчет 1");
		strcpy(colName[0], "им€");
		strcpy(colName[1], "в наличии");
		strcpy(colName[2], "потрачено");
		strcpy(colName[3], "выручено");
		break;
	case 5:
		strcpy(name, "ќтчет 2");
		strcpy(colName[0], "п/п");
		strcpy(colName[1], "дата");
		strcpy(colName[2], "кол-во");
		strcpy(colName[3], "сумма");
	}
}
HandBook::~HandBook()
{
	deleteData();
	delete [] name;
	for (int i = 0; i < 5; i++)
		delete colName[i];
	delete [] colName;
	count = 0;
}
void HandBook :: deleteData()
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 5; j++)
			delete data[i][j];
		delete [] data[i];
	}
	data = NULL;
	count = 0;
}
void HandBook :: read()
{
	ifstream file(name);
	int Rows = 0, badFields = 0;
	char *buf = new char[1024];
	while (!file.eof())
	{
		file >> buf;
		if (validate(buf, (name[0] == 'c')?1:2))
			Rows++;
	}
	file.close();
	file.open(name);
	data = new BaseField **[Rows];
	count = 0;
	char *buf1 = new char[1024];
	while (!file.eof())
	{
		char ch;
		int bufN = 0;
		file.get(ch);
		do
		{
			buf[bufN++] = ch;
			file.get(ch);
		} while (ch != '\n' && !file.eof());
		buf[bufN] = '\0';
		bufN = 0;
		if (!validate(buf, (name[0] == 'c')?1:2))
		{
			cout << buf << "\n«апись пропущена из-за неверного формата\n";
			badFields++;
			continue;
		}
		data[count++] = new BaseField *[5];
		getMemory(data);
		for (int fieldCount = 0; fieldCount < 5; fieldCount++)
		{
			int i = 0;
			do
			{
				buf1[i] = buf[bufN];
				i++;
				bufN++;
			} while (buf[bufN] != ',' && buf[bufN] != '\0');
			buf1[i] = '\0';
			bufN++;
			data[count - 1][fieldCount] -> set(buf1);
		}
	}
	file.close();
	cout << "¬сего неверно заданных записей: " << badFields << endl;
}
void HandBook :: getMemory(BaseField ***d)
{
	switch (name[0])
	{
	case 'c':
		d[count - 1][0] = new TextField;
		d[count - 1][1] = new TextField;
		d[count - 1][2] = new TextField;
		d[count - 1][3] = new TextField;
		d[count - 1][4] = new NumberField;
		break;
	case 'b':
	case 's':
		d[count - 1][0] = new NumberField;
		d[count - 1][1] = new TextField;
		d[count - 1][2] = new DataField;
		d[count - 1][3] = new NumberField;
		d[count - 1][4] = new MoneyField;
	}
	if (name[6] == '1')
	{
		d[count - 1][0] = new TextField;
		d[count - 1][1] = new NumberField;
		d[count - 1][2] = new MoneyField;
		d[count - 1][3] = new MoneyField;
		
		d[count - 1][4] = new NumberField;
	}
	if (name[6] == '2')
	{
		d[count - 1][0] = new TextField;
		d[count - 1][1] = new DataField;
		d[count - 1][2] = new NumberField;
		d[count - 1][3] = new MoneyField;

		d[count - 1][4] = new NumberField;
	}
}
void HandBook :: show()
{
	cout << name << endl;
	int line = (name[0] == 'ќ')?70-14:70;
	int nn = (name[0] == 'ќ')?4:5;
	for (int i = 0; i < line; i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < nn; i++)
		cout << " " << setw(10) << colName[i] << "  |";
	cout << endl;
	for (int i = 0; i < line; i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < nn; j++)
			cout << " " << setw(10) << *data[i][j] << "  |";
		cout << endl;
	}
	for (int i = 0; i < line; i++)
		cout << "-";
	cout << endl << "¬сего записей: " << count << endl;
}
void HandBook :: sort(int col)
{
	for (int i = count - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (data[j][col] -> bigger(data[j][col] -> getValue(), data[j + 1][col] -> getValue()))
				swap(data[j], data[j + 1]);
}
void HandBook :: add(char *s)
{
	char **ss = split(s);
	int n = count + 1;
	BaseField ***newData = new BaseField**[n];
	count = 0;
	for (; count < n; count++)
	{
		newData[count] = new BaseField *[5];
		count++;
		getMemory(newData);
		count--;
		if (count == n - 1)
			break;
		for (int i = 0; i < 5; i++)
			newData[count][i] -> set(data[count][i] -> getValue());
	}
	deleteData();
	data = newData;
	newData = NULL;
	count = n;
	for (int i = 0; i < 5; i++)
		data[count - 1][i] -> set(ss[i]);
}
int HandBook :: find(char *toFind, int Col)
{
	int n = -1;
	for (int i = 0; i < count; i++)
	{
		//cout << data[i][0] -> getValue() << endl;
		if (!strcmp(toFind, data[i][Col] -> getValue())) // watch не видит второй параметр
		{
			n = i;
			break;
		}
	}
	return n;
}
bool HandBook :: del(char *s, int Col)
{
	int toDel = find(s, Col);
	if (toDel < 0)
		return false;
	for (int i = toDel; i < count - 1; i++)
		swap(data[i], data[i + 1]);
	delete data[count - 1];
	count--;
	return true;
}
bool HandBook :: edit(char *toReplace, char *New)
{
	int toEdit = find(toReplace, 0);
	if (toEdit < 0)
		throw "not found";
	char **s = split(New);
	for (int i = 0; i < 5; i++)
		data[toEdit][i] -> set(s[i]);
	return true;
}
void HandBook :: Report1()
{

	HandBook cat(1), buy(2), sale(3);
	cat.read();
	buy.read();
	sale.read();
	
	for (int i = 0; i < cat.count; i++) // проходимс€ по каталогу дл€ сбора данных о товаре
	{

		char *itemName;
		int stock = 0, buyValue = 0, sellValue = 0; // обнул€ем переменные
		itemName = new char[strlen(cat.data[i][1]->getValue()) + 1]; // выдел€ем пам€ть под название товара
		strcpy(itemName, cat.data[i][1]->getValue()); // записываем название товара

		while (buy.find(cat.data[i][0]->getValue(), 1) != -1) // пока в покупках есть записи покупок данного товара
		{
			// находим в покупках нужный товар
			int ind = buy.find(cat.data[i][0]->getValue(), 1); 
			// прибавл€ем число закупленного
			stock += atoi(buy.data[ind][3] -> getValue());
			// прибавл€ем стоимость
			buyValue += atoi(buy.data[ind][3] -> getValue()) * getRurValue(buy.data[ind][4] -> getValue());
			// удал€ем обработанную строку
			buy.del(cat.data[i][0]->getValue(), 1);
		}

		while (sale.find(cat.data[i][0]->getValue(), 1) != -1) // пока в продажах есть записи продаж данного товара
		{
			// находим в продажах нужный товар
			int ind = sale.find(cat.data[i][0]->getValue(), 1); 
			// убавл€ем число на количество проданных товаров
			stock -= atoi(sale.data[ind][3] -> getValue());
			// прибавл€ем выручку
			sellValue += atoi(sale.data[ind][3] -> getValue()) * getRurValue(sale.data[ind][4] -> getValue());
			// удал€ем обработанную строку
			sale.del(cat.data[i][0]->getValue(), 1);
		}

		char *buf = new char[1024], *uBuf = new char[1024];
		strcpy(buf, itemName);
		strcat(buf, ",");
		strcat(buf, itoa(stock, uBuf, 10));
		strcat(buf, ",");
		strcat(buf, itoa(buyValue, uBuf, 10));
		strcat(buf, "RUR");
		strcat(buf, ",");
		strcat(buf, itoa(sellValue, uBuf, 10));
		strcat(buf, "RUR");
		strcat(buf, ",0");
		add(buf);
		
		delete [] itemName;
		delete [] buf;
		delete [] uBuf;
	}
}
void HandBook :: Report2(char *code)
{
	HandBook buy(2), sale(3);
	buy.read();
	sale.read();
	char *toAdd = new char[1024];

	while (buy.find(code, 1) != -1)
	{
		int ind = buy.find(code, 1);
		sprintf(toAdd, "покупка,%s,%s,%dRUR", buy.data[ind][2]->getValue(), buy.data[ind][3]->getValue(), 
			atoi(buy.data[ind][3]->getValue()) * getRurValue(buy.data[ind][4]->getValue()));
		buy.del(code, 1);
		add(toAdd);
	}

	while (sale.find(code, 1) != -1)
	{
		int ind = sale.find(code, 1);
		sprintf(toAdd, "продажа,%s,%s,%dRUR", sale.data[ind][2]->getValue(), sale.data[ind][3]->getValue(), 
			atoi(sale.data[ind][3]->getValue()) * getRurValue(sale.data[ind][4]->getValue()));
		sale.del(code, 1);
		add(toAdd);
	}
}
void HandBook :: reWrite()
{
	FILE *f = fopen(name, "w");
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			fprintf(f, "%s", data[i][j]->getValue());
			if (j != 4)
				fprintf(f, ",");
		}
		if ( i != count - 1)
			fprintf(f, "\n");
	}
	fclose(f);
}