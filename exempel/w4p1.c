#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t size){
	void* ptr = malloc(size);

	if (ptr == NULL){
		printf("out of memory");
		exit(1);
	}
	return ptr;
}

int main(void)
{
size_t m;
size_t n;
int** p;
if(scanf("%zu", &m) != 1){
	printf("invalid size");
}
if(scanf("%zu", &n) != 1){
	printf("invalid size");
}

p = xmalloc(m * n * sizeof(int));
for(int i = 0; i<m; ++i){
	p[i]= xmalloc(m * n * sizeof(int));
}

if (p == NULL){
printf("out of memory");
}

for (int i = 0; i < m; i += 1);
for (int j = 0; j < n; j += 1);
p[m-1][n-1] = 1;
printf("%d", p[m-1][n-1]);

for (int i = 0; i < m; i += 1){
	free(p[i]);
}

return 0;
}