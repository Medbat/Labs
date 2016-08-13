#include "stdafx.h"
#include "Heap.h"


int Heap::make_segment()
{
	Segment* newseg = new Segment(segment_size);
	newseg->prev = current;
	newseg->descriptor[0].size = segment_size;
	current = newseg;
	return 1;
}

void Heap::delete_segments()
{
	while (current != NULL)
	{
		Segment* toDel = current->prev;
		delete current;
		current = toDel;
	}
}

void* Heap::get_mem(int size)
{
	if (size > segment_size || size <= 0) return NULL;
	Segment* curseg = current;
	int maxsize = 0;
	Segment* maxseg = NULL;
	int numToRemove = 0;
	int numToReplace = 0;
	for (curseg = current; curseg; curseg=curseg->prev)
	{
		for (int i = 0; i < curseg->descriptor_count; i++)
		{
			if (curseg->descriptor[i].used) continue;
			if (curseg->descriptor[i].size == size)   // случай нереального везения
			{
				curseg->descriptor[i].used = true;
				return (void*)((int)curseg->data + curseg->descriptor[i].offset);
			}

			numToRemove = 0;
			for (int j = i + 1; !(curseg->descriptor[j].used) && j<curseg->descriptor_count; j++)
			{
				curseg->descriptor[i].size += curseg->descriptor[j].size;
				numToRemove++;
			}
			if (numToRemove > 0)
			{
				for (int j = i + 1; j < (curseg->descriptor_count) - numToRemove; j++)
					copySegDef(curseg, j + numToRemove, j, j + numToRemove, j, j - 1, j);
				curseg->descriptor_count -= numToRemove;
			}
			if (i == curseg->descriptor_count - 1)
			{
				if (maxsize < curseg->descriptor[i].size && curseg->descriptor_count<SEGMENTCOUNT)
				{
					maxsize = curseg->descriptor[i].size;
					maxseg = curseg;
				}
				continue;
			}

			numToReplace = 0;
 			copySegDef(curseg, i, SEGMENTCOUNT, i, SEGMENTCOUNT);
			for (int j = i + 1; curseg->descriptor[j].used && j < curseg->descriptor_count; j++)
			{
				copySegDef(curseg, j, j - 1, j, j - 1, j - 2, j - 1);
				numToReplace++;
			}
			copySegDef(curseg, SEGMENTCOUNT, i + numToReplace, SEGMENTCOUNT, i + numToReplace, i + numToReplace - 1, i + numToReplace);
			i += numToReplace - 1;
		}
	}
	if (maxsize < size)
	{
		make_segment();
		if (segment_size == size)
		{
			current->descriptor[0].used = true;
			return current;
		}
		newSettings(current, 1, size);
		return (void*)current->data;
	}
	newSettings(maxseg, maxseg->descriptor_count, size);
	return (void*)((int)maxseg->data + 8 * maxseg->descriptor[maxseg->descriptor_count - 2].offset);
}

void Heap::copySegDef(Segment* seg, int usedFrom, int usedTo, int sizeFrom, int sizeTo, int offsetFrom, int offsetTo)
{
	seg->descriptor[usedTo].used = seg->descriptor[usedFrom].used;
	seg->descriptor[sizeTo].size = seg->descriptor[sizeFrom].size;
	if (offsetFrom>=0)
		seg->descriptor[offsetTo].offset = seg->descriptor[offsetFrom].size + seg->descriptor[offsetFrom].offset;
}
void Heap::newSettings(Segment* seg, int descrIndex, int siz)
{
	seg->descriptor[descrIndex - 1].used = true;
	seg->descriptor[descrIndex - 1].size = siz;
	seg->descriptor[descrIndex].used = false;
	seg->descriptor[descrIndex].offset = siz + seg->descriptor[descrIndex - 1].offset;
	seg->descriptor[descrIndex].size = segment_size - seg->descriptor[descrIndex].offset;
	seg->descriptor_count++;
}

void  Heap::free_mem(void* addr)
{
	if (addr == NULL) return;
	for (Segment* cur = current; cur; cur=cur->prev)
	{
		if ((int)addr<(int)cur->data || (int)addr>(int)cur->data + 8 * segment_size) continue;
		for (int i = 0; i < cur->descriptor_count; i++)
		{ 
			if ((void*)((int)cur->data + 8 * cur->descriptor[i].offset) == addr)
			{
				cur->descriptor[i].used = false;
				return;
			}
		}
	}
}