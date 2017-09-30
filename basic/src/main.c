#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include "main.h"

char* get_a_string_ptr(char a_str[]) {

	char* p_ret =  (char*) malloc(strlen(a_str));
	p_ret = strcpy(p_ret, a_str);
	return p_ret;
}

void pass_str_function(const char* p_str) {
	printf("pass_str_function() received str %s\n", p_str);
}

char* string_stuff() {
	
	printf("doing string stuff ...\n");

	// initialize the string
	// this will go in the global string pool
	char* p_hello = "hello\n";
	printf("%s", p_hello);

	// this will create the string on the heap
	char* p_foo = get_a_string_ptr("blah blah blah\n");
	printf("%s", p_foo);
	printf("length of p_foo is %zd\n", strlen(p_foo));

	// adding strings together
	size_t size_of_foo = strlen(p_foo);
	char* p_added_foo = (char*)malloc(size_of_foo + strlen(p_hello));
	strcat(p_added_foo, p_foo);
	strcat(p_added_foo, p_hello);

	// modifying the content of a string
	printf("new concatenated string is %s\n", p_added_foo); 
	*(p_added_foo + 14) = ' ';
	*(p_added_foo + 15) = 'f';

	printf("updated string  is %s\n", p_added_foo); 

	return p_added_foo;
}

int main(int argc, char* argv[] ) {

	printf("starting...\n");
	char* ret = string_stuff();
	pass_str_function(ret);

	return EXIT_SUCCESS;
}
