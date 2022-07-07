/************************************************************/
/*  Lab 5                                                   */
/*  Student Name:                                           */
/*     Soodeh Vanaki                                        */
/*  Student Number                                          */
/*     075782128                                            */
/************************************************************/

#include <string>
#include "stack.h"

using namespace std;

bool bracketCheck(const std::string& s) {

	Stack<char> bracketPair(s.length());
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
			bracketPair.push(s[i]);

		}
		else if (s[i] == ')' || s[i] == '}' || s[i] == ']') {
			if (bracketPair.isEmpty()) {
				return false;
			}
			else if (bracketPair.top() == '(' && s[i] == ')' ||
				bracketPair.top() == '{' && s[i] == '}' || 
				bracketPair.top() == '[' && s[i] == ']') {
				bracketPair.pop();
			}
		}
	}
	return bracketPair.isEmpty() ? true : false;
}