/**
 * Second project to IZP.
 * Created by Jakub Čábera (Ash258) <cabera.jakub@gmail.com> <xcaber00@stud.fit.vutbr.cz> on 11/4/16.
 */

//region Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
//endregion

//region Defines
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define IR_NUMBER 258258258258258.258258258258

/** Error Statuscodes */
enum errors{
	FLAG_ERROR         = 0,
	BELOW_ZERO         = 1,
	NEGATIVE_NUMBER    = 2,
	NEGATIVE_ITERATION = 3,
	INVALID_NUMBER     = 4
};
//endregion

//region Helpers
/**
 * Print error message and exit program with given status code.
 *
 * @param message Message to be printed.
 * @param statusCode Status code.
 */
void error(int statusCode){
	static const char *errs[] = {"Not supported arguments passed to program.",
	                             "Number for logarithm cannot be bellow zero.",
	                             "Argument for factorial cannot be negative.",
	                             "Number of iterations cannot be 0 or bellow.",
	                             "Invalid number given to function."};
	fprintf(stderr, RED "%s\n"
			"Exit status code: %d\n"
			RESET, errs[statusCode], statusCode + 100);
	exit(statusCode + 100);
}

/**
 * Check is number is odd integer.
 *
 * @param x Integer to check.
 *
 * @return True if number is odd.
 */
int isOdd(double x){
	return (int) x == x
	       ? (int) x % 2
	       : 0;
}

/**
 * Check if given value is suitable for logarithmic function.
 *
 * @param x Value for validation.
 *
 * @see man log
 *
 * @return Values as log() function.
 */
double logValidation(double x){
	/*
	 * If x is a NaN, a NaN is returned.
	 * If x is negative (including negative infinity), then a domain error occurs, and a NaN (not a number) is returned.
	 * If x is 1, the result is +0.
	 * If x is positive infinity, positive infinity is returned.
	 * If x is zero, then a pole error occurs, and the functions return -HUGE_VAL, -HUGE_VALF, or -HUGE_VALL, respectively.
	 */
	if(x < 0 || isnan(x) == 1){ return NAN; }
	else if(x == 1){ return 0; }
	else if(isinf(x) == 1){ return INFINITY; }
	else if(x == 0){ return INFINITY * -1.0; }
	else {
		return IR_NUMBER;
	}
}

/**
 * Check if values given to pow function is valid and return values as pow() in math.h.
 *
 * @param x Base
 * @param y Exponent
 *
 * @see man pow
 *
 * @return Values as pow() function.
 */
double powValidation(double x, double y){
	/*
	 * If x is +1, the result is 1.0 (even if y is a NaN).
	 * If y is 0, the result is 1.0 (even if x is a NaN).
	 * If x is positive infinity, and y greater than 0, the result is positive infinity.
	 * If x is positive infinity, and y less than 0, the result is +0.
	 * If x is -1, and y is positive infinity or negative infinity, the result is 1.0.
	 * If the absolute value of x is greater than 1, and y is positive infinity, the result is positive infinity.
	 * If x or y is a NaN, the result is a NaN.
	 * If x is +0 or -0, and y is less than 0 and not an odd integer, a pole error occurs and +HUGE_VAL, +HUGE_VALF, or +HUGE_VALL, is returned.
	 * If x is +0 (-0), and y is an odd integer greater than 0, the result is +0 (-0).
	 * If x is negative infinity, and y less than 0 and not an odd integer, the result is +0.
	 * If x is negative infinity, and y greater than 0 and not an odd integer, the result is positive infinity.
	 * If x is negative infinity, and y is an odd integer greater than 0, the result is negative infinity.
	 * If x is negative infinity, and y is an odd integer less than 0, the result is -0.
	 * If x is 0, and y greater than 0 and not an odd integer, the result is +0.
	 * If the absolute value of x is less than 1, and y is negative infinity, the result is positive infinity.
	 * If the absolute value of x is greater than 1, and y is negative infinity, the result is +0.
	 * If the absolute value of x is less than 1, and y is positive infinity, the result is +0.
	 * If x is +0 or -0, and y is an odd integer less than 0, a pole error occurs and HUGE_VAL, HUGE_VALF, or HUGE_VALL, is returned, with the same sign as x
	 */
	if(x == 1){ return 1; }
	else if(y == 0){ return 1; }
	else if((isinf(x) == 1) && (y > 0)){ return INFINITY; }
	else if((isinf(x) == 1) && (y < 0)){ return +0; }
	else if((x == -1) && ((isinf(y) == 1) || isinf(y) == -1)){ return 1; }
	else if((fabs(x) > 1) && (isinf(y) == 1)){ return INFINITY; }
	else if((isnan(x) == 1) || (isnan(y) == 1)){ return NAN; }
	else if((x == 0) && (y < 0) && (isOdd(y) == 0)){ return INFINITY; }
	else if((x == 0) && (y < 0) && (isOdd(y) == 1)){ return INFINITY; }
	else if((x == 0) && (y > 0) && (isOdd(y) == 1)){ return +0; }
	else if((x == -1.0 * 0) && (y > 0) && (isOdd(y) == 1)){ return -1.0 * 0; }
	else if((isinf(x) == -1) && (y < 0) && (isOdd(y) == 0)){ return +0; }
	else if((isinf(x) == -1) && (y > 0) && (isOdd(y) == 0)){ return INFINITY; }
	else if((isinf(x) == -1) && (y > 0) && (isOdd(y) == 1)){ return -INFINITY; }
	else if((isinf(x) == -1) && (y < 0) && (isOdd(y) == 1)){ return -1.0 * 0; } // -1 * 0 ==> -0
	else if((isinf(x) == -1) && (y < 0)){ return -1.0 * 0; } // -1 * 0 ==> -0
	else if((isinf(x) == -1) && (y > 0)){ return INFINITY; } // -1 * 0 ==> -0
	else if((x == 0) && (y > 0) && isOdd(y) == 0){ return +0; }
	else if((abs((int) x) < 1) && (isinf(y) == -1)){ return INFINITY; }
	else if((abs((int) x) > 1) && (isinf(y) == -1)){ return +0; }
	else if((abs((int) x) < 1) && ((isinf(y) == 1))){ return +0; }
	else if((x == +0) && (isOdd(y) == 1) && (y < 0)){ return +0; }
	else if((x == -1.0 * 0) && (isOdd(y) == 1) && (y < 0)){ return -1.0 * 0; }
	else if(isinf(y) == -1){ return 0; }
	else if(x == 0 && (1 / x) < 0 && isOdd(y) && y < 0){ return -HUGE_VAL; }
	else if(x == 0 && (1 / x) > 0 && isOdd(y) && y < 0){ return HUGE_VAL; }
	else {
		return IR_NUMBER;
	}
}
//endregion

//region Functions
/**
 * Implementation of logarithm using Taylor series.
 *
 * @param x Number for logarithmic function.
 * @param n Number of members.
 *
 * @return Logarithmic number.
 */
double taylor_log(double x, unsigned int n){
	double validation    = logValidation(x);
	if(validation != IR_NUMBER) return validation;
	if(n <= 0) error(NEGATIVE_ITERATION);

	unsigned int i, j;
	double       current = x, result = 0;

	if(x >= 1){
		x     = current = (current - 1) / current;
		for(i = 1; i <= n; i++) {
			result += current / i;
			current *= x;
		}
	} else {
		x     = current = 1 - current;
		for(j = 1; j <= n; j++) {
			result -= current / j;
			current *= x;
		}
	}

	return result;
}

/**
 * Implementation of logarithm using concatenated fraction.
 *
 * @param x Number for logarithm.
 * @param n Number of iterations.
 *
 * @return Logarithmic number.
 */
double cfrac_log(double x, unsigned int n){
	double validation = logValidation(x);
	if(validation != IR_NUMBER) return validation;
	if(n <= 0) error(NEGATIVE_ITERATION);

	double z = (x - 1) / (x + 1), denominator = 1, odd, numerator;

	for(unsigned int i = n; i > 0; i--) {
		// 2 * i - 1 => left side of denominator (odd number) in formula
		odd         = 2 * i - 1;
		// brackets => numerator in formula
		numerator   = i * i * z * z;
		denominator = odd - (numerator / denominator);
	}

	return 2 * z / denominator;
}

/**
 * Implementation of exponential function using Taylor series with different logarithms.
 *
 * @param logarithm Pointer to logarithmic function.
 * @param x Base number for powering.
 * @param y Exponent for powering.
 * @param n Number of iterations.
 *
 * @return Powered number.
 */
double taylor_pow_258(double (*logarithm)(double, unsigned int), double x, double y, unsigned int n){
	double validation        = powValidation(x, y);
	if(validation != IR_NUMBER) return validation;

	/* From formula ==> x = y
	 * From formula ==> a = x */
	unsigned int i;
	double       value       = 1, result = value;
	double       formulaX    = y, formulaA = x;
	double       staticValue = formulaX * logarithm(formulaA, n);

	for(i = 1; i <= n; i++) {
		value *= (staticValue / i);
		result += value;
	}

	return result;
}

/**
 * Implementation of exponential function using Taylor series (concatenated fraction).
 * Useless function. Only because of task with exact prototypes.
 * This function handle taylor_pow itself based on function name in taylor_pow function calling.
 *
 * @param x Power base.
 * @param y Power Number.
 * @param n Number of iterations.
 *
 * @return Powered number.
 */
double taylorcf_pow(double x, double y, unsigned int n){
	double validation        = powValidation(x, y);
	if(validation != IR_NUMBER) return validation;

	unsigned int i;
	double       value       = 1, result = value;
	double       formulaX    = y, formulaA = x;
	double       staticValue = formulaX * cfrac_log(formulaA, n);

	for(i = 1; i <= n; i++) {
		value *= (staticValue / i);
		result += value;
	}

	return result;
}

/**
 * Implementation of exponential function using Taylor series (concatenated fraction).
 * Useless function. Only because of task with exact prototypes.
 * This function handle taylor_pow itself based on function name in taylor_pow function calling.
 *
 * @param x Power base.
 * @param y Power Number.
 * @param n Number of iterations.
 *
 * @return Powered number.
 */
double taylor_pow(double x, double y, unsigned int n){
	double validation        = powValidation(x, y);
	if(validation != IR_NUMBER) return validation;

	unsigned int i;
	double       value       = 1, result = value;
	double       formulaX    = y, formulaA = x;
	double       staticValue = formulaX * taylor_log(formulaA, n);

	for(i = 1; i <= n; i++) {
		value *= (staticValue / i);
		result += value;
	}

	return result;
}
//endregion

//region Main
/**
 * Perform log.
 *
 * @param X Number.
 * @param N NUmber of iterations.
 */
void performLog(double X, unsigned int N){
	printf("%10s(%g) = %.12g\n", "log", X, log(X));
	printf("%10s(%g) = %.12g\n", "cf_log", X, cfrac_log(X, N));
	printf("%10s(%g) = %.12g\n", "taylor_log", X, taylor_log(X, N));
}

/**
 * Perform powering.
 *
 * @param X Base.
 * @param Y Exponent.
 * @param N Number of iterations.
 */
void performPow(double X, double Y, unsigned int N){
	printf("%12s(%g,%g) = %.12g\n", "pow", X, Y, pow(X, Y));
	printf("%12s(%g,%g) = %.12g\n", "taylor_pow", X, Y, taylor_pow_258(taylor_log, X, Y, N));
	printf("%12s(%g,%g) = %.12g\n", "taylorcf_pow", X, Y, taylor_pow_258(cfrac_log, X, Y, N));
}

/**
 * Handle flags and perform actions.
 *
 * @param argc Argument count from user.
 * @param argv Array of arguments from user.
 *
 * @example ./proj2 --log X N
 * 			./proj2 --pow X Y N
 */
void flagHandler(int argc, char **argv){
	double       X, Y;
	unsigned int N, errors = 0;
	if(argc == 1) error(FLAG_ERROR);

	if((strcmp(argv[1], "--log") == 0) && (argc == 4)){
		// Convert string to double and check if it is valid number
		errors += sscanf(argv[2], "%lf", &X);
		errors += sscanf(argv[3], "%u", &N);

		if(errors != 2) error(INVALID_NUMBER);

		performLog(X, N);
	} else if((strcmp(argv[1], "--pow") == 0) && (argc == 5)){
		// Convert string to double and check if it is valid number
		errors += sscanf(argv[2], "%lf", &X);
		errors += sscanf(argv[3], "%lf", &Y);
		errors += sscanf(argv[4], "%u", &N);

		if(errors != 3) error(INVALID_NUMBER);

		performPow(X, Y, N);
	} else {
		error(FLAG_ERROR);
	}
}
//endregion

//region Testing

void powTest(){
	double pow_numbers[][2] = {{1, 0}, {INFINITY, 1}, {INFINITY, -1},
	                           {-1, -1}, {-1, INFINITY}, {-1, -INFINITY},
	                           {abs(-2), INFINITY}, {abs(-1), INFINITY}, {NAN, NAN},
	                           {+0, -3}, {-0, -3}, {+0, -4},
	                           {-0, -4}, {+0, 3}, {-0, 3},
	                           {-INFINITY, -4}, {-INFINITY, 4}, {-INFINITY, 3},
	                           {-INFINITY, -3}, {0, 4}, {abs(1), -INFINITY},
	                           {abs(-2), -INFINITY}, {abs(1), INFINITY}, {+0, 3},
	                           {-0, 3}
	};
	printf("                  POWERING\n");

	for(int i = 0; i <= 25; i++) {
		printf("%lf\n", powValidation(pow_numbers[i][0], pow_numbers[i][1]));
		printf("%lf\n", pow(pow_numbers[i][0], pow_numbers[i][1]));
		printf("**********************************\n");
	}
}

void log_test(){
	double numbers[] = {NAN, -1, 1, INFINITY, 0};
	printf("             LOG\n");

	for(int i = 0; i < 4; i++) {
		performLog(numbers[i], 20);
		log(numbers[i]);
		printf("*******************************\n");
	}
}

void test(){
	printf("\n***************VALIDATION TESTS\n");
	log_test();

	powTest();
	printf("\n***************VALUES TESTS\n");
}
//endregion

int main(int argc, char **argv){
	flagHandler(argc, argv);
	return 0;
}
