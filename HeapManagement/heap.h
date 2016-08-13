#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define SEGMENTSIZE 65536
#define SEGMENTCOUNT 1024

#include <iostream>

using namespace std;

class Heap
{
public:
        Heap(int _segment_size = SEGMENTSIZE)
        { 
            segment_size  = _segment_size;
            current       = NULL;
		}
        ~Heap()    
               {  delete_segments(); }

		void*      get_mem(int size);
		void       free_mem(void*);

		void Test();
private:
        struct Segment_def
        {       
                bool      used;
                int       size;
                void*     ptr;
        };

        struct Segment
        {
                void*        data;
                Segment*     prev;
                Segment_def  descriptor[SEGMENTCOUNT];
                int          descriptor_count;
        };

        int       make_segment();
        void      delete_segments();

        int       segment_size;

		Segment*  current;

};

static Heap heap;