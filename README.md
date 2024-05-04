# R_MATH
## A math library written in C
<hr>
### What does R_MATH mean?
Well my name starts with R, and the math part is because this library contains libraries that help you do math! yay!

### Why??
I wanted to learn how computers calculate sine and the best way to do that is to do it yourself.

## Implemented Functions:
- `int r_abs(int x)` - Returns the absolute value of the input
<br>
- `double r_pow(double base, int power)` - Raises the base to the power
	- For right now, the power can only be a signed integer. I'm 2 lazy to implement fractional exponents
<br>
- `long long r_fact(int x)` - Returns the factorial of the input
<br>
- `double r_sin(double x)` - Returns the sine of the input
	- Uses the sine taylor series method up to the 7th term ($\dfrac{x^{13}}{13!}$)
<br>   
- `double r_cos(double x)` - Returns the cosine of the input
	- Uses the cosine taylor series method up to the 7th term ($\dfrac{x^{12}}{12!}$)
<br>
