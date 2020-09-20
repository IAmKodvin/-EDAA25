#include <stdlib.h>
#include <stdio.h>
// flexible array member
struct example_t{
	size_t n;
	//int * p;
	// unspec length, only one ok, must be last
	int a[][2];
};

int main(){
	struct example_t* p;
	size_t n;
	size_t i;

	n=10;
	p = malloc(sizeof(struct example_t) + 2*n*sizeof(int));
	p->n = n;
	// or
	//p->p = malloc(n*sizeof(int));
	for(i=0; i<p->n; i+=1){
		p->a[i][0] = i;
		printf("a[%d][0]=%d, ", i, p->a[i][0]);
	}
	free(p);
}