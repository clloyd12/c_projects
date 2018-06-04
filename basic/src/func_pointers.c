#include <stdio.h>

// declare some functions
//
static int device_read_op();
static int device_write_op(const char*);

static int device_read_op() {
	printf("read op\n");
	return 0;
}

static int device_write_op(const char* c) {

	printf("address of arg char* c: %p\n", &(*c));

	int data;
	long long_data;

	printf("address of arg int data : %p\n", &data);
	printf("address of arg long data : %p\n", &long_data);


	printf("write_op %s\n", c);
	return 0;
}

typedef int (*write)(const char*);

static void invoke_me(write w, char* c) {
	printf("invoke_me executing..\n");
	w(c);
}

int main(int argc, char* argv[] ) {

	printf("functors starting... \n");
	device_read_op();
	device_write_op("foo");

	int (*read)() = device_read_op;
	/* read = device_read_op; */
	read();


	// without typdef 
	/* int (*write)(const char*) = device_write_op; */
	// using typedef
	write w = device_write_op;
	w("foo2");
	w("foo");


	/* printf("address of write %p\n", &w); */

	invoke_me(w,"foo3");
	printf("finished\n");
}
