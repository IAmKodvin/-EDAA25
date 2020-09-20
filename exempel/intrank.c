#include <assert.h>
#include <stdio.h>

int main(void){
	signed int a;
	unsigned int b;
	unsigned long c;

	a = -1;
	b += 1;
	c += 1;

	if(a>b){
		printf("a=%d is larger than b=%d", a,b);
	}
	assert(a>b);
	assert(a>c);

	return 0;
}