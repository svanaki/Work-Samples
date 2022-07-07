#include "a5.h"
/****************************************************/
/*                                                  */
/*  BTP600                                          */
/*  a5 tester                                       */
/*                                                  */
/*  To compile:                                     */
/*      c++ a5tester.cpp a5.cpp -std=c++0x          */
/*                                                  */
/****************************************************/

int main(void){
	FeatureStatus feature;
	feature.update("initial design");
	feature.print();
	feature.accept();

	feature.update("initial code");
	feature.print();
	feature.accept();

	feature.update("test 2 failed");
	feature.print();
	feature.reject();

	feature.update("design flaw");
	feature.print();
	feature.reject();

	feature.update("code error");
	feature.print();
	feature.reject();

	feature.update("code attempt 2");
	feature.print();
	feature.reject();

	feature.update("redesign needed");
	feature.print();
	feature.accept();

	feature.update("class design 2");
	feature.print();
	feature.reject();

	feature.update("class design 3");
	feature.print();
	feature.accept();


	feature.update("code again");
	feature.print();
	feature.accept();

	feature.update("test 5 failed");
	feature.print();
	feature.reject();


	feature.update("fix needed in function 3()");
	feature.print();
	feature.accept();

	feature.update("code to fix function 3");
	feature.print();
	feature.accept();

	feature.update("test pass");
	feature.print();
	feature.accept();

	feature.update("memory leak");
	feature.print();
	feature.reject();

	feature.update("fix mem leak");
	feature.print();
	feature.accept();

	feature.update("function 4 and function 5 change");
	feature.print();
	feature.accept();

	feature.update("test pass");
	feature.print();
	feature.accept();

	feature.update("PR Accepted");
	feature.print();
	feature.accept();

	feature.update("Done");
	feature.print();
	feature.accept();

}