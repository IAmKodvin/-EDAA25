#include <stdio.h>

int main(void)
{
int i = 8;
for (int i = 0; i < 10; ++i) //for has its own scope
;
printf("i = %d\n", i);
return 0;
}
