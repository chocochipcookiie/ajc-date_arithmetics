#ifndef MONTH_H
#define MONTH_H

#include <iostream>

using namespace std;

const int DAYS_IN_MONTH = 30;										// Used for conversion from months to days

/**
	Month Class: Represents the actual month or month as a unit; used in Date.h
**/
class Month {
	private:
		int month;													// Integer that represents the numeric month
	public:
		Month();													// Default Constructor
		Month(int m);												// Constructor
		void setMonth(int m);										// Setter method
		int getMonth() const{ return month; }						// Getter method
		int add(int m);												// Add method
		int convertToDays();										// convertToDays() method
		friend ostream& operator<<(ostream &os, const Month& m);	// Output operator
};

/**
	Default Constructor: Sets month to 0
**/
Month::Month() {
	month = 0;
}

/**
	Constructor: Sets the month variable as m
	@param m Month that is to be set
**/
Month::Month(int m) {
	month = m;
}

/**
	convertToDays(): Converts the amount of months into days, returning an integer
**/
int Month::convertToDays() {
	return month * DAYS_IN_MONTH;
}

/**
	setMonth(): Sets the month to m
	@param m Integer that month is to be set at
**/
void Month::setMonth(int m) {
	month = m;
}

/**
	add(): Adds the m to the amount of months
	@param m Integer to be added 
**/
int Month::add(int m) {
	month += m;
	//cout << "Calculation: " << month << endl;
	if(month > 12 || month <= 0)
	{
		if(month == 0)
		{
			month = 12;			// If it's equal to 0, it will be month 12
		}
		else
		{
			month = month % 12;
	
		}
	}
	return month / 12;
}

/**
	Output Operator
**/
ostream& operator<<(ostream &os, const Month& m) { 
	os << m.getMonth();
	return os;
}

#endif MONTH_H