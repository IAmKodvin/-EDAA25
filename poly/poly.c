#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

struct poly_t{
	// number of terms
	size_t n;
	// koeff, potens
	int a[][2];
};


int isOperator(char c){
	if((c =='+') || (c == '-') || (c == '/') || (c == '*')){
		return 1;
	}
	return 0;
}

poly_t* new_poly_from_string(const char* polystr){
	// calculate number of terms
	int n = 0;
	int i = 0;
	while(*(polystr+i)){
		if(isOperator(*(polystr+i)) && i!=0){
			n++;
		}
		i++;
	}
	n++;
	// Allocate memory for struct
	poly_t* poly;
	poly = malloc(sizeof(struct poly_t) + 2*n*sizeof(int));
	poly->n = n;

	// store coeffs and pots
	int negative = 0;
	int coeff = 0;
	int pot = 0;
	int c;
	i=0;
	while(*polystr){
		c = *(polystr++);
		if(c == '-'){
			negative = 1;
		} else if(isdigit(c)){
			coeff = coeff*10 + (((int) c) - 48);
		} else if(c == 'x'){
			//printf("char=%c, coeff=%d", c, coeff);
			if(coeff==0){
				coeff = 1;
			}
			if(negative){
				coeff = -coeff;
				negative = 0;
			}
			poly -> a[i][0] = coeff;
			// check if pot
			if(*polystr=='^'){
				// is next character also digit, keep adding to pot
				while(isdigit(*(polystr+1))){
					pot = pot*10 + ((int) *(polystr+1))-48;
					polystr++;
				}
				polystr++;
				poly -> a[i][1] = pot;
				pot = 0;
			} else {
				poly -> a[i][1] = 1;
			}
			i++;
			coeff = 0;
		}
	}

	if(coeff!=0){
		if(negative){
			coeff = -coeff;
		}
		poly -> a[i][0] = coeff;
		poly -> a[i][1] = 0;
	}
	return poly;
}

void free_poly(poly_t* p){
	free(p);
}

int term_exists(poly_t* poly, int p){
	for(int i=0; i<poly->n;i++){
		if((poly->a[i][1]) == p && (poly->a[i][0]!=0)){
			return i;
		}
	}
	return -1;
}

void sort_poly(poly_t* poly){
	int tmp[poly->n][2];
	int big = -1;
	int bigIndex = -1;
	int pot = 0;
	for(int i = 0; i<poly->n; i++){
		for(int j=0; j<poly->n; j++){
			pot = poly->a[j][1];
			if(pot>big){
				big = pot;
				bigIndex = j;
			}
		}
		tmp[i][0] = poly->a[bigIndex][0];
		tmp[i][1] = poly->a[bigIndex][1];
		poly->a[bigIndex][1] = -1;
		big = -1;
	}
	for(int i = 0; i<poly->n; i++){
		poly->a[i][0] = tmp[i][0];
		poly->a[i][1] = tmp[i][1];
	}
}

poly_t*	mul(poly_t* p1, poly_t* p2){
	poly_t* poly;
	int n = (p1->n)*(p2->n);
	poly = malloc(sizeof(struct poly_t) + n*2*sizeof(int));
	poly->n = n;

	int pot;
	int coeff;
	int exist;
	int index = 0;
	//print_poly(poly);
	for(int i=0; i<p1->n; i++){
		for(int j=0; j<p2->n; j++){
			coeff = (p1->a[i][0])*(p2->a[j][0]);
			pot = (p1->a[i][1])+(p2->a[j][1]);
			exist = term_exists(poly, pot);
			if(exist>=0){
				poly->a[exist][0] += coeff;
				// if zero coeff
				if(poly->a[exist][0] == 0){
					// remove term
					for(int k=exist; k<index; k++){
						poly->a[k][0] = poly->a[k+1][0];
						poly->a[k][1] = poly->a[k+1][1];
					}
					index--;
				}
			} else {
				poly->a[index][0] = coeff;
				poly->a[index][1] = pot;
				index++;
			}
		}
	}
	//printf("\n mul of terms %zu, index=%d \n", (poly->n), index);
	if((poly->n)>index){
		poly = realloc(poly,sizeof(struct poly_t) + 2*(index)*sizeof(int));
		poly->n = index;
	}
	//printf("\n mul of terms2 %zu \n", (poly->n));
	//print_poly(poly);
	sort_poly(poly);
	//print_poly(poly);
	return poly;
}

void print_poly(poly_t* poly){
	int c;
	int p;
	//printf("\n nbr of terms %zu \n", (poly->n));

	for(int i=0;i<poly->n;i++){
		c = poly->a[i][0];
		p = poly->a[i][1];
		
		// print operator
		if((c>0) && (i>0)){
			printf(" + ");
		} else if(c<0){
			if(i == 0){
				printf("- ");
			} else {
				printf(" - ");
			}
			c = -c;
		}
		// print term
		if(c==1){
			if(p==0){
				printf("%d",c);
			} else if(p==1){
				printf("x");
			} else {
				printf("x^%d", p);
			}
		} else {
			if(p==0){
				printf("%d",c);
			} else if(p==1){
				printf("%dx",c);
			} else if(c==0){
			}else {
				printf("%dx^%d", c, p);
			}
		}
	}
	printf("\n");
	//printf("\n nbr of terms %zu \n", (poly->n));
}