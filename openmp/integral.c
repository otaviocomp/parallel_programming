#include <stdio.h>
#include <omp.h>

void input_vars(int *n, double *inferior_limit, double *superior_limit);
double trap(int n, double inferior_limit, double superior_limit);
double f(double x);

int main()
{
	// n is the number of trapezoids
	int n;
	double inferior_limit,superior_limit;
	input_vars(&n, &inferior_limit, &superior_limit);

	double result;
	result = trap(n, inferior_limit, superior_limit);
	printf("result = %e\n", result);
}

void input_vars(int *n, double *inferior_limit, double *superior_limit)
{
	printf("number of trapezoids: ");
	scanf("%d", n);
	printf("inferior limit: ");
	scanf("%lf", inferior_limit);
	printf("superior limit: ");
	scanf("%lf", superior_limit);
}

double trap(int n, double inferior_limit, double superior_limit)
{
	double h = (superior_limit - inferior_limit) / n;
	double a;
	double b;
	double accumulator = 0.0;
	int i;
	#pragma omp parallel for reduction(+ : accumulator) private(a, b)
	for(i = 0; i < n; i++)
	{
		a = i * h;
		b = (i + 1) * h;
		accumulator = (f(a) + f(b)) * h / 2.0 + accumulator;
	}
	return accumulator;
}

double f(double x)
{
	return x*x;
}
