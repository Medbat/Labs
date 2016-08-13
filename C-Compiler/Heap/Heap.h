#pragma once
#include "stdafx.h"
#include "STDIO.H"
#include <iostream>
#define SEGMENTSIZE 65539*16
#define SEGMENTCOUNT 1024
using namespace std;

class Heap
{
public:
	Heap(int _segment_size = SEGMENTSIZE)
	{
		segment_size = _segment_size;
		current = 0;
	}
	~Heap()
	{
		delete_segments();
	}
	void*      get_mem(int size);
	void       free_mem(void*);
private:
	struct Segment_def
	{
		bool      used;
		int       size;
		int		offset;
	};

	struct Segment
	{
		void*        data; 
		Segment*     prev;
		Segment_def  descriptor[SEGMENTCOUNT+1];
		int          descriptor_count;
		Segment(int size)
		{
			data = malloc(size);
			descriptor_count = 1;
			descriptor[0].offset = 0;
			descriptor[0].used = 0;
		}
		~Segment()
		{
			delete data;
			data = NULL;
		}
	};

	int       make_segment();
	void      delete_segments();
	void	  copySegDef(Segment* seg,
						int usedFrom, int usedTo, 
						int sizeFrom, int sizeTo,
						int offsetFrom=-1, int offsetTo=-1);
	void	newSettings(Segment* seg, int descrIndex, int size);

	int segment_size;

	Segment*  current;
};

static Heap* heap = new Heap();