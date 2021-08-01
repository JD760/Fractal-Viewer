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
    int x;
    int y;
    int i;
}Term;
/* globals */
/* function prototypes */
void binomialExpansion(int a, int b, int n, Term *result);
int factorial(int n);

void main()
{
    int n = 4;
    Term *result = malloc(sizeof(Term) * (n + 1));
    binomialExpansion(1, 1, n, result);
    //printf("Factorial: %d\n", factorial(4));

    return;
}
/*
 * find the result of (a + b)^n
 * each item in result array represents 
 * (n choose k)(x^a)(y^b) eg 1x^2b^3
*/
void binomialExpansion(int a, int b, int n, Term *result)
{
    int chooseDenominator;

    for(int k = 0; k <= n; k++)
    {
        // save on computations by using known values for the denominator
        if (k == 0 || k == n) result[k].choose = 1;
        else if (k == 1 || k == n - 1) result[k].choose = n;
        else {
            chooseDenominator = factorial(k) * factorial(n - k);
            result[k].choose = factorial(n) / chooseDenominator;
        }

        result[k].x = n - k;
        result[k].y = k;
        // i^0 = 1 so leave the total coefficient and parity unchanged
        // also i^k = 1 when k % 4 = 0 so these cases are identical
        if (k == 0 || k % 4 == 0) result[k].i = 0;
        // (x + y^ki^k) == -(x + y^ki) when k % 4 == 1
        else if (k % 4 == 1)
        {
            result[k].i = 1;
            result[k].choose *= -1;
        }
        else if (k % 4 == 2)
        {
            result[k].i = 0;
            result[k].choose *= -1;
        }
        else if (k % 4 == 3)
        {
            result[k].i = 1;
        }

        printf("(%d)(x^%d)(y^%d)(i^%d)\n", result[k].choose, result[k].x, result[k].y, result[k].i);
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