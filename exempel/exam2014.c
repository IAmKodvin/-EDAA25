//Exam 2014
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* strcat(char* restrict dest, const char* restrict src){
	/*
	appends the string pointed to by src to the end of the string pointed to by dest, and the first
	character appended overwrites the null character of dest. The strings must not overlap, but if they
	do the behavior is undefined. The return value is dest

	Note that if realloc is not used we assum that dest has enough space.
	*/

	int n = strlen(dest) + strlen(src);
	dest = realloc(dest, sizeof(char)*(n+1));
	int i = strlen(dest);
	for(i; i<n;i++){
		printf("%c ,", *(dest+i));
		*(dest+i) = *(src++);
	}

	return dest;
}

int main(void){
	/*
	char *a = malloc(50);
	strcpy(a, "This is a string");
	a = strcat(a, " test");
	printf("%s\n", a);
	free(a);
	*/
	char b[] = "Arrays and pointers in C are not the same thing.";
	char* c = b;
	if (sizeof b == sizeof c)
	printf("THEN\n");
	else
	// number of elements in array with sizeof, pointer is simply size of a char
	printf("%d, %d, ELSE\n", sizeof(b), sizeof(c));
	return 0;

}