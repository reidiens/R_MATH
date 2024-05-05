#include "r_math.h"

int main() {
    poly_t x1, x2;

    x1.k = 4;
    x1.coef = malloc((x1.k + 1) * sizeof(double));

    x1.coef[0] = 15;
    x1.coef[1] = 2;
    x1.coef[2] = 3;
    x1.coef[3] = 0;
    x1.coef[4] = 4;

    x2.k = 2;
    x2.coef = malloc((x2.k + 1) * sizeof(double));

    x2.coef[0] = 32;
    x2.coef[1] = 2;
    x2.coef[2] = 3;

    PrintPolynomial(x1);
    PrintPolynomial(x2);
    PrintPolynomial(AddPolynomials(x1, x2));

    PolyFree(x1);
    PolyFree(x2);

    return 0;
}