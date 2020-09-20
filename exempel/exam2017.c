// Exam 2017
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list_t list_t;

struct list_t {
	list_t* succ;
	list_t* pred;
	void* data;
};

list_t* new_list(void* data){
	list_t* head;
	head = malloc(sizeof(size_t));
	if (head == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	} else {
		head -> succ = head;
		head -> pred = head;
		head -> data = data;
		return head;
	}	
}

void free_list(list_t* list){
	list_t* p;
	list_t* q;
	list_t** h;

	h = &list;
	*h = list;
	if(list==NULL){ //if address i null
		return ;
	}

	p = list->succ;
	while(p!=*h){
		q = p->succ;
		free(p);
		p = q;
	}
	free(p);
	h = NULL;
}

void append(list_t** list1, list_t* list2){

	if(*list1==NULL || list2==NULL){ //if address i null
		printf("error\n");
		return ;
	}
	printf("adding %s \n", list2->data);
	list_t* tmp1;

	tmp1 = *list1;

	((*list1)->pred)->succ = list2;
	list2->pred->succ = *list1;
	tmp1 =  (*list1)->pred;
	(*list1)->pred = list2->pred;
	list2->pred = tmp1;
}

void add(list_t** list, void* data){
	list_t* tail;
	tail = new_list(data);
	append(list, tail);
 }

void reverse(list_t** list){
	/*
	It should reverse the list and modify what the parameter points to so that it will point to the
	new start of the list. You are not permitted to allocate new memory from the heap (i.e. getting
	memory from malloc/calloc/realloc). Using a VLA (variable length array) is also forbidden
	in this question.
	*/
	list_t* tmp;
	list_t* head;
	head = *list;
	// first reverse the head (new tail)
	tmp = *list;

	(*list)->succ = tmp->pred;
	(*list)->pred = tmp->succ;
	*list++;

	while(*list != head){
		//swap pointers
		tmp = *list;
		(*list)->succ = tmp->pred;
		(*list)->pred = tmp->succ;
		*list = tmp->succ;
	}
	*list = head->pred;
}

void print(list_t* list, void (*func)(void*)){
	list_t* head;
	head = list;
	list = head->succ;
	(*func)(head->data);
	while(list!=head){
		(*func)(list->data);
		list = list->succ;
	}
	printf("\n");
}

void print_string(void* s)
{
printf("%s", s);
}
char* strchr(const char* s, int c){
	// problem 1
	char * st; //note that input arg is a string literal and return type is a pointer
	char ch;

	st = (char *) s;
	ch = (char) c; //cast to char
	while(*st != '\0'){
		if(*st == c){
			return st;
		}
		st++;
	}
	return st;
}

int main(void){
	char * s;
	int c = (int) 'e';
	s = strchr("test", c);
	printf("%s\n", s);

	list_t* list;
	list = new_list("a");
	add(&list, "b");
	add(&list, "c");
	print(list, print_string);
	reverse(&list);
	print(list, print_string);
	free_list(list);
	/*
	print(list, print_string);
	reverse(&list);
	print(list, print_string);
	*/
	return 0;
}