#include <stdio.h>
#include <stdlib.h>
#include "poly.h"


static void poly_test(const char* a, const char* b)
{
	poly_t*		p;
	poly_t*		q;
	poly_t*		r;

	printf("Begin polynomial test of (%s) * (%s)\n", a, b);

	p = new_poly_from_string(a);
	q = new_poly_from_string(b);

	print_poly(p);
	print_poly(q);

	r = mul(p, q);

	print_poly(r);

	free_poly(p);
	free_poly(q);
	free_poly(r);

	printf("End polynomial test of (%s) * (%s)\n", a, b);
}

int main(void)
{
	poly_test("4x^5 + 2x^3", "2x^14 + 3x + 4");
	putchar('\n');
	poly_test("x^3 - 2x^2", "x + 1");
	putchar('\n');
	poly_test("x^2 - 7x + 1", "3x + 2");
	putchar('\n');
	poly_test("x^10000000 + 2", "2x^2 + 3x + 4");
	putchar('\n');
	poly_test("x - 1", "x + 1");
	putchar('\n');
	poly_test("x^84 - x - 1", "x + 1");
	putchar('\n');
	poly_test("-8x^8426 - 2x - 20", "x^2 + 33x - 1");
	
	return 0;
}
