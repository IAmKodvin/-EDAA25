#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(void)
{	
	int maxLen = 20;

	char * buf;
    buf = malloc(sizeof(char)*maxLen);
    int i = 0;

    // string char
    //buf = "abcasdds";
    //printf("%s\n", buf);

    char * longWord;
    longWord = malloc(sizeof(char)*maxLen);
	int n = 0;

	int c;

	while((c = getchar()) != EOF){
		if(isalpha(c)){
			// reads new char and adds to buffer
			*(buf+i) = c;
			i++;
			if(i>=maxLen){
				maxLen +=10;
				buf = realloc(buf, sizeof(char)*maxLen);
				longWord = realloc(longWord, sizeof(char)*maxLen);
			}
			//continue;
		}else {// if((c == ' ') || (c=='\n')){ // not required
			// compare buffer with longest word when new line or space
			*(buf+i) = '\0';
			if(i > n){
				strcpy(longWord,buf);
				n=i;
				//printf("%d characters in longest word:%s\n", n, longWord);
			}
			i = 0;
		}
	}
	printf("%d characters in longest word: %s\n", n, longWord);
	free(buf);
	free(longWord);
	return 0;
}

