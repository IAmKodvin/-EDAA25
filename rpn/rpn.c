#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define N (10)
// specs
// one char at a time, w getChar
// integers and +, -, *, /
// process one line at a time, print only on new line
// stack 10 nbrs


static void error(unsigned int line, int c, bool* err){

	char buf[3] = "";
	if(c == '\n'){
		strcpy(buf, "\\n");
	}else{
		buf[0] = c; //the getchar int
		buf[1] = 0;
	}

	printf("line %u: error at %s\n", line, buf); 

	*err = true;
}


int main(void){
	int stack[N];
	int i;
	int c;
	int x; //Value of number
	bool num; //Reading a number
	bool err; //Found error on the line 
	unsigned line; //Line number

	x = 0;
	i = 0;
	line = 1;
	num = false;
	err = false;

	while((c = getchar()) != EOF){
		if(err){
			if(c == '\n'){ //if a newline is found
				line += 1;  //update line number
				err = 0;
				i = 0;
			}
			continue; //Skips straight to the outer loop, in this case the top of the while-statement
		}else if(isdigit(c)){
			x = x*10 + c - '0'; //Saves the numbers in a buffer
			num = true;
			continue;
		// if digit not longer true, store value on stack
		}else if(num){
			if(i == N){
			    // no more space on stack
				error(line, '0' + x%10, &err);
			}else{
				stack[i++] = x; //stores the number on the stack at stack[i] then increments i
				num = false;
				x = 0;
			}
		} 
	
		// not enough numbers in stack to make operation
		//if(i<1){
			//printf("error at math \n");
		//	error(line, '0' + x%10, &err);
		//} else {
		if((c == '+' || c == '-' ||  c == '*' || c == '/') && (i<2)){
			error(line, c, &err);
		}
		// Math operator or other symbol
		switch(c) {
				// MATH
				case '+':
					stack[i-2] += stack[i-1];
					i--;
					stack[i] = 0;
				break;
				case '-' :
					stack[i-2] -= stack[i-1];
					i--;
					stack[i] = 0;
					break;
				case '/':
					// division by zero
					if(stack[i-1]==0){
						//printf("error at zero div \n");
						error(line, c + x%10, &err);
					} else {
						stack[i-2] /= stack[i-1];
						i--;
						stack[i] = 0;
					}
					break;
				case '*' :
					stack[i-2] *= stack[i-1];
					i--;
					stack[i] = 0;
					break;
				case '\n' : //new line
					if(i!=1){
						error(line, c, &err);
						err = 0;
					} else {
						printf("line %u: %d\n", line, stack[i-1]);
					}
					line += 1;  //update line number
					i = 0;
					break;
				case ' ' : //blank
					break;
				default :
					// not allowed character ! or similar
					// printf("unkwn char \n");
					error(line, c + x%10, &err);
				}
			//}
		}
	}