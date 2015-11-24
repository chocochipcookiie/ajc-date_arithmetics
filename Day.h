#ifndef DAY_H
#define DAY_H

#include <iostream>

using namespace std;

/**
	Day Class: Represents the actual day or day as a unit; used in Date.h
**/
class Day {
	private:
		int day;													// Integer that represents the numeric day
	public:
		Day();														// Default Constructor
		Day(int d);													// Constructor
		int getDay() const{ return day; }							// Getter method
		void setDay(int d) { day = d; }								// Setter method
		Day& operator+(const Day &rhs);								// + Operator Overload
		bool operator<=(const Day &rhs);							// Comparison Operator <= overload
		Day& operator=(const Day &rhs);								// Assignment Operator Overload
		friend ostream& operator<<(ostream &os, const Day& d);		// Output Operator
};

/**
	Default Constructor: Sets day to 0
**/
Day::Day() {
	day = 0;
}

/**
	Constructor: Sets the day variable as d
	@param d Day that is to be set

**/
Day::Day(int d) {
	day = d;
}

/**
	Assignment Operator
	@param &rhs Right hand of the assignment operator
	@return Day& 
**/
Day& Day::operator=(const Day &rhs) {
	Day *d = new Day(rhs.getDay());
	return *d;
}

/**
	<= Comparison Operator
	@param &rhs Right hand of the <= operator
	@return bool True or False based if the left hand side is less than or equal to right hand side
**/
bool Day::operator<=(const Day &rhs) {
	return (this->getDay() <= rhs.getDay());
}

/**
	+ Addition Operator
	@param &rhs Right hand of the + operator
	@return Day&
**/
Day& Day::operator+(const Day &rhs) {
	Day *newDay;
	newDay = new Day(this->getDay() + rhs.getDay());
	return *newDay;
}

/**
	<< Output Operator
	@param &os output stream, Day& object to be outputted
	@return ostream& output stream
**/
ostream& operator<<(ostream &os, const Day& d) { 
	os << d.getDay();
	return os;
}

#endif DAY_H