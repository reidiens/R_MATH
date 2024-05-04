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

    for (int i = 0; i < 3; i++) {
        if (!(i % 2))
            retval -= r_pow(x, (i * 2) + 3) / factorial((i * 2) + 3);

        else
            retval += r_pow(x, (i * 2) + 3) / factorial((i * 2) + 3);
    }

    retval += r_pow(x, 9) / FACTORIAL_9;
    retval -= r_pow(x, 11) / FACTORIAL_11;
    retval += r_pow(x, 13) / FACTORIAL_13;

    return retval;
}

double r_cos(double x) {
    double retval = 1;

    for (int i = 0; i < 3; i++) {
        if (!(i % 2))
            retval -= r_pow(x, (i * 2) + 2) / factorial((i * 2) + 2);

        else
            retval += r_pow(x, (i * 2) + 2) / factorial((i * 2) + 2);
    }

    retval += r_pow(x, 8) / FACTORIAL_8;
    retval -= r_pow(x, 10) / FACTORIAL_10;
    retval += r_pow(x, 12) / FACTORIAL_12;

    return retval;
}