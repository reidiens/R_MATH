#include "r_math.h"

double r_abs(double x) {
    if (x == 0) return 0;
    if (x > 0) return x;
    double retval = x * -2;
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

double p_eval(const poly_t p_x, double x) {
    if (p_x.k == 0) return p_x.coef[0];

    double retval = 0;
    for (int i = 0; i < p_x.k; i++)
        retval += p_x.coef[i] * r_pow(x, i);

    return retval;
}

void p_derive(const poly_t p_x, poly_t *d_px) {
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
    d_px->coef = malloc(p_x.k * sizeof(double));

    for (int i = d_px->k; i >= 0; i--)
         d_px->coef[i] = p_x.coef[i + 1] * (p_x.k - (p_x.k - (i + 1)));
    
    return;
}

void p_print(const poly_t p_x) {
    if (p_x.k == 0) {
        if ((int)p_x.coef[0] != p_x.coef[0]) printf("%.3lf\n", p_x.coef[0]);
        else printf("%.0lf\n", p_x.coef[0]);
        return;
    }

    if (p_x.coef[p_x.k] == 1) {
        if (p_x.k == 1) printf("x ");
        else printf("x^%d ", p_x.k);
    }
    else {
        if ((int)p_x.coef[p_x.k] != p_x.coef[p_x.k]) {
            if (p_x.k == 1) printf("%.3lfx ", p_x.coef[p_x.k]);
            else printf("%.3lfx^%d ", p_x.coef[p_x.k], p_x.k);
        }
        else {
            if (p_x.k == 1) printf("%.0lfx ", p_x.coef[p_x.k]);
            else printf("%.0lfx^%d ", p_x.coef[p_x.k], p_x.k);
        }
    }

    for (int i = p_x.k - 1; i >= 0; i--) {
        if (p_x.coef[i] == 0) continue;

        if (i == 0) {
            printf("%s ", (p_x.coef[i] > 0) ? "+" : "-");

            if ((int)p_x.coef[i] != p_x.coef[i]) printf("%.3lf\n", r_abs(p_x.coef[i]));
            else printf("%.0lf\n", r_abs(p_x.coef[i]));           

            break;
        }

        printf("%s ", (p_x.coef[i] > 0) ? "+" : "-");

        if (p_x.coef[i] == 1) {
            if (i == 1) printf("x ");
            else printf("x^%d ", i);
        }
        else {
            if ((int)p_x.coef[i] != p_x.coef[i]) {
                if (i == 1) printf("%.3lfx ", r_abs(p_x.coef[i]));
                else printf("%.3lfx^%d ", r_abs(p_x.coef[i]), i);
            }
            else {
                if (i == 1) printf("%.0lfx ", r_abs(p_x.coef[i]));
                else printf("%.0lfx^%d ", r_abs(p_x.coef[i]), i);
            }
        }
    }
}

void p_antiderive(const poly_t p_x, poly_t *P_x) {
    P_x->k = p_x.k + 1;
    P_x->coef = malloc((P_x->k + 1) * sizeof(double));

    for (int i = P_x->k; i >= 0; i--) {
        if (i == 0) {
            P_x->coef[0] = 0;
            break;
        }

        if (p_x.coef[i - 1] == 0) continue;

        P_x->coef[i] = p_x.coef[i - 1] / i;
    }
    return;
}

void p_free(poly_t p_x) {
    free(p_x.coef);
    return;
}

poly_t p_add(const poly_t p_x1, const poly_t p_x2) {
    poly_t sum;

    if (p_x1.k >= p_x2.k)
        sum.k = p_x1.k;
    else sum.k = p_x2.k;

    sum.coef = malloc((sum.k + 1) * sizeof(double));

    if (sum.k >= p_x2.k) {
        for (int i = sum.k; i > sum.k - p_x2.k; i--)
            sum.coef[i] = p_x1.coef[i];

        for (int i = sum.k - (sum.k - p_x2.k); i >= 0; i--)
            sum.coef[i] = p_x1.coef[i] + p_x2.coef[i];
    }
    else {
        for (int i = p_x2.k; i > p_x2.k - sum.k; i--)
            sum.coef[i] = p_x2.coef[i];

        for (int i = p_x2.k - (p_x2.k - sum.k); i >= 0; i++)
            sum.coef[i] = p_x2.coef[i] + p_x1.coef[i];
    }

    return sum;
}