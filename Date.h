#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Day.h"
#include "Year.h"
#include "Month.h"

using namespace std;

const int NUM_MONTHS = 12;
const int DAYS_IN_MONTHS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
enum { january, february, march, april, may, june, july, august, september, october, november, december };

class Date {
	private:
		Year *year;
		Month *month;
		Day *day;
	public:
		Date();
		Date(int y, int m, int d);
		Date(Year y, Month m, Day d);
		void read(string d);

		// Getter Methods
		Day getDay() const { return *day; }
		Month getMonth() const { return *month; }
		Year getYear() const { return *year; }

		// Setter Methods
		void setDay(Day d) { day = new Day(d.getDay());}
		void setMonth(Month m) { month = new Month(m.getMonth()); }
		void setYear(Year y) { year = new Year(y.getYear()); }

		Date& operator+(const string &rhs);
		Date operator+(const Date &rhs);
		Date&  operator=(const Date &rhs);
		void subtract(Day d);
		//Date & operator-(const string &rhs);
		friend ostream& operator<<(ostream &os, const Date& dt);
		int calcLeapYear(Year initialYear);
		void add(Month m, int *carry); //private methods, since they should not be called by the user?
		void add(Year y, int *carry);
		void add(Day d, int *carry, int *yearCarry);
		void readNumeric(string d);
		void readAlpha(string d);
		string toLowerCase(string d);
};

Date::Date() {
	year = new Year();
	month = new Month();
	day = new Day();
}

Date::Date(Year y, Month m, Day d) {
	year = new Year(y.getYear());
	month = new Month(m.getMonth());
	day = new Day(d.getDay());
}

Date::Date(int y, int m, int d) {
	year = new Year(y);
	month = new Month(m);
	day = new Day(d);
}

void Date::read(string d) {
	if(isdigit(d[0]))
	{
		readNumeric(d);
	}
	else
	{
		readAlpha(d);
	}
}

void Date::readNumeric(string d) {
	// convert to string stream, is porbably best
	stringstream ss(d);
	int yr, mon, dy;
	char split_char = '/';

	istringstream split(d);
	vector<string> tokens;

	for(string each; getline(split, each, split_char); tokens.push_back(each));

	mon = atoi(tokens[0].c_str());
	dy = atoi(tokens[1].c_str());
	yr = atoi(tokens[2].c_str());

	year = new Year(yr);
	month = new Month(mon);
	day = new Day(dy);

}

void Date::readAlpha(string d) {
	stringstream ss(d);
	int yr, mon, dy;
	char split_char = ',';

	istringstream split(d);
	vector<string> tokens;
	string each;

	getline(split, each, ' ');
	tokens.push_back(each);
	getline(split, each, ',');
	tokens.push_back(each);
	getline(split, each);
	tokens.push_back(each);

	toLowerCase(tokens[0]);				// Need to convert to lowercase to match the enum
	// need to check if it is enum
	mon = atoi(tokens[0].c_str()) + 1;
	dy = atoi(tokens[1].c_str());
	yr = atoi(tokens[2].c_str());

	year = new Year(yr);
	month = new Month(mon);
	day = new Day(dy);

}

string Date::toLowerCase(string d) {
	std::transform(d.begin(), d.end(), d.begin(), ::tolower);
	return d;
}

Date& Date::operator+(const string &rhs) {
	char typeDate;
	const char* rhsArray = rhs.c_str();
	int amount, indexChar;
	Date *endDate = new Date();
	Date initialDate = *this;
	
	typeDate = rhs.back();


	if(typeDate == 'y' || typeDate == 'Y')
	{
		indexChar = rhs.find('y');
		amount = atoi(rhs.substr(0, indexChar).c_str());
		//cout << "Index Char: " << indexChar << endl;
		//cout << "Amount: " << amount << endl;
		Date *newDate = new Date(amount, 0, 0);
		*endDate = initialDate + *newDate;
	}
	else if(typeDate == 'm' || typeDate =='M')
	{
		indexChar = rhs.find('m');
		amount = atoi(rhs.substr(0, indexChar).c_str());
		//cout << "Index Char: " << indexChar << endl;
		//cout << "Amount: " << amount << endl;
		Date *newDate = new Date(0, amount, 0);
		*endDate = initialDate + *newDate;
	}
	else if(typeDate == 'd' || typeDate =='D')
	{
		indexChar = rhs.find('d');
		amount = atoi(rhs.substr(0, indexChar).c_str());
		//cout << "Index Char: " << indexChar << endl;
		//cout << "Amount: " << amount << endl;
		Date *newDate = new Date(0, 0, amount);
		*endDate = initialDate + *newDate;
	}
	else
	{
		cout << "\nInvalid data type. Please either enter y, m, or d to signify if you want to add years, months, or days.\n\n";
	}
	return *endDate;
}

Date Date::operator+(const Date &rhs) {
	Date finalDate = *this;
	//cout << "First Date: " << finalDate << endl << endl;
	Year initialYear = this->getYear();
	int carry = 0, yearCarry = 0, leapDays;

	finalDate.add(rhs.getDay(), &carry, &yearCarry);
	//cout << "Day: " << finalDate.getDay().getDay();
	finalDate.add(rhs.getMonth(), &carry);
	finalDate.add(rhs.getYear(), &yearCarry);
	leapDays = finalDate.calcLeapYear(initialYear);
	if (leapDays > 0)
	{
		Day *newDay = new Day(leapDays);
		carry = 0;
		yearCarry = 0;
		finalDate.subtract(*newDay);
		//cout << "it's here: " << finalDate << endl;
	}

	//cout << finalDate;
	return finalDate;
}

void Date::subtract(Day d)
{
	int difference;
	int leapDays = d.getDay();
	int currentDay = this->getDay().getDay();
	Month currentMonth = this->getMonth();
	int carry = 0;

	do
	{
		difference = currentDay - leapDays;
		if(difference < 0)
		{
			currentDay = DAYS_IN_MONTHS[currentMonth.getMonth() - 1] + difference;
			carry = -currentMonth.add(-1);
			//cout << carry << endl;
			leapDays -= currentDay;
			currentDay = DAYS_IN_MONTHS[currentMonth.getMonth() - 1];
		}
	}while(leapDays > 0);

	this->setDay(currentDay);
	this->setMonth(currentMonth);
	this->setYear(this->getYear().getYear() - 1);
}

void Date::add(Day d, int *carry, int *yearCarry) {
	Date addDate = *this;
	Day *finalDay;
	int amountOfDaysFromEnd, daysInMonth, currentDay = this->getDay().getDay();
	Month currentMonth = this->getMonth();

	if ( d.getDay() != 0)
	{
		finalDay = new Day(d.getDay());		// total amount of "days"
		//cout << "Final: " << *finalDay;
		daysInMonth = DAYS_IN_MONTHS[currentMonth.getMonth() - 1];
		do
		{
				// Need to calculate if it is over the amount of the days of the month
				//cout << currentDay << endl;
				amountOfDaysFromEnd = daysInMonth - currentDay;
				//cout << amountOfDaysFromEnd << endl;
				//cout << finalDay->getDay() - daysInMonth << endl;
				//cout << finalDay->getDay() - amountOfDaysFromEnd << endl;
			 
				if(finalDay->getDay() - amountOfDaysFromEnd > 0)
				{
					*carry += 1;
					//cout << "Carry: " << *carry;
					//cout << *finalDay << endl;
					finalDay->setDay(finalDay->getDay() - amountOfDaysFromEnd);
					//cout << "Amount of Days from End: " << amountOfDaysFromEnd << endl;
					//cout << "Days in Months: " << DAYS_IN_MONTHS[currentMonth.getMonth()] << endl << endl;
					*yearCarry += currentMonth.add(1);
					//cout << "Current Month: " << currentMonth.getMonth() << endl;
					currentDay = 1;
					//cout << " Final: " << *finalDay << endl;
				}
				daysInMonth = DAYS_IN_MONTHS[currentMonth.getMonth() - 1];
		}while(finalDay->getDay() / DAYS_IN_MONTHS[currentMonth.getMonth() - 1] != 0); 
		//cout << "Final: " << *finalDay << endl;
		this->setDay(*finalDay);
		delete finalDay;
	}

}


void Date::add(Month m, int *carry) {
	Month *finalMonth = new Month(this->getMonth().getMonth());
	Date addDate = *this;
	int amountOfMonthsFromEnd, numDays, monthCarry = 0;
	int yearCarry = 0;
	
	//cout << "Final Month: " << *finalMonth << endl;
	finalMonth->add(*carry);			// Add carry from days first
	//cout << "Final Month: " << *finalMonth << endl;
	numDays = m.convertToDays();
	Day *temp = new Day(numDays);

	this->add(*temp, &monthCarry, &yearCarry);
	delete temp;
	if(monthCarry != 0)
	{
		monthCarry--;
		//cout << "finalmonth:" << finalMonth->getMonth();
		//cout << "carry: " << monthCarry << endl << endl;
		finalMonth->add(monthCarry);
		//cout << finalMonth->getMonth();
		if(finalMonth->getMonth() > NUM_MONTHS)
		{
			*carry = finalMonth->getMonth() / NUM_MONTHS;
			finalMonth->setMonth(finalMonth->getMonth() % 12);
		}
		this->setMonth(*finalMonth);
		delete finalMonth;
	}

}

void Date::add(Year y, int *carry) {
	Year finalYear;
	Date *finalDate;

	finalYear = y + this->getYear();
	//finalYear.add(*carry);
	// need to check for leap year here
	//cout << finalYear;
	this->setYear(finalYear);
	
}

int Date::calcLeapYear(Year initialYear)
{
	int current, initial, acc = 0;
	
	current = this->getYear().getYear();
	//cout << "Current: " << current;
	initial = initialYear.getYear();
	//cout << "Initial: " << initial;
	
	if(initial != current)
	{
		while (true)
		{
			if((initial % 4 == 0 && initial % 100 != 0) || initial % 400 == 0)
				acc++;
			if(initial + 1 == current) break;
				initial++;
		}
	}

	return acc;
}

Date& Date::operator=(const Date &rhs) {
	Date *newD = new Date(rhs.getYear(), rhs.getMonth(), rhs.getDay());
	//cout << rhs.getYear() << rhs.getMonth() << rhs.getDay() << endl;
	//cout << newD->getYear() << newD->getMonth() << newD->getDay() << endl;

	this->setYear(rhs.getYear());
	this->setMonth(rhs.getMonth());
	this->setDay(rhs.getDay());

	return *newD;
}

ostream& operator<<(ostream &os, const Date& dt) {
	os << *(dt.month) << "/" << *(dt.day) << "/" << *(dt.year);
	return os;
}


#endif DATE_H