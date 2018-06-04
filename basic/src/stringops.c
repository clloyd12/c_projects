
#include <stdio.h>


// define the struct
struct ops {
	int data;
};

// use the typedef to make instantiation
// more conventional e.g. Ops my_ops;
typedef struct ops Ops;



int main() {

	printf("Hello\n");

	// instantiate the struct
	/* struct ops my_ops; */
	/* struct ops your_ops; */
	Ops my_ops;
	Ops your_ops;

	my_ops.data = 4;
	your_ops.data = 9;

	printf("my_ops.data is %d\n", my_ops.data);
	printf("your_ops.data is %d\n", your_ops.data);


	// alternatively for struct declaration 
	typedef struct Packed {
		int data:31;
		int flag:1;
		char c:8;
	} Packed;

	// can instiate the struct the same way
	Packed my_packed;
	my_packed.data = 1;

	printf("size of Packed  is %zd\n", sizeof(Packed));
	printf("my_packed data is %d\n", my_packed.data);

	printf("size of int is %zd\n", sizeof(int));
	printf("size of int* is %zd\n", sizeof(int*));
	printf("size of long is %zd\n", sizeof(long));
	printf("size of long* is %zd\n", sizeof(long*));


}


/* char* sort_str(char str[]) { */

/* 	int length = strlen(str); */
/* 	char* arr = (char*)malloc(length); */

/* 	char* p_ret =  (char*) malloc(strlen(str)); */
/* 	for (int i=0;i<length;i++) { */
/* 		push(arr, str[i]); */	
/* 	} */
/* 	return arr; */
/* } */


/* void push( */
