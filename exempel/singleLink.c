#include <stdlib.h>
#include <stdio.h>
typedef struct node_t node_t;
typedef struct list_t list_t;

struct node_t{
	node_t* next;
	void* data;
};

struct list_t{
	node_t* head;
	node_t* tail;
};

list_t* new_list(){
	// returns a null pointer (def of empty list)
	list_t* new_list;
	new_list = malloc(sizeof(list_t));
	new_list->head = NULL;
	new_list->tail = NULL;
	return new_list;
}

void add(list_t* list, void* data){
	node_t* new_node;
	new_node = malloc(sizeof(node_t));
	new_node -> data = data;
	new_node -> next = NULL;

	if(list->head == NULL){
		list->head = new_node;
		
	} else {
		(list->tail)->next = new_node;
	}
	list->tail = new_node;
}

node_t* recursive_rev(node_t* n){
	node_t* current;
	node_t* following;
	node_t* previous;

	previous = NULL;
	current = n;

	while(current!=NULL){
		following = current->next;

		current->next = previous;
		previous = current;
		current = following;
	}
	return previous;
}

void reverse(list_t** list){
	if((*list)->head == NULL){
		printf("NUll in rev");
		return;
	} else if((*list)->head == (*list)->tail){
		printf("Only one node");
		return;
	} else {
		node_t* old_head;
		old_head = (*list)->head;
		(*list)->head = recursive_rev((*list)->head);
		(*list)->tail = old_head;
	}
}

void print_list(list_t* list){
	node_t* n;
	n = list->head;
	int *d;
	while(n!=NULL){
		d = n->data;
		printf("%d\n", *d);
		n = n->next;
	}
}

void free_list(list_t* list){
	if(list == NULL){
		printf("list is NULL\n");
		return;
	}
	node_t* p;
	node_t* q;
	p=list->head;

	free(list);
	while(p!=NULL){
		q = p->next;
		free(p);
		p = q;
	}
}


int main(void){
	list_t* p;
	p = new_list();
	int* a;
	int* b;
	int* c;
	*a = 10;
	*b = 5;
	*c = 1;
	add(p, a);
	add(p, b);
	add(p, c);
	print_list(p);
	reverse(&p);
	print_list(p);

	free_list(p);
}