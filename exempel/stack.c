
/*Implement a stack that can be used in an RPN-calculator such as the one in Assignment 1 from
September. Your stack should have int as the type of the stored data, and it must be implemented
with a heap allocation for each time you push, and deallocation each time something is popped. Your
implementation should check that it was possible to allocate memory and that no attempt is made to
pop from an empty stack. At any error, call exit(1).
In addition to push and pop, you should implement a function new_stack to create an empty stack
(which, of course, may simply return a null pointer if you wish that), and free_stack to deallocate
any memory used by the stack. These functions should be used as in the code below, and the return
value from main should be zero (which it will be if free_stack sets what the parameter points at to
NULL).*/

#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t stack_t;

struct stack_t{
	int n;
	int *stack;
};

int pop(stack_t* s){
	if((s->n) == 0){
		printf("n is: %d \n", s->n);
		exit(1);
	}
	int ret;
	ret = *(s->stack+(s->n-1));
	(s->n)--;
	s->stack = realloc(s->stack, sizeof(int)*(s->n));
	printf("pop: %d, n=%d\n", ret,(s->n));
	return ret;
}

void push(stack_t* s, int data){
	int n = data;
	int div = 1;
	int len = 0;
	while(n!=0){
		len++;
		n/=10;
		div*=10;
	}
	div/=10;
	//printf("%d \n", s->n+len);
	if(s->stack==NULL){
		s->stack = (int*) malloc(sizeof(int)*(s->n+len));
	} else {
		s->stack = (int*) realloc(s->stack, sizeof(int)*(s->n+len));
	}
	if(s->stack == NULL){
			printf("error \n");
			exit(1);
			return;
	}

	n = s->n;
	for(int i = n; i<(n+len);i++){
		*(s->stack+i)=data/div;
		printf("%d \n", *(s->stack+i));
		data = data % div;
		div/=10;
	}
	s->n = n+len;
}

stack_t* new_stack(){
	stack_t* new_stack;
	new_stack = (stack_t*) malloc(sizeof(stack_t));
	new_stack -> n = 0;
	return new_stack;
}

void free_stack(stack_t** stack){
	free(*stack);
	*stack = NULL;
}

void print_stack(stack_t* s, void (*func)(void*)){
	for(int i = 0; i<(s->n); i++){
		(*func)(*(s->stack+i));
	}
}

void print_int(void* d)
{
printf("%d", d);
}

int main(void)
{	
	stack_t* stack;
	int a;
	stack = new_stack();
	push(stack, 2014);
	a = pop(stack);
	a = pop(stack);
	push(stack, 10);
	print_stack(stack, print_int);
	free_stack(&stack);
	return stack == NULL ? 0 : 1;
}