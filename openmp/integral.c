#include <stdio.h>
#include <omp.h>

double trap(int n, double inferior_limit, double superior_limit);
double f(double x);

int main()
{
	// n is the number of trapezoids
	int n = 1024;
	double inferior_limit = 0.0;
	double superior_limit = 3.0;
	double result;
	result = trap(n, inferior_limit, superior_limit);
	printf("result = %e\n", result);
}

double trap(int n, double inferior_limit, double superior_limit)
{
	double h = (superior_limit - inferior_limit) / n;
	double a;
	double b;
	double area;
	double accumulator = 0.0;
	int i;
	#pragma omp parallel for reduction(+ : accumulator) private(a, b)
	for(i = 1; i <= 1024; i++)
	{
		a = i * h;
		b = (i + 1) * h;
		accumulator = (f(a) + f(b)) * h / 2.0;
	}
	return accumulator;
}

double f(double x)
{
	return x*x;
}
