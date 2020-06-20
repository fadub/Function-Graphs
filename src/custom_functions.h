#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include "custom_defs.h"

// --------------------------------------------------------- CUSTOM FUNCTIONS: ----------------------------------------------------------------
// As of now there is no function render engine. Functions need to be defined and put into the function array here.
// Changes take effect after compiling ¯\_(ツ)_/¯


double f(double x, BOOL *isNotDefined) {
	if (x<0 && x>(-0.5)) {
		*isNotDefined = TRUE;
		return 0;
	}
	
	return (1.0/3.0) * (pow((1.0/x + 2), 2) -1);
}

/*
double f2(double x, BOOL *isNotDefined) {
	return pow(0.5 * x, 2);
}


double f3(double x, BOOL *isNotDefined) {
	return 0.5 * pow(x, 2);
}


double h(double x, BOOL *isNotDefined) {
	return cos(x);
}
*/



#define SIZE_FUNC_ARR  1										// ACTION REQUIRED! -> number of your functions defined here
double (*funcArr[SIZE_FUNC_ARR])(double, BOOL*) = {f};			// ACTION REQUIRED! -> every function defined here MUST be a member of the array
const char *funcNames[SIZE_FUNC_ARR] = {"f"};

// ---------------------------------------------------------------------------------------------------------------------------------------------