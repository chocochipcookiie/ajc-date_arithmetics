#ifndef YEAR_H
#define YEAR_H

#include <iostream>
using namespace std;

const int DAYS_IN_YEAR = 365;										// Used for conversion from years to days

/**
	Year Class: Represents the actual year or the year as a unit; used in Date.h class
**/
class Year {
	private:
		int year;													// Integer that represents numeric year
	public:
		Year();														// Default Constructor
		Year(int y);												// Constructor
		int getYear() const{ return year; }							// Getter method
		int convertToDays();										// convertToDays() method
		Year& operator+(const Year &rhs);							// Addition Operator
		void add(int y);											// Add operator
		friend ostream& operator<<(ostream &os, const Year& y);		// Output Operator
};

Year::Year() {
	year = 0;
}

Year::Year(int y) {
	year = y;
}

int Year::convertToDays() {
	return year * DAYS_IN_YEAR;
}

Year& Year::operator+ (const Year &rhs) {
	Year *newYear;
	newYear = new Year(this->getYear() + rhs.getYear());

	return *newYear;
}

void Year::add(int y) {
	year += y;
}


ostream& operator<<(ostream &os, const Year& y) {
	os << y.getYear();
	return os;
}

#endif YEAR_H