#include <assert.h>

int main(void){
	signed int a;
	unsigned int b;
	unsigned long c;

	a = -1;
	b += 1;
	c += 1;

	assert(a>b);
	assert(a>c);

	return 0;
}