# R_MATH
## A math library written in C

### What does R_MATH mean?
Well my name starts with R, and the math part is because this library contains libraries that help you do math! yay!

### Why??
I wanted to learn how computers calculate sine and the best way to do that is to do it yourself.

## Implemented Functions:
- `int r_abs(int x)` - Returns the absolute value of the input


- `double r_pow(double base, int power)` - Raises the base to the power
	- For right now, the power can only be a signed integer. I'm 2 lazy to implement fractional exponents

   
- `long long r_fact(int x)` - Returns the factorial of the input


- `double r_sin(double x)` - Returns the sine of the input
	- Uses the sine taylor series method up to the 9th term ($\dfrac{x^{17}}{17!}$)


- `double r_cos(double x)` - Returns the cosine of the input
	- Uses the cosine taylor series method up to the 9th term ($\dfrac{x^{16}}{16!}$)

- `double r_tan(double x)` - Returns the tangent of the input

- `double EvaluatePolynomial(const poly_t p_x, double x)` - Returns the value of the polynomial at the given value for x

- `void PrintPolynomial(const poly_t p_x)` - Prints the polynomial in the format $ax^{k}+bx^{k-1}+cx^{k-2}+...$

- `void DerivePolynomial(const poly_t p_x, poly_t *d_px)` - Finds the derivative of p_x and stores it in the polynomial at d_px
	- p_x = $P(x)$
	- d_px = $P^{'}(x)$

## Implemented Types:

### `poly_t`

~~~
	typedef struct Polynomial {
		uint8_t k;
		int32_t *coef;
	} poly_t;
~~~

This type is the basis for polynomials. The element `k` stores the degree of the polynomial. `coef` is a dynamically allocated array storing the coefficients in the polynomial.

The size of `coef` is (k + 1). The element specified by `coef[k]` is the coefficient corresponding to that exponent in the polynomial. For example, for the polynomial $4x{3}-5x^{2}+7$ the value stored at `coef[3]` would be 4, and the value for `coef[1]` would be 0.
