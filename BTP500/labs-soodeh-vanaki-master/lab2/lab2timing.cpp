/********************************************************************/
/*                                                                  */
/*   lab 2 timing file                                              */
/*                                                                  */
/*   To compile: g++ lab2.cpp lab2timing.cpp timer.cpp -std=c++0x   */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include "timer.h"
#include <iostream>
using namespace std;

unsigned int factorial (unsigned int n);
double power (double base, unsigned int n);
unsigned int fibonacci (unsigned int n);

int main(void){
 
     for (unsigned int n=21; n <=45; n++){
       //	unsigned int n = 25;
	unsigned int rc;
	Timer t;
	t.start();
	rc=fibonacci(n);
	t.stop();
	cout << "fibonacci (" << n << ") = " << rc << endl;
	cout << "fibonacci (" << n << ") took " << t.currtime() << " s" << endl;
     }
	return 0;
}
