/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Soodeh Vanaki                           */
/*  Student number: 075782128                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/


unsigned int factorial (unsigned int n){
	if (n <= 1) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}

double power (double base, unsigned int n){
	if (n != 0) {
		return (base * power(base, n - 1));
	}
	else {
		return 1;
	}
}
unsigned int fibonacci (unsigned int n){
	if (n == 1 || n == 0) {
		return n;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}	
}
