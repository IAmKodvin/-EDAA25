#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
char s1[] = "string tokenization";
char* s2 = " ";
char* t1; 
char* t2; 
t1 = strtok(s1, s2); //strtok no thread safe
// first call must point to modifyable string
// remaining calls must use NULL
// s1 uses internal pointer with static storage duration of s1
t2 = strtok(NULL, s2);
printf("found tokens %s and %s\n", t1, t2);
return 0;
}