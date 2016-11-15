#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "fecha.h"

using namespace std;

fecha::fecha(){

	sec = 0;
	min = 0;
	hour = 0;
	mday = 1;
	mon = 1;
	year = 1;

}

fecha::fecha(const fecha & f){

	sec = f.getSecond();
	min = f.getMinute();
	hour = f.getHour();
	mday = f.getDay();
	mon = f.getMonth();
	year = f.getYear();

}

fecha::fecha(const string & s){

	mon = atoi(s.substr(0,2).c_str());
	mday = atoi(s.substr(3,2).c_str());
	year = atoi(s.substr(8,2).c_str());
	hour = atoi(s.substr(11,2).c_str());
	min = atoi(s.substr(14,2).c_str());
	sec = atoi(s.substr(17,2).c_str());

	if(s[20] == 'P')

		hour += 12;

}
  
fecha & fecha::operator=(const fecha & f){

	if(this != &f){

		sec = f.getSecond();
		min = f.getMinute();
		hour = f.getHour();
		mday = f.getDay();
		mon = f.getMonth();
		year = f.getYear();

	}

	return *this;

}

fecha & fecha::operator=(const string & s){

	mon = atoi(s.substr(0,2).c_str());
	mday = atoi(s.substr(3,2).c_str());
	year = atoi(s.substr(8,2).c_str());
	hour = atoi(s.substr(11,2).c_str());
	min = atoi(s.substr(14,2).c_str());
	sec = atoi(s.substr(17,2).c_str());

	if(s[20] == 'P')

		hour += 12;

	return *this;

} // s es un string con el formato mm/dd/aaaa hh:mm:ss AM/PM

string fecha::toString() const{

	stringstream convert;

	if(mon < 10)

		convert << '0';

	convert << mon << '/';

	if(mday < 10)

		convert << '0';

	convert << mday << '/' << (year+2000) << ' ';
			
	if(hour < 10)

		convert << '0';	

	convert << (hour%12) << ':';

	if(min < 10)

		convert << '0';

	convert << min << ':';

	if(sec < 10)

		convert << '0';

	convert << sec << ' ';

	string date = convert.str();

	if(hour/12 > 0)

		date += "PM";

	else

		date += "AM";

	return date;
	
} //convierte la fecha a un string

bool fecha::operator==(const fecha & f) const{

	bool same = true;

	if((mon != f.getMonth()) || (mday != f.getDay()) || (year != f.getYear())
		|| (hour != f.getHour()) || (min != f.getMinute()) || (sec != f.getSecond()))

		same = false;

	return same;

}

bool fecha::operator<(const fecha & f) const{

	return(year < f.getYear() ||
		(year == f.getYear() && mon < f.getMonth()) ||
		(year == f.getYear() && mon == f.getMonth() && mday < f.getDay()) ||
		(year == f.getYear() && mon == f.getMonth() && mday == f.getDay() && hour < f.getHour()) ||
		(year == f.getYear() && mon == f.getMonth() && mday == f.getDay() && hour == f.getHour() && min < f.getMinute()) ||
		(year == f.getYear() && mon == f.getMonth() && mday == f.getDay() && hour == f.getHour() && min == f.getMinute() && sec < f.getSecond()));

}

bool fecha::operator>(const fecha & f) const{

	return (f < *this);

}

bool fecha::operator<=(const fecha & f) const{

	return !(*this > f);

}

bool fecha::operator>=(const fecha & f) const{

	return !(*this < f);

}

bool fecha::operator!=(const fecha & f) const{

	return !(*this == f);

}

int fecha::getYear() const{

	return year;

}

int fecha::getMonth() const{

	return mon;
	
}

int fecha::getDay() const{

	return mday;
	
}

int fecha::getHour() const{

	return hour;
	
}

int fecha::getMinute() const{

	return min;
	
}

int fecha::getSecond() const{

	return sec;
	
}

bool fecha::cheq_rep(){

	return !(sec < 0 || sec > 59 || min < 0 || min > 59 ||
	hour < 0 || hour > 23 || mday < 1 || mday > 31 ||
	mon < 1 || mon > 12 || year < 0);

	// Basta con que una condición de las anteriores 
	// sea cierta para que el invariante se incumpla.

}

ostream& operator<< (ostream& os, const fecha & f){

	string date = f.toString();

	os << date;

	return os;

}