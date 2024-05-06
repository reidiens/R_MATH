#include "r_math.h"

double r_abs(double x) {
    if (x == 0) return 0;
    if (x > 0)  return x;
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

poly_t* p_create(uint8_t k) {
    poly_t *p = malloc(sizeof(poly_t));

    if (!p) return NULL;

    p->k = k;

    if (k == 0) 
        p->coef= malloc(sizeof(double));
    else
        p->coef = malloc((k + 1) * sizeof(double));
    
    if (p->coef == NULL) {
        free(p);
        return NULL;
    }
    
    return p;
}

void p_free(poly_t* p_x) {
    free(p_x->coef);
    free(p_x);
    return;
}

double p_eval(const poly_t *p_x, double x) {
    if (p_x->k == 0) return p_x->coef[0];

    double retval = 0;
    for (int i = 0; i < p_x->k; i++)
        retval += p_x->coef[i] * r_pow(x, i);

    return retval;
}

poly_t* p_derive(const poly_t *p_x) {
    poly_t *d_px;

    if (p_x->k == 0) return NULL;

    else if (p_x->k == 1) {
        d_px = p_create(0);

        if (!d_px) return NULL;

        d_px->coef[0] = p_x->coef[1];
        return d_px;
    }

    d_px = p_create(p_x->k - 1);
    if (!d_px) return NULL;

    for (int i = d_px->k; i >= 0; i--)
         d_px->coef[i] = p_x->coef[i + 1] * (p_x->k - (p_x->k - (i + 1)));
    
    return d_px;
}

void p_print(const poly_t *p_x) {
    if (p_x->k == 0) {
        if ((int)p_x->coef[0] != p_x->coef[0]) printf("%.3lf\n", p_x->coef[0]);
        else printf("%.0lf\n", p_x->coef[0]);
        return;
    }

    if (p_x->coef[p_x->k] == 1) {
        if (p_x->k == 1) printf("x ");
        else printf("x^%d ", p_x->k);
    }
    else {
        if ((int)p_x->coef[p_x->k] != p_x->coef[p_x->k]) {
            if (p_x->k == 1) printf("%.3lfx ", p_x->coef[p_x->k]);
            else printf("%.3lfx^%d ", p_x->coef[p_x->k], p_x->k);
        }
        else {
            if (p_x->k == 1) printf("%.0lfx ", p_x->coef[p_x->k]);
            else printf("%.0lfx^%d ", p_x->coef[p_x->k], p_x->k);
        }
    }

    for (int i = p_x->k - 1; i >= 0; i--) {
        if (p_x->coef[i] == 0) continue;

        if (i == 0) {
            printf("%s ", (p_x->coef[i] > 0) ? "+" : "-");

            if ((int)p_x->coef[i] != p_x->coef[i]) printf("%.3lf\n", r_abs(p_x->coef[i]));
            else printf("%.0lf\n", r_abs(p_x->coef[i]));           

            break;
        }

        printf("%s ", (p_x->coef[i] > 0) ? "+" : "-");

        if (p_x->coef[i] == 1) {
            if (i == 1) printf("x ");
            else printf("x^%d ", i);
        }
        else {
            if ((int)p_x->coef[i] != p_x->coef[i]) {
                if (i == 1) printf("%.3lfx ", r_abs(p_x->coef[i]));
                else printf("%.3lfx^%d ", r_abs(p_x->coef[i]), i);
            }
            else {
                if (i == 1) printf("%.0lfx ", r_abs(p_x->coef[i]));
                else printf("%.0lfx^%d ", r_abs(p_x->coef[i]), i);
            }
        }
    }
}

poly_t* p_antiderive(const poly_t *p_x) {
    poly_t *P_x = p_create(p_x->k + 1);
    if (P_x == NULL) return NULL;

    for (int i = P_x->k; i >= 0; i--) {
        if (i == 0) {
            P_x->coef[0] = 0;
            break;
        }

        if (p_x->coef[i - 1] == 0) continue;

        P_x->coef[i] = p_x->coef[i - 1] / i;
    }
    return P_x;
}

poly_t* p_add(const poly_t *p_x1, const poly_t *p_x2) {
    poly_t *sum;
    unsigned char larger;

    if (p_x1->k >= p_x2->k) larger = 1;
    else larger = 0;

    if (larger) sum = p_create(p_x1->k);
    else sum = p_create(p_x2->k);

    if (sum == NULL) return NULL;

    for (int i = ((larger) ? p_x1->k : p_x2->k); i > ((larger) ? (p_x1->k - p_x2->k) : (p_x2->k - p_x1->k)); i--)
        sum->coef[i] = ((larger) ? p_x1->coef[i] : p_x2->coef[i]);
    
    for (int i = ((larger ? (p_x1->k - p_x2->k) : (p_x2->k - p_x1->k))); i >= 0; i--)
        sum->coef[i] = p_x1->coef[i] + p_x2->coef[i];
    
    return sum;
}

poly_t* p_negate(const poly_t *p_x) {
    poly_t *neg = p_create(p_x->k);
    if (neg == NULL) return NULL;

    for (int i = p_x->k; i >= 0; i--) {
        if (p_x->coef[i] == 0) continue;
        neg->coef[i] = p_x->coef[i] - (p_x->coef[i] * 2);
    }

    return neg;
}

poly_t* p_sub(const poly_t *px1, const poly_t *px2) {
    poly_t *temp = p_negate(px2);
    if (temp == NULL) return NULL;
    poly_t *difference = p_add(px1, temp);
    if (!difference) return NULL;

    p_free(temp);
    return difference;
}