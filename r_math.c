#include "r_math.h"

int r_abs(int x) {
    if (x == 0) return 0;
    if (x > 0) return x;
    int retval = x * -2;
    retval /= 2;
    return retval; 
}

double r_pow(double base, int power) {
    if (power == 0) return 1;
    if (power == 1) return base;

    double retval = 1;
    for (int i = 0; i < r_abs(power); i++)
        retval *= base;

    if (power > 0) return retval;
    return 1 / retval;
}

long long factorial(int x) {
    long long retval = 1;

    if (x > 0)
        for (int i = x; i > 0; i--) retval *= i;

    else if (x < 0)
        for (int i = x; i < 0; i++) retval *= i;
        
    else return 0;
    return retval; 
}

double r_sin(double x) {
    double retval = x;

    for (int i = 0; i < 5; i++) {
        if (!(i % 2))
            retval -= r_pow(x, (i * 2) + 3) / factorial((i * 2) + 3);

        else
            retval += r_pow(x, (i * 2) + 3) / factorial((i * 2) + 3);
    }

    retval += r_pow(x, 13) / FACTORIAL_13;
    retval -= r_pow(x, 15) / FACTORIAL_15;
    retval += r_pow(x, 17) / FACTORIAL_17;

    return retval;
}

double r_cos(double x) {
    double retval = 1;

    for (int i = 0; i < 5; i++) {
        if (!(i % 2))
            retval -= r_pow(x, (i * 2) + 2) / factorial((i * 2) + 2);

        else
            retval += r_pow(x, (i * 2) + 2) / factorial((i * 2) + 2);
    }

    retval += r_pow(x, 12) / FACTORIAL_12;
    retval -= r_pow(x, 14) / FACTORIAL_14;
    retval += r_pow(x, 16) / FACTORIAL_16;

    return retval;
}

double r_tan(double x) {
    double retval = r_sin(x);
    retval /= r_cos(x);
    return retval;
}

double EvaluatePolynomial(const poly_t p_x, double x) {
    if (p_x.k == 0) return p_x.coef[0];

    double retval = 0;
    for (int i = 0; i < p_x.k; i++)
        retval += p_x.coef[i] * r_pow(x, i);

    return retval;
}

void PrintPolynomial(const poly_t p_x) {
    if (p_x.k == 0) {
        printf("%d\n", p_x.coef[0]);
        return;
    }

    if (p_x.coef[p_x.k] == 1) {
        if (p_x.k == 1) printf("x ");
        else printf("x^%d ", p_x.k);
    }
    else {
        if (p_x.k == 1) printf("%dx ", p_x.coef[p_x.k]);
        else printf("%dx^%d ", p_x.coef[p_x.k], p_x.k);
    }

    for (int i = p_x.k - 1; i >= 0; i--) {
        if (p_x.coef[i] == 0) continue;

        if (i == 0) {
            printf("%s %d\n", (p_x.coef[i] > 0) ? "+" : "-", r_abs(p_x.coef[i]));
            break;
        }

        printf("%s ", (p_x.coef[i] > 0) ? "+" : "-");

        if (p_x.coef[i] == 1) {
            if (i == 1) printf("x ");
            else printf("x^%d ", i);
        }
        else {
            if (i == 1) printf("%dx ", r_abs(p_x.coef[i]));
            else printf("%dx^%d ", r_abs(p_x.coef[i]), i);
        }
    }
}

void DerivePolynomial(const poly_t p_x, poly_t *d_px) {
    if (p_x.k == 0) {
        d_px->k = p_x.coef[0];
        d_px->coef = NULL;
        return;
    }
    else if (p_x.k == 1) {
        d_px->k = p_x.coef[1];
        d_px->coef = NULL;
        return;
    }

    d_px->k = p_x.k - 1;
    d_px->coef = malloc(p_x.k * sizeof(int32_t));

    for (int i = d_px->k; i >= 0; i--)
         d_px->coef[i] = p_x.coef[i + 1] * (p_x.k - (p_x.k - (i + 1)));
    
    return;
}