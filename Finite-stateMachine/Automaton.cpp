#include "Automaton.h"

#include <fstream>

Automaton::Automaton(char* fileName)
{
	ifstream file(fileName);
	char buf[1024];
	// алфавит
	file >> alphabetN;
	alphabet = (char**)heap.get_mem(alphabetN * sizeof(char*));
	for (int i = 0; i < alphabetN; i++)
	{
		file >> buf;
		alphabet[i] = (char*)heap.get_mem(sizeof(char)* (strlen(buf) + 1));
		strcpy(alphabet[i], buf);
	}
	// состояния
	file >> statesN;
	states = (char**)heap.get_mem(statesN * sizeof(char*));
	for (int i = 0; i < statesN; i++)
	{
		file >> buf;
		states[i] = (char*)heap.get_mem(sizeof(char)* (strlen(buf) + 1));
		strcpy(states[i], buf);
	}
	// ошибки
	file >> errorsN;
	errors = (char**)heap.get_mem(errorsN * sizeof(char*));
	for (int i = 0; i < errorsN; i++)
	{
		file >> buf;
		file.getline(buf, 1023, '.');
		errors[i] = (char*)heap.get_mem(sizeof(char)* (strlen(buf)));
		strcpy(errors[i], &buf[1]);
	}
	// таблица
	tableM = alphabetN;
	tableN = statesN;
	table = (char**)heap.get_mem(sizeof(char*) * tableM * tableN);
	for (int i = 0; i < tableN; i++)
	{
		file >> buf;
		for (int j = 0; j < tableM; j++)
		{
			file >> buf;
			table[i * tableM + j] = (char*)heap.get_mem(sizeof(char)* (strlen(buf) + 1));
			strcpy(table[i * tableM + j], buf);
		}
	}
	file.close();
	/*table = (char***)heap.get_mem(sizeof(char**) * tableM);
	for (int i = 0; i < tableM; i++)
		table[i] = (char**)heap.get_mem(sizeof(char*) * tableN);
	for (int i = 0; i < tableM; i++)
	{
		for (int j = 0; j < tableN; j++)
		{
			file >> buf;
			table[i][j] = (char*)heap.get_mem(sizeof(char)* (strlen(buf) + 1));
			strcpy(table[i][j], buf);
		}
	}*/
}

void Automaton::Test()
{
	for (int i = 0; i < alphabetN; i++)
		cout << alphabet[i] << endl;
	for (int i = 0; i < statesN; i++)
		cout << states[i] << " ";
	cout << endl;
	for (int i = 0; i < errorsN; i++)
		cout << errors[i] << endl;
	cout << endl;
	for (int i = 0; i < tableN; i++)
	{
		for (int j = 0; j < tableM; j++)
			cout << table[i * tableM + j] << " ";
		cout << endl;
	}
}

char* Automaton::define(char* source, int &position, char* &error, bool trace)
{
	ofstream tracer; 
	if (trace)
		tracer.open("trace.txt");
	char* currentState = states[0];
	while (true)
	{
		if (trace)
		{
			tracer << "State: " << currentState << ". Symbol " << position << ": ";
			if (source[position] == '\0')
				tracer << "TERMINATOR";
			else 
				tracer << source[position];
			tracer << endl;
		}
		// если достигнут конец строки - возвращаем текущее состояние
		if (source[position] == '\0')
		{
			if (trace)
			{
				tracer << "End of line was found. Returning current state <" << currentState << ">" << endl;
				tracer.close();
			}
			position--;
			return currentState;
		}
		// ищем символ в алфавите
		bool found = false;
		int i, j;
		for (i = 0; i < alphabetN; i++)
		{
			j = 0;
			while (alphabet[i][j] != '\0')
			{
				if (alphabet[i][j] == source[position])
				{
					found = true;
					break;
				}
				j++;
			}
			if (found)
				break;
		}
		// если символ не найден, значит лексема закончилась
		if (!found)
		{
			if (trace)
			{
				tracer << "Decision not found: returning state <" << currentState << ">\n";
				tracer.close();
			}
			position--;
			return currentState;
		}
		// иначе продолжаем
		int stateN = 0;
		// ищем номер текущего состояния
		while (true)
		{
			if (strcmp(currentState, states[stateN]))
				stateN++;
			else
				break;
		}
		int tableIndex = stateN * tableM + i;
		// если в таком случае выходит ошибка, возвращаем её
		if (table[tableIndex][0] == '#')
		{
			if (trace)
			{
				tracer << "Decision found: error. Description: <" 
					<< errors[table[tableIndex][1] - '1'] << "> at " << position << "\n";
				tracer.close();
			}
			error = errors[table[tableIndex][1] - '1'];
			return table[tableIndex];
		}
		// если встретили ключевое слово STOP, возвращаем последнее состояние
		if (!strcmp(table[tableIndex], "STOP"))
		{
			if (trace)
			{
				tracer << "Decision found: STOP. Returning current state: <" << currentState << ">\n";
				tracer.close();
			}
			position--;
			return currentState;
		}
		if (trace)
		{
			tracer << "Desicion found: " << table[tableIndex] << endl;
		}
		currentState = table[tableIndex];
		position++;
	}
}
