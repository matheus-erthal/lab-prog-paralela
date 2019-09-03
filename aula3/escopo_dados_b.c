#include <string.h>
#include <stdio.h>
#include <omp.h>


int main(){
	int a = 1, b = 2, c = 3;
	
	#pragma omp parallel firstprivate(a)
	{
		a+= 1;
		c+= 7;
		printf("A becomes %d, b is %d\n", a, b);
	}
}