#ifndef _GLIBCXX_MATH_H

    #ifndef REIDIENS_MATH_H__
        #define REIDIENS_MATH_H__ 1

    #ifndef _STDIO_H
        #include <stdio.h>
    #endif

    #ifndef __CLANG_STDINT_H
        #include <stdint.h>
    #endif

    #ifndef _GLIBCXX_STDLIB_H
        #include <stdlib.h>
    #endif

    #define FACTORIAL_12    479001600
    #define FACTORIAL_13    6227020800
    #define FACTORIAL_14    87178291200
    #define FACTORIAL_15    1307674368000
    #define FACTORIAL_16    20922789888000
    #define FACTORIAL_17    355687428096000

    typedef struct Polynomial {
        uint8_t k;      // degree of the polynomial
        double *coef;  // dynamically alloc'd array of size (k + 1) that stores the coefficients
    } poly_t;

    double r_abs(double x);
    double r_pow(double base, int power);
    long long factorial(int x);
    double r_sin(double x);
    double r_cos(double x);
    double r_tan(double x);
    poly_t* p_create(uint8_t k);
    void p_free(poly_t* p_x);
    double p_eval(const poly_t* p_x, double x);
    poly_t* p_derive(const poly_t *p_x);
    void p_print(const poly_t *p_x);
    poly_t* p_antiderive(const poly_t *p_x);
    poly_t* p_add(const poly_t *p_x1, const poly_t *p_x2);
    poly_t* p_negate(const poly_t *p_x);
    poly_t* p_sub(const poly_t *px1, const poly_t *px2);

    #endif
#endif
