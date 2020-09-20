#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.h"
#include "poly.h"

//Need to define poly_t and the four functions declared in the header-file

//poly_t is a linked list
struct poly_t{ //a single term in the polynomial
    int c; //coefficient of term
	int exp; //exponent of term
    poly_t* next; //points to next term in polynomial 
};

void new_list(poly_t* head, int coeff, int exponent){ //void* kan peka på vilken data som helst
	
	head->next = NULL; //the next item in the list
	head->c = coeff;  //the coefficient of the current term
	head->exp = exponent; //the exponent of the current term
}

//Pushes node to the end USED BUT COULD BE REPLACED BY addterm()
void push(poly_t* head, int coeff, int exponent) {
    poly_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // now we can add a new variable
    current->next = (poly_t*) malloc(sizeof(poly_t));
    current->next->c = coeff;
    current->next->exp = exponent;
    current->next->next = NULL;
}

void free_list(poly_t** head){ //anrop: free_list(&p)
	poly_t* h = *head;
	poly_t* p;
	poly_t* q;
	if (h == NULL){
		return;
	}
	p = h->next;

	while(p != NULL){ //while(p != h){
		q = p->next;
		free(p);
		p = q;
	}

	free(*head);
	
	//free(p);
	//*head = NULL;
}

void free_poly(poly_t* p){
	free_list(&p);
}

poly_t*	new_poly_from_string(const char* a){
	poly_t*	p;
	p = (poly_t*) malloc(sizeof(poly_t)); //creates head term
	
	int isNeg = false; //Is the coefficient negative?
	bool polyExist = false; //Is there already a node in the linked list?
	bool readTerm = false;
	int c = 0; //coefficient
	int exp = 0; //exponent
	int i = 0; //iterator int
	int b; //char input buf
	int x = 0; //coeff buffer
	int y = 0; //exp buffer
	//Read the string 'a'
	while( *(a+i) != '\0'){
		b = *(a+i);
	
		if(b == '-'){
			x = 0;
			isNeg = true;

		}else if(b == '+'){
			x = 0;
			isNeg = false;
		}else if(isdigit(b)){
			x = x*10 + b - '0'; //Saves the numbers in a buffer
			readTerm = true; //A new term has been started to be read, a new node can be created

		}else if(b == 'x'){ //the whole coeff has been read
			if(x == 0){ //if no number is written before x, there is 1*x
				c = 1;
				readTerm = true;
				x = 1;
			}

			if(isNeg){
				c = -x;	
			}else{
				c = x;
			}


			i++; //go to next char, could be '\0', '^' or ' '
			if(*(a+i) == '^'){
				i++; //goes to first nr
				while(isdigit(*(a+i))){
					y = y*10 + *(a+i) - '0'; //Saves the numbers in a buffer
					i++;
				}
				exp = y;
				y = 0;
				 
			}else{
				exp = 1;
			}
		}else if(readTerm){
			if(!polyExist){ //if no list exists ->
				new_list(p, c, exp); //creates a new linked list	
				polyExist = true;	
				c = 0;
				exp = 0;
			}else{
				push(p, c, exp); //pushes new term to the back of linked list
				c = 0;
				exp = 0;
			}
			readTerm = false; //can only save another node if a new number is read
		}	
	
		i++;	//goes to index of next char
	}

	//store last term, after the while-loop has found '\0'
	if(readTerm){
		if(isNeg){
			c = -x;
		}else{
			c = x;
		}
		if(!polyExist){
			new_list(p, c, exp);
		}else{
			push(p, c, exp);
		}
	}else{
		if(!polyExist){
			new_list(p, x, exp);
		}
	}
	return p;
}

int size_poly(poly_t* p){
	int i = 1;
	while(p->next != NULL){
		p = p->next;
		i++;
	}
	return i;
}

void print_poly(poly_t* p){
	int n = size_poly(p);
	int c = 0;
	int exp = 0;
	int i;
	bool isNeg = false;
	for(i = 0; i < n; i++){
		c = p->c;
		if(c < 0){
			c = -c;
			isNeg = true;
		}else{
			isNeg = false;
		}
		exp = p->exp;
		
		if(c == 1){ // if coeff is == 1 or -1, don't print coeff
			if(i > 0 && !isNeg){
				printf(" + ");
			}else if(i > 0 && isNeg){
				printf(" - ");
			}

			if(exp != 0){
				if(exp == 1){
					printf("x");
				}else{
					printf("x^%d", exp);
				}	
			}else{ //exp is 0, print 1
				printf("1");
			}
		}else{ 
			if(!isNeg && i > 0){ //don't print '+' if it is first term
				printf(" + "); //positive coefficient, print coeff
			}else if(isNeg){ // negative coeff, print '-' before coeff
				printf(" - ");
			}

			if(exp != 0){
				if(exp == 1){
					printf("%d x", c);
				}else{
					printf("%d x^%d", c, exp);
				}	
			}else{ //exponent is 0, constant term
				printf("%d", c);
			}
		}
		p = p->next;
	}
	printf("\n");
}

//Puts node (coeff, exp) at a sorted place, adds coeff for terms with same exp, removes term if coeff becomes 0 
void addTerm(poly_t* head, int coeff, int exponent){
	poly_t* current = head; //Both really necessary? Need malloc in these cases?
	poly_t* prev;
	poly_t* newTerm;

	if(exponent > current->exp){//add term to head of list
		newTerm = (poly_t*) malloc(sizeof(poly_t)); //allocate memory for new node
		newTerm->c = coeff;
		newTerm->exp = exponent;
		//new term points to the current term
		newTerm->next = current;
		//head is equal to the new term
		head = newTerm; //need to free some of the pointers here?

	}else{ //add somewhere else - find where
		prev = head; //init prev
		while(exponent < current->exp && current->next != NULL){//finds position to put new term
			prev = current; //keeps track of previous term
			current = current->next; //Finds the right place to put the term
		}

		if(exponent == current->exp){ //If the exponent is the same of two terms ->
			//have to add coefficients
			current->c = current->c + coeff;
			//if coeff = 0, delete term current
			if(current->c == 0){
				prev->next = current->next; //removes current from list
				free(current);
			}
		}else{ //create new node here
			newTerm = (poly_t*) malloc(sizeof(poly_t));
			newTerm->c = coeff;
			newTerm->exp = exponent;
			
			if(current->next == NULL){
				newTerm->next = NULL;
				current->next = newTerm;
			}else{
				//term points to current term
				newTerm->next = current;
				//current term points to new term
				prev->next = newTerm;
			}
		}
	}
}

poly_t*	mul(poly_t* p, poly_t* q){
	poly_t* r; // p*q = r
	r = (poly_t*) malloc(sizeof(poly_t)); //creates new head node

	int np = size_poly(p);
	int nq = size_poly(q);
	int c = 0;
	int exp = 0;
	//printf("a\n");
	poly_t* firstQ = q;
	//printf("b\n");
	for (int i = 0; i < np; i++){
		for(int j = 0; j < nq; j++){
			c = (p->c)*(q->c);
			exp = (p->exp)+(q->exp);	
			if(i == 0 && j == 0){
				new_list(r, c, exp);
			}/*else if(i == 0 && j == 1){
				printf("c2\n");
				push(r, c, exp);
				printf("c: %d exp: %d\n", r->next->c, r->next->exp);
			}*/else{
				//printf("c: %d exp: %d\n", c, exp);
				addTerm(r, c, exp); //adds a new term into a sorted position, if same exp already exists, add together, if c becomes 0, remove
				//printf("d2\n");
			}
			q = q->next;
		}
		q = firstQ; //Without this, the inner loop doesnt 'restart' 
		p = p->next;
	}
	return r;
}
