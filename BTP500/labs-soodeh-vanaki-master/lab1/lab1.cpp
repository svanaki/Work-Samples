/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Soodeh Vanaki                           */
/*  Student number: 075782128                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned int factorial (unsigned int n){

	unsigned int fact = 1;
	if (n == 0) {
		fact = 1;
	}
	else{
		for (unsigned int i = 1; i <= n; i++){
			fact = fact * i;
		}
	}
	return fact;
}

double power (double base, unsigned int n){
 	
	double result = 1;
	if (n == 0) {
		result = 1;
	}
	else {
		for (unsigned i = 1; i <= n; i++) {
			result *= base;
		}
	}
	return result;
}

unsigned int fibonacci (unsigned int n){
	
	unsigned int fib1 = 0;
	unsigned int fib2 = 1;
	unsigned int nextfib = 0;
	if (n == 0) {
		nextfib = fib1;
	}
	if (n == 1) {
		nextfib = fib2;
	}
	else {
		for (unsigned int i = 2; i <= n; i++) {
			nextfib = fib1 + fib2;
			fib1 = fib2;
			fib2 = nextfib;
		}
	}
	return nextfib;	
}
