#include <stdio.h>
#include <stdlib.h>

// complex number arithmetic functions

struct ComplexNumber{
    // c = a + bi
    long double re; // real component
    long double im; // imaginary component
};

struct ComplexNumber addComplex(struct ComplexNumber a, struct ComplexNumber b);
struct ComplexNumber subtractComplex(struct ComplexNumber a, struct ComplexNumber b);
struct ComplexNumber multiplyComplex(struct ComplexNumber a, struct ComplexNumber b);
struct ComplexNumber divideComplex(struct ComplexNumber a, struct ComplexNumber b);

int main()
{
    struct ComplexNumber a = {2, 3}; // 2 + 3i
    struct ComplexNumber b = {3, 2}; // 3 + 2i
    struct ComplexNumber result = divideComplex(a, b);
    printf("re: %Lf , im: %Lf\n", result.re, result.im);
}

// add two complex numbers (a + b)
struct ComplexNumber addComplex(struct ComplexNumber a, struct ComplexNumber b)
{
    struct ComplexNumber result = {a.re + b.re, a.im + b.im};
    return result;
}

// subtract two complex numbers (a - b)
struct ComplexNumber subtractComplex(struct ComplexNumber a, struct ComplexNumber b)
{
    struct ComplexNumber result = {a.re - b.re, a.im - b.im};
    return result;
}

// multiply two complex numbers (a * b)
struct ComplexNumber multiplyComplex(struct ComplexNumber a, struct ComplexNumber b)
{
    // same as multiplying two binomials
    struct ComplexNumber result;
    long double re = a.re * b.re;
    result.im = (a.re * b.im) + (a.im * b.re);
    re -= a.im * b.im;
    result.re = re;
    return result;
}

// divide two complex numbers ( a / b)
struct ComplexNumber divideComplex(struct ComplexNumber a, struct ComplexNumber b)
{
    struct ComplexNumber result;
    long double divisor = (b.re * b.re) + (b.im * b.im);
    result.re = ((a.re * b.re) + (a.im * b.im)) / divisor;
    result.im = ((a.im * b.re) - (a.re * b.im)) / divisor;
    return result;
}
