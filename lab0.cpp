/*
	Lab 0: Calendar Dates Arithmetics
	Name: Anna Chang
	Date: 9/28/2015
*/

#include <iostream>

#include "Date.h"

using namespace std;

int main()
{

	// Can read dates in U.S. format (M/D/Y) or in format of Month Day, Year (where month is a word and day and year are integers)
	Date dateA;
	Date dateB;

	dateA.read("januAry 2, 2015");
	dateB.read("11/3/1992");

	Date dateC = dateA + dateB;
	cout << dateA << " + " << dateB << " = " << dateC << endl;

	// Can add months, years, and days, must use lower m, d, y. otherwise, will return an error message and print 0/0/0
	string A = "11m";
	string B = "11c";
	string C = "11d";
	string D = "11y";

	cout << dateA << " + " << A << " = " << (dateA + A) << endl;
	cout << dateA << " + " << B << " = " << (dateA + B) << endl;
	cout << dateA << " + " << C << " = " << (dateA + C) << endl;
	cout << dateB << " + " << D << " = " << (dateB + D) << endl;
	return 0;
	
}