#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "main.h"
#include "fileops.h"
#include "btree.h"

DEF_PAIR_OF(int);

/**
 * Returns a pointer to a copy of the string
 * referenced by a_str
 */

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

void do_scanf() {

	char input_buffer[50];
	printf("Please submit some input and press <Return>\n");
	scanf("%s", input_buffer);
	printf("you entered [%s]\n", input_buffer);
	printf("size of what you entered is %zd\n", strlen(input_buffer));
}

void do_single_pendulum_iteration() {

	printf("Enter the array to pendulumize: \n");

	char* input_data;
	int number_of_read_items = scanf("%ms", &input_data);
	if (number_of_read_items > 0) {
		const char s[2] = ",";
		char* token;
		token = strtok(input_data, s);
		Stackable* head = malloc(sizeof(Stackable));
		/* show_top_3(head); */

		while (token != NULL){
			push_ordered(head, atoi(token));
			/* show_top_3(head); */
			token = strtok(NULL, s);
		}
		free(input_data);

		show_top(head,4);
		// @todo return a datastructure from pendulumize and print it 
		pendulumize(head);
	}
	else {
		printf("Didn't read pendulum input correctly\n");
		fprintf(stderr, "No matching characters\n");
	}
}
void do_pendulum_puzzle() {

	printf("How many test cases? (0-999)\n");
	int number_of_tests ;
	int number_of_read_items;
	number_of_read_items = scanf("%1d", &number_of_tests );

	if (number_of_read_items > 0) {
		for (int i=0;i<number_of_tests;i++) {
			do_single_pendulum_iteration();
		}
	}
	else if (errno != 0) {
		printf("Didn't read input correctly\n");
		perror("scanf");
	}
	else {
		printf("Didn't read input correctly\n");
		fprintf(stderr, "No matching characters\n");
	}
	/* printf("read %d items\n", number_of_read_items); */
}

void do_circle_puzzle() {

	printf("Enter the radius of the circle as an integer: \n");
	int radius ;
	int number_of_read_items;

	const size_t fit_length = 1000;
	pair_of_int_t ones_that_fit[fit_length];
	int next=0;

	number_of_read_items = scanf("%3d", &radius );
	if (number_of_read_items > 0) {
		int diameter = 2*radius;
		printf("the area of a circle with diameter %d is %f\n",diameter, 3.14f * radius * radius);

		for (int i=1;i<diameter;i++) {
			for (int j=1;j<diameter;j++) {
				double diagonal = sqrt(pow(i,2) + pow(j,2));
				/* printf("the diagonal of a rectangle with dimensions %dx%d is: %f\n", */
				/* i,j,diagonal); */
				if (diagonal < diameter) {
					pair_of_int_t dimensions;
					dimensions.first = i;
					dimensions.second = j;

					if (next < (int)fit_length)
						ones_that_fit[next] = dimensions;
					else 
						printf("ones_that_fit is full. not addiing %f\n", diagonal);
					next++;
				} 
			}
		}
	}

	for (int i=0;i<next;i++) {
		printf("dimension %dx%d fits\n", ones_that_fit[i].first, ones_that_fit[i].second);
	}

	printf("Number or rectangles  that fit: %d\n", next);
}

bool validate_tip_input(const int num_of_orders,
		const int rahuls_max,
		const int ankits_max) {

	return (num_of_orders <= 105 && num_of_orders > 0  && 
			rahuls_max <= 105 && rahuls_max > 0 && 
			ankits_max <= 105 && ankits_max > 0 && 
			(rahuls_max + ankits_max) >= num_of_orders);
}

void flush_input() {
	/* printf("Flushing input\n"); */
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF); 
}

int* get_dynamic_array(size_t size) {

	int* ret = calloc(size, sizeof(int));
	return ret;

}

void show_populated_segment(int* head, int marker) {

	int i = 0;
	while (*(head + i) != marker) {
		printf("%d ", *(head+i));
		i++;
	}
	   
	printf("\n");
	
}

void show_array(int* head, size_t length) {

	for (int i=0;i<(int)length;i++) {
		printf("%d ", *(head+i));
	}
	printf("\n");

}

void fill_array(int* head, size_t length, int value) {
	
	for (int i=0;i<(int)length;i++) {
		*(head+i) = value;
	}
}

void do_single_tip_iteration() {
	printf("Enter number of orders (N), Rahul's Max (X), and Ankit's max (Y)\n");

	int num_of_orders, rahuls_max, ankits_max;
	int number_of_read_items;
	number_of_read_items = 
		scanf("%3d %3d %3d", &num_of_orders, &rahuls_max, &ankits_max);
	if (number_of_read_items > 0) {
		if (validate_tip_input(num_of_orders, rahuls_max, ankits_max)) {

			/* printf("sizeof rahul_data is %lu\n", sizeof(rahul_data)); */

			flush_input();
			printf("Enter values for tips on orders for Rahul\n" );
			/* char* rahul_data; */
			/* int number_of_read_items = scanf("%ms", &rahul_data); */

			char rahul_data[400];
			fgets(rahul_data, sizeof(rahul_data), stdin);

			// replace the newline with a space 
			char* newline = strchr(rahul_data, '\n');
			*(newline) = ' ';

			/* int* rahuls_tip_list = get_dynamic_array(2); */
			int rahuls_tip_list[105];
			fill_array(&rahuls_tip_list[0], sizeof(rahuls_tip_list)/sizeof(int), -1);

			const char s[2] = " ";
			char* token = strtok(rahul_data, s);
			unsigned int i = 0;
			while (token != NULL) {
				/* printf("read [%s]\n", token); */
				int tip = atoi(token);
				/* printf("sizeof rahuls_tip_list %lu\n", sizeof(rahuls_tip_list)); */

				if (tip != 0) {
					/* *(rahuls_tip_list + i) = tip; */
					rahuls_tip_list[i] = tip;
					/* printf("read [%d]\n", *(rahuls_tip_list + i)); */
					/* printf("read [%d]\n", rahuls_tip_list[i]); */
				} else if (strcmp(token,"0") == 0) {
					rahuls_tip_list[i] = 0;
					printf("read [%d]\n", rahuls_tip_list[i]);
				} else {
					printf("Error: read a tip amount that was invalid %s\n", token);
				}	
				token = strtok(NULL, s);
				i++;
			}

			/* show_array(&rahuls_tip_list[0], sizeof(rahuls_tip_list)/sizeof(int)); */
			/* show_populated_segment(&rahuls_tip_list[0], -1); */

			printf("Enter values for tips on orders for Ankit\n" );

			char ankit_data[400];
			fgets(ankit_data, sizeof(rahul_data), stdin);

			newline = strchr(ankit_data, '\n');
			*(newline) = ' ';

			int ankits_tip_list[105];
			fill_array(&ankits_tip_list[0], sizeof(ankits_tip_list)/sizeof(int), -1);

			token = strtok(ankit_data, s);
			i = 0;
			while (token != NULL) {
				int tip = atoi(token);

				if (tip != 0) {
					ankits_tip_list[i] = tip;
					/* printf("read [%d]\n", ankits_tip_list[i]); */
				} else if (strcmp(token,"0") == 0) {
					ankits_tip_list[i] = 0;
					printf("read [%d]\n", ankits_tip_list[i]);
				} else {
					printf("Error: read a tip amount that was invalid %s\n", token);
				}	
				token = strtok(NULL, s);
				i++;
			}

			/* show_populated_segment(&ankits_tip_list[0], -1); */

			i = 0;
			int running_total = 0;
			while (rahuls_tip_list[i] != -1 &&
					ankits_tip_list[i] != -1) {
				running_total += max(rahuls_tip_list[i], ankits_tip_list[i]);
				i++;
			}
			// get the remaining items from the list that still has them and add them
			if (rahuls_tip_list[i] != -1) {
				printf("remaining in rahuls: ");
				show_populated_segment(&rahuls_tip_list[i], -1);
				while (rahuls_tip_list[i] != -1) {
					running_total += rahuls_tip_list[i];
					i++;
				}
			}
			else {
				printf("remaining in ankits: ");
				show_populated_segment(&ankits_tip_list[i], -1);
				while (ankits_tip_list[i] != -1) {
					running_total += ankits_tip_list[i];
					i++;
				}
			}
			printf("Max tips is %d\n", running_total);
		}
		else {
			printf("Error: Read invalid input: N: %d, X: %d, Y %d\n", 
					num_of_orders,rahuls_max,ankits_max);
		}
	}
	else {
		printf("Didn't read input correctly for orders, Rahul, or Ankit\n");
	}
}
void do_tip_puzzle() {

	printf("How many test cases? (0-999)\n");
	int number_of_tests ;
	int number_of_read_items;
	number_of_read_items = scanf("%1d", &number_of_tests );

	if (number_of_read_items > 0) {
		for (int i=0;i<number_of_tests;i++) {
			do_single_tip_iteration();
		}
	}
	else if (errno != 0) {
		printf("Didn't read input correctly\n");
		perror("scanf");
	}
	else {
		printf("Didn't read input correctly\n");
		fprintf(stderr, "No matching characters\n");
	}
}

void pointer_exe() {

	int** pp = NULL;
	/* if (pp == NULL) { */
	/* 	printf("oh yeah pp was NULL\n"); */ 
	/* 	printf("%d\n", **pp); // seg faults */ 
	/* } else { */
	/* 	printf("%d\n", **pp); // seg faults */ 
	/* } */


	int list[] = { 1, 2, 3, 4, 5, 6 };

	int* p = &list[0];
	pp = &p;

	printf("address of pp is: %p contains:%p\n", pp, *pp); // prints 1 
	printf("address: %zd contains:%d\n", (long)*pp, **pp); // prints 1 
	printf("address: %zd contains:%d\n", (long)(*pp+1), *(*pp + 1)); // prints 2

	printf("address: %zd contains: %d\n", (long)*pp, *(*pp + 6)); // prints 2
	printf("address: %zd contains: %d\n", (long)*pp, *(*pp + 7)); // prints 2
	printf("address: %zd contains: %d\n", (long)*pp, *(*pp + 8)); // prints 2

	/* pp = NULL; */ 
	/* if (pp == NULL) { */
	/* 	printf("oh yeah pp was NULL\n"); */ 
	/* 	printf("%d\n", **pp); // seg faults */ 
	/* } */
}

void test_compare() {


	Node* lhs = (Node*)malloc(sizeof(Node));
	lhs->data = 5;

	Node* rhs = (Node*)malloc(sizeof(Node));
	rhs->data = 4;

	fptr_compare COMP = compare_nodes;

	int ret = COMP(lhs,rhs);
	if (ret > 0)
		printf("The bigger one was %d\n", lhs->data);
	else if (ret == 0)
		printf("The they were equal! data: %d\n", lhs->data);
	else
		printf("The bigger one was %d\n", rhs->data);
}

int main(int argc, char* argv[] ) {

	printf("starting...\n");
	/* char* ret = string_stuff(); */
	/* pass_str_function(ret); */
	/* do_scanf(); */
	/* do_pendulum_puzzle(); */
	/* do_circle_puzzle(); */
	/* printf("max test %d\n", max(4,5)); */
	/* do_tip_puzzle(); */
	/* pointer_exe(); */
	/* test_compare(); */

	Node* root = NULL;
	Node** tree = &root;

	fptr_compare compare = compare_nodes;
	fptr_display display = display_data;
	/* fptr_display display = display_node; */

	add_node(tree, compare, 163);
	add_node(tree, compare, 42);
	add_node(tree, compare, 38);
	add_node(tree, compare, 45);
	add_node(tree, compare, 26);
	add_node(tree, compare,  5);
	add_node(tree, compare, 20);
	add_node(tree, compare, 43);
	add_node(tree, compare, 23);
	add_node(tree, compare, 33);
	add_node(tree, compare,  6);
	add_node(tree, compare,  7);

	in_order(root, display);

/* 	show_tree((*tree), display); */
/* 	show_tree((*tree)->left, display); */
/* 	show_tree((*tree)->left->left, display); */
/* 	show_tree((*tree)->right, display); */

	return EXIT_SUCCESS;
}
