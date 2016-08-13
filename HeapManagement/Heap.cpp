#include "heap.h"

void* Heap::get_mem(int size)
{
	if (size > segment_size)
	{
		cout << "���������� �������� ������ �������� " << size << ": �������� ������ �������� (" << segment_size << ")\n";
		return NULL;
	}
	if (current == NULL)
		make_segment();
	Segment *temp = current;
	// �������� �� ���� ���������
	while (temp != NULL)
	{
		
		// ��������� �� ���� ��������� ��������
		for (int i = temp->descriptor_count - 1; i >= 0; i--)
		{
			// ���� ����� ������ ����� ������
			if (temp->descriptor[i].used == false)
			{
				// ���� ������ ��������
				if (temp->descriptor[i].size >= size)
				{
					// ���� ������ �������� �� �����
					if (temp->descriptor[i].size != size)
					{
						// � ������������ �� ������ ��� ������ �������
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
						// ������� ����������� ��� ���������� ������ � ��������
						for (int j = temp->descriptor_count; j > i + 1; j--)
							temp->descriptor[j] = temp->descriptor[j - 1];
						// ��������� ����� ������ �� ��� ����� - ����������� ������ � ���������� �� �����
						temp->descriptor[i + 1].size = temp->descriptor[i].size - size;
						temp->descriptor[i + 1].ptr = (char*)(temp->descriptor[i].ptr) + size;
						temp->descriptor[i + 1].used = false;
						temp->descriptor[i].size = size;
						// � ���������� ���������� �������� �����������
						temp->descriptor_count++;
					}
					temp->descriptor[i].used = true;
					return temp->descriptor[i].ptr;
				}
			}
		}
		// ��������� �� ������ �������
		temp = temp->prev;
		// ���� ������ �� �������, �������� ����� ������� - ������ ����� ������
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
		cout << "������� " << j << endl;
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
	// ����� �� ���� ���������
	while (temp != NULL)
	{
		// ����� �� ������ ������
		for (int i = temp->descriptor_count - 1; i >= 0; i--)
		{
			// ���� ��� ������ ����� ������, ����������� ��� � �� ����������� ������ � �������
			if (temp->descriptor[i].ptr == ptr)
			{
				temp->descriptor[i].used = false;
				int ind = -1;
				int both = 0;
				// ����� ����� �������� - ����������� ��
				if (i > 0 && temp->descriptor[i - 1].used == false)
				{
					ind = 0;
					both++;
				}

				// ����� ������ �������� - ��������� ���
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

