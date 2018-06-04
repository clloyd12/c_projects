#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "fileops.h"

DEF_PAIR_OF(int);
DEF_PAIR_OF(double);

void show_top(Stackable* p_head, int how_many) {

	/* printf("showing top %d of stack: ",how_many); */
	Stackable* current = p_head;
	if (p_head->p_next == NULL) {
		printf("Stack is empty so far\n");
		return;
	}
	int numbershown = 0;
	// move current off of the marker
	current = p_head->p_next;
	while (current != NULL) {
		numbershown++;
		printf("%d " , current->data);
		current = current->p_next;
		if (how_many != 0 && numbershown == how_many) {
			break;
		}
	}
	printf("\n");
}

void show_from_end(Stackable* p_head){

	Stackable* current = get_last(p_head);
	while (current->p_prev != NULL) {
		printf("%d " , current->data);
		current = current->p_prev;
	}
}

Stackable* get_last(Stackable* p_head) {
	Stackable* current = p_head;
	if (current->p_next == NULL) {
		return current;
	}
	while (current->p_next != NULL) {
		current = current->p_next;
	}
	return current;
}

Stackable* pop(Stackable* p_head) {

	Stackable* ret = p_head->p_next;
	p_head->p_next = ret->p_next;
	return ret;
}

void push_ordered(Stackable* p_head, int data) {

	Stackable* p_add_me = malloc(sizeof(p_head));
	p_add_me->data = data;

	// if empty just insert it at the head
	Stackable* current = p_head;
	if (p_head->p_next == NULL) {
		p_head->p_next = p_add_me;
		p_add_me->p_prev = p_head;
		return;
	}
	/**
	 * invariant - at this point we're guananteed to have
	 * a length of 2 nodes:  head->next.  We're pointed to
	 * head node to start
	 */
	while (current != NULL) {

		// if we're at the end insert at the end
		if (current->p_next == NULL) {
			current->p_next = p_add_me;
			p_add_me->p_prev = current;
			return;
		}
		if (current->p_next->data >= p_add_me->data) {

			// current<->next and now we want current<->addme<->next
			//
			// make addme and current point to same next node: addme->next, current<->next
			p_add_me->p_next = current->p_next;
			// make addme previous point to current: current<-addme->next, current<->next
			p_add_me->p_prev = current;
			// make the node we're inserting in front of have its prev point to addme
			// curent<-p_addme<->next, current->next
			current->p_next->p_prev = p_add_me;
			// current next needs to point to add me.  
			// current<->addme<->next 
			current->p_next = p_add_me;
			return;
		}
		current = current->p_next;
	}
}

/**
 * Precondition: p_head is the marker for sorted (lowest to highest)
 * list of Stackables
 **/
void pendulumize(Stackable* p_head) {

	Stackable* current = p_head;
	if (p_head->p_next == NULL) {
		printf("Stack is empty\n");
		return;
	}
	/**
	 * invariant - at this point we're guananteed to have
	 * a length af 2 nodes:  head->next.  We're pointed to
	 * head node to start
	 */

	Stackable* pivot = malloc(sizeof(Stackable));
	// move current off of the head marker
	Stackable* lowest = p_head->p_next;
	pivot->data = lowest->data;

	Stackable* left_head = malloc(sizeof(Stackable));
	Stackable* right_head = malloc(sizeof(Stackable));
	
	bool go_left = true;

	current = p_head->p_next;
	while (current != NULL) {
		/* printf("%d " , current->data); */
		if (go_left) {
			push_ordered(left_head, current->data);
		} else {
			push_ordered(right_head, current->data);
		}
		go_left = !go_left;
		current = current->p_next;
	}
	pivot->p_next = right_head->p_next;
	pivot->p_prev = left_head->p_next;

	/* printf("left head is:\n"); */
	show_from_end(left_head);
	/* printf("pivot head is:\n"); */
	show_top(pivot,0);
}


void push(Stackable* p_head, int data) {

	Stackable* p_add_me = malloc(sizeof(p_head));
	p_add_me->data = data;

	p_add_me->p_next = p_head->p_next;
	p_add_me->p_next->p_prev = p_add_me;
	p_head->p_next = p_add_me;
	p_add_me->p_prev = p_head;
}

void do_file_ops() {

	FILE *fp;
	char fName[20];

	printf("Enter a filename:");
	scanf("%s", fName);

	fp=fopen(fName,"w");
	if (fp != NULL) {
		printf("File %s created successfully \n", fName);
	}
	else {
		printf("File not created!! %s\n", fName);
		exit(EXIT_FAILURE);
	}
	// lets write something to the file
	printf("Enter some text to write to the file. \n");
	char input_char;
	// get the first char and throw it out
	input_char = getchar();
	do {
		input_char = fgetc(stdin); 	
		/* input_char = getchar(); */
		fputc(input_char, fp);	
	} 
	while (input_char != '\n' );

	printf("closing file %s...\n", fName);

	int ret_close = fclose(fp);
	if (ret_close == -1)  {
		printf("File not closed!! %s\n", fName);
		exit(EXIT_FAILURE);
	}
	else {
		printf("File %s closed\n", fName);
	}
}

int count_lines(const char* filename) {

	// open file 
	// read each line until EOF, increment counter
	// return the count
	//
	FILE *fp;
	fp = fopen(filename, "r");	
	int count = 0;
	if (fp != NULL) {
		printf("Reading File %s ...\n", filename);

		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;

		while ((linelen = getline(&line, &linecap, fp)) > 0) {

			/* 			printf("read: %s",line); */
			count++;
		}

		int close_status = fclose(fp);
		if (close_status == 0) {
			printf("succesfully closed file %s \n",filename);

		} else {

			printf("couldn't close file %s\n", filename);
		}	

	}
	else {
		printf("Couldn't read file!! %s\n", filename);
	}
	return count;
}

int reverse_content(const char* filename) {

	FILE *fp;
	fp = fopen(filename, "r");	

	if (fp != NULL) {

		fseek(fp,0L ,SEEK_END);	
		long pos_indicator = ftell(fp);
		printf("ftell says indicator is at position: %ld \n",
				pos_indicator);

		for (int i=(pos_indicator-1); i>=0; --i) {

			fseek(fp,i ,SEEK_SET);	
			pos_indicator = ftell(fp);
			char read_char = fgetc(fp); 	
			printf("%c", tolower(read_char));
		}

		printf("\n");
		printf("ftell says indicator is at position: %ld \n",
				pos_indicator);

		int close_status = fclose(fp);
		if (close_status == 0) {
			printf("succesfully closed file %s \n",filename);

		} else {

			printf("couldn't close file %s\n", filename);
		}	

	} else {
		printf("couldn't open file %s\n", filename);
	}
	return EXIT_SUCCESS;
}

void use_macro() {

	pair_of_int_t pair;

	pair.first = 8;
	pair.second = 8;

	printf("pair first is %d\n", pair.first);
	printf("pair second is %d\n", pair.second);
}
void swap(int arr[], int pos1, int pos2) {

	arr[pos1] ^= arr[pos2];
	arr[pos2] ^= arr[pos1];
	arr[pos1] ^= arr[pos2];
}

void randomize_array(int* arr, int length) {

	// initialize random number generator
	/* time_t t; */
	srand((unsigned) time(NULL));

	int last_index = length - 1;
	for (int i=0;i<length;i++) {

		// if we're at the last element just break
		if (i == last_index) {
			/* printf("last index reached %d\n", last_index); */
			break;
		}
		// if we've reached the second to last index just
		// swap with the last index
		if (i == (last_index - 1)) {
			/* printf("penultimate index reached %d\n", i); */
			/* printf("switching %d and %d \n",i,last_index); */
			swap(arr,i,last_index);
		} 
		else {
			int offset = (rand() % (last_index - (i + 1))); 
			int swap_index = last_index - offset;
			
			/* printf("i is %d, offset is %d. switching %d and %d \n", i,offset, */
					/* i,swap_index); */ 
			swap(arr,i,swap_index);
		}
	}
}


void show_list(int arr[], int length) {

	for (int i=0; i< length; i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}

/* int main(int argc, char* argv[]) { */


/* 	/1* printf("Main file is %s\n", __BASE_FILE__); *1/ */
/* 	/1* printf("Counter is %d\n", __COUNTER__); *1/ */
/* 	/1* printf("Compiled with version %s\n", __VERSION__); *1/ */
/* 	/1* printf("INT 64 Max is %ld\n", __INT64_MAX__); *1/ */
/* 	/1* printf("Endian is %s\n",ENDIAN); *1/ */
/* 	/1* char* filename = "foo.txt"; *1/ */
/* 	/1* do_file_ops(); *1/ */
/* 	/1* int linecount = count_lines(filename); *1/ */
/* 	/1* printf("line count is %d\n", linecount); *1/ */

/* 	/1* reverse_content(filename); *1/ */

/* 	/1* int my_max = max(8,8); *1/ */
/* 	/1* printf("%d\n", my_max); *1/ */

/* 	int my_list[20]; */
/* 	int my_list_size = sizeof(my_list) / sizeof(int); */

/* 	printf("list size is: %d\n", my_list_size); */


/* 	for (int i=0; i< my_list_size;i++) { */
/* 		my_list[i] = i; */
/* 	} */

/* 	Stackable* head = malloc(sizeof(Stackable)); */

/* 	for (int i=0; i< 40;i++) { */
/* 		push(head,i); */
/* 		show_top_3(head); */
/* 	} */

/* 	for(int i=40; i>1; i--) { */
/* 		head = pop(head); */
/* 		show_top_3(head); */
/* 	} */

/* 	/1* printf("hello\n"); *1/ */
/* 	/1* return 0; *1/ */

/* 	show_list(my_list, my_list_size); */


/* 	/1* for (int i=0;i<1001;i++) { *1/ */
/* 		/1* randomize_array(my_list, my_list_size); *1/ */
/* 		/1* show_list(my_list, my_list_size); *1/ */
/* 	/1* } *1/ */

/* } */
