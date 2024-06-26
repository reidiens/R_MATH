# R_MATH
## A math library with polynomial support written in C

### What does R_MATH mean?
Well my name starts with R, and the math part is because this library contains libraries that help you do math! yay!

### Why??
I wanted to learn how computers calculate sine and the best way to do that is to do it yourself. then i got a little carried away.

## Implemented Functions:
- `double r_abs(double x)` - Returns the absolute value of the input


- `double r_pow(double base, int power)` - Raises the base to the power
	- For right now, the power can only be a signed integer. I'm 2 lazy to implement fractional exponents

   
- `long long r_fact(int x)` - Returns the factorial of the input


- `double r_sin(double x)` - Returns the sine of the input
	- Uses the sine taylor series method up to the 9th term ($\dfrac{x^{17}}{17!}$)


- `double r_cos(double x)` - Returns the cosine of the input
	- Uses the cosine taylor series method up to the 9th term ($\dfrac{x^{16}}{16!}$)

- `double r_tan(double x)` - Returns the tangent of the input

- `double p_eval(const poly_t p_x, double x)` - Returns the value of the polynomial at the given value for x

- `void p_print(const poly_t p_x)` - Prints the polynomial in the format $ax^{k}+bx^{k-1}+cx^{k-2}+...$

- `poly_t* p_derive(const poly_t p_x, poly_t *d_px)` - Finds the derivative of p_x and stores it in the polynomial at d_px
	- p_x = $P(x)$
	- d_px = $P`(x)$

- `poly_t* p_antiderive(const poly_t p_x, poly_t *P_x)` - Finds the antiderivative of p_x and stores it in P_x

- `void p_free(poly_t p_x)` - Free the dynamically allocated polynomial

- `poly_t* p_add(const poly_t p_x1, const poly_t p_x2)` - Add the 2 polynomials together and return their sum

- `poly_t* p_negate(const poly_t *p_x)` - Reverses the signs of each term in the polynomial

- `poly_t* p_sub(const poly_t *px1, const poly_t *px2)` - Subtract the 2 polynomials

## Implemented Types:

### `poly_t`

~~~
	typedef struct Polynomial {
		uint8_t k;
		double *coef;
	} poly_t;
~~~

This type is the basis for polynomials. The element `k` stores the degree of the polynomial. `coef` is a dynamically allocated array storing the coefficients in the polynomial.

The size of `coef` is $k + 1$. The element specified by `coef[k]` is the coefficient corresponding to that exponent in the polynomial. For example, for the polynomial $4x^{3}-5x^{2}+7$ the value stored at `coef[3]` would be 4, and the value for `coef[1]` would be 0.

## To Do:
 - implement some sort of garbage collection for the polynomials
 - perhaps rework function return values
 - add logarithms
 - add fractional exponentiation
 - add sqrt
 - add integrals
 - multiply/divide polynomials
 - fix antiderivative function
 - perhaps add multivariable polynomials perhaps? perchance
 - non-polynomial functions 
