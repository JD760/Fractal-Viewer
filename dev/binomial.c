/* 
 * implementation of the binomial theorem in C - used in my project
 * to calculate iterations for iteration of formulas such as 
 * z = z^2 + c 
*/

/* system includes */
#include <stdlib.h>
#include <stdio.h>
/* project includes */
/* externs */
/* defines */
/* typedefs */
typedef struct Term{
    int choose;
    int a;
    int b;
}Term;
/* globals */
/* function prototypes */
void binomialCoefficients(int a, int b, int n, Term *result);
int factorial(int n);

void main()
{
    int n = 4;
    Term *result = malloc(sizeof(Term) * (n + 1));
    binomialCoefficients(3, 6, n, result);
    //printf("Factorial: %d\n", factorial(4));
    /*
    for(int i = 0; i < n; i++)
    {
        printf("(%d)(x^%d)(y^%d)\n", result[i].choose, result[i].a, result[i].b);
    }
    return; */
}
/*
 * find the result of (a + b)^n
 * each item in result array represents 
 * (n choose k)(x^a)(y^b) eg 1x^2b^3
*/
void binomialCoefficients(int a, int b, int n, Term *result)
{
    int chooseDenominator;

    for(int k = 0; k <= n; k++)
    {
        //printf("%d\n", k);
        result[k].a = n - k;
        result[k].b = k;
        result[k].choose;
        // save on computations by using known values for the denominator
        if (k == 0 || k == n) result[k].choose = 1;
        else if (k == 1 || k == n - 1) result[k].choose = n;
        else {
            chooseDenominator = factorial(k) * factorial(n - k);
            result[k].choose = factorial(n) / chooseDenominator;
        }
        printf("(%d)(x^%d)(y^%d)\n", result[k].choose, result[k].a, result[k].b);
    }
    
}

int factorial(int n)
{
    int output = 1;
    for(int i = n; i > 1; i--)
    {
        output *= i;
    }
    return output;
}