#ifndef FILEOPS_H
#define FILEOPS_H

/* function-like macro */
#define DEF_PAIR_OF(dtype) \
	typedef struct pair_of_##dtype { \
		dtype first; \
		dtype second; \
	} pair_of_##dtype##_t 

struct stackable {
	struct stackable* p_next;
	struct stackable* p_prev;
	int data;
};

typedef struct stackable Stackable;

void push(Stackable* p_head, int data); 
void push_ordered(Stackable* p_head, int data); 
void show_top(Stackable* p_head, int how_many); 
void pendulumize(Stackable* p_head); 
Stackable* get_last(Stackable* p_head); 


#if __BYTE_ORDER == __ORDER_LITTLE_ENDIAN__ 
	#define ENDIAN "Little" 
#else
	#define ENDIAN "Big"	
#endif

#define max(a,b) \
	({ typeof (a) _a = (a); \
	 typeof (b) _b = (b); \
	 _a > _b ? _a : _b; })



#endif
