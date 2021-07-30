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

void main()
{
    return;
}
/*
 * find the result of (a + b)^n
*/
void binomialCoefficients(int a, int b, int n)
{
    // there are n+1 terms produced from (a + b)^n expansion
    Term *result = malloc(sizeof(Term) * (n + 1));
    for(int k = 0; k <= n; k++)
    {
        result[0].a = n - k;
        result[0].b = k;
        
    }
}