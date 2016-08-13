#include "heap.h"

void* Heap::get_mem(int size)
{
	if (size > segment_size)
	{
		cout << "Невозможно выделить память размером " << size << ": превышен размер сегмента (" << segment_size << ")\n";
		return NULL;
	}
	if (current == NULL)
		make_segment();
	Segment *temp = current;
	// проходим по всем страницам
	while (temp != NULL)
	{
		
		// пробегаем по всем элементам сегмента
		for (int i = temp->descriptor_count - 1; i >= 0; i--)
		{
			// если нашли пустой кусок памяти
			if (temp->descriptor[i].used == false)
			{
				// если размер подходит
				if (temp->descriptor[i].size >= size)
				{
					// если размер подходит не точно
					if (temp->descriptor[i].size != size)
					{
						// и дескрипторов не хватит для нового деления
						if (temp->descriptor_count == SEGMENTCOUNT)
						{
							temp = temp->prev;
							if (temp == NULL)
							{
								make_segment();
								temp = current;
							}
							continue;
						}
						// смещаем дескрипторы для добавления нового в середину
						for (int j = temp->descriptor_count; j > i + 1; j--)
							temp->descriptor[j] = temp->descriptor[j - 1];
						// разделяем кусок памяти на два новых - запрошенная память и оставшаяся от куска
						temp->descriptor[i + 1].size = temp->descriptor[i].size - size;
						temp->descriptor[i + 1].ptr = (char*)(temp->descriptor[i].ptr) + size;
						temp->descriptor[i + 1].used = false;
						temp->descriptor[i].size = size;
						// в результате количество кусочков увеличилось
						temp->descriptor_count++;
					}
					temp->descriptor[i].used = true;
					return temp->descriptor[i].ptr;
				}
			}
		}
		// переходим на другой сегмент
		temp = temp->prev;
		// если памяти не хватило, выделяем новый сегмент - теперь точно хватит
		if (temp == NULL)
		{
			make_segment();
			temp = current;
		}
	}
}

void Heap::Test()
{
	Segment* temp = current;
	int j = 0;
	while (temp != NULL)
	{
		cout << "Сегмент " << j << endl;
		for (int i = 0; i < temp->descriptor_count; i++)
		{
			cout << i << ": " << temp->descriptor[i].ptr << " " << temp->descriptor[i].size <<
				" " << ((temp->descriptor[i].used)?"busy":"free") << endl;
		}
		j++;
		temp = temp->prev;
	}
}

void Heap::free_mem(void* ptr)
{
	Segment* temp = current;
	// бежим по всем страницам
	while (temp != NULL)
	{
		// бежим по кускам памяти
		for (int i = temp->descriptor_count - 1; i >= 0; i--)
		{
			// если это нужный кусок памяти, освобождаем его и по возможности мержим с соседом
			if (temp->descriptor[i].ptr == ptr)
			{
				temp->descriptor[i].used = false;
				int ind = -1;
				int both = 0;
				// сосед слева свободен - поглощаемся им
				if (i > 0 && temp->descriptor[i - 1].used == false)
				{
					ind = 0;
					both++;
				}

				// сосед справа свободен - поглощаем его
				if (i < temp->descriptor_count - 1 && temp->descriptor[i + 1].used == false)
				{
					ind = 1;
					both++;
				}

				for (int k = 0; k < both; k++)
				{
					temp->descriptor[i - 1 + ind].size += temp->descriptor[i + ind].size;
					for (int j = i + ind; j < temp->descriptor_count - 1; j++)
						temp->descriptor[j] = temp->descriptor[j + 1];
					temp->descriptor_count--;
					ind = 0;
				}

				return;
			}
		}
		temp = temp->prev;
	}
}

int Heap::make_segment()
{
	Segment* temp = new Segment;
	temp->data = malloc(segment_size);
	temp->prev = current;
	temp->descriptor[0].ptr = temp->data;
	temp->descriptor[0].used = false;
	temp->descriptor[0].size = segment_size;
	temp->descriptor_count = 1;
	current = temp;
	return 0;
}

void Heap::delete_segments()
{
	Segment* temp = current;
	while (current != NULL)
	{
		temp = current;
		current = current->prev;
		free(temp->data);
	}
}

