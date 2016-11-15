#include <iostream>
#include <string>

using namespace std;

crimen::crimen(){

	ID = 1;
	case_number = "";
	iucr = "";
	primary_type = "";
	description = "";
	location_description = "";
	arrest = false;
	domestic = false;
	latitude = 0;
	longitude = 0;

}

crimen::crimen(const crimen& x){

	ID = x.getID();
	case_number = x.getCaseNumber();
	date = x.getDate();
	iucr = x.getIUCR();
	primary_type = x.getPrimaryType();
	description = x.getDescription();
	location_description = x.getLocationDescription();
	arrest = x.getArrest();
	domestic = x.getDomestic();
	latitude = x.getLatitude();
	longitude = x.getLongitude();

}

void crimen::setID(long int & id){

	ID = id;

}

void crimen::setCaseNumber(const string & s){

	case_number = s;

}

void crimen::setDate(const fecha & d){

	date = d;

}

void crimen::setIUCR(const string & s){

	iucr = s;

}

void crimen::setPrimaryType(const string & s){

	primary_type = s;

}

void crimen::setDescription(const string & s){

	description = s;

}

void crimen::setLocationDescription(const string & s){

	location_description = s;

}

void crimen::setArrest(bool & a){

	arrest = a;

}

void crimen::setDomestic(bool & d){

	domestic = d;

} 

void crimen::setLatitude(double & lat){

	latitude = lat;

}

void crimen::setLongitude(double & lon){

	longitude = lon;

}

long int crimen::getID() const{

	return ID;

}

string crimen::getCaseNumber() const{

	return case_number;	
	
}

fecha crimen::getDate() const{

	return date;	
	
}

string crimen::getIUCR() const{

	return iucr;	
	
}

string crimen::getPrimaryType() const{

	return primary_type;	
	
}

string crimen::getDescription() const{

	return description;	
	
}

string crimen::getLocationDescription() const{

	return location_description;
	
}

bool crimen::getArrest() const{

	return arrest;	
	
}

bool crimen::getDomestic() const{

	return domestic;	
	
}

double crimen::getLatitude() const{

	return latitude;	
	
}

double crimen::getLongitude() const{

	return longitude;	
	
}

crimen & crimen::operator=(const crimen & c){

	if(this != &c){

		ID = c.getID();
		case_number = c.getCaseNumber();
		date = c.getDate();
		iucr = c.getIUCR();
		primary_type = c.getPrimaryType();
		description = c.getDescription();
		location_description = c.getLocationDescription();
		arrest = c.getArrest();
		domestic = c.getDomestic();
		latitude = c.getLatitude();
		longitude = c.getLongitude();

	}

	return *this;

}

bool crimen::operator==(const crimen & x) const{

	return ID == x.getID();

}

bool crimen::operator<(const crimen & x) const{

	return ID < x.getID();

}

bool crimen::cheq_rep(){

	return (ID > 0);

}

bool LessFecha::operator()(const crimen & a, const crimen & b){

	return (a.getDate() < b.getDate()); // devuelve verdadero si el crimen a precede a b en el tiempo

}

bool GreaterFecha::operator()(const crimen & a, const crimen & b){

	return (a.getDate() > b.getDate()); // devuelve verdadero si el crimen b precede a a en el tiempo

}

bool LessIUCR::operator()(const crimen & a, const crimen & b){

	return (a.getIUCR() < b.getIUCR()); // devuelve verdadero si el crimen a precede a b respecto al IUCR

}

ostream& operator<< ( ostream& os, const crimen& c){

	os << c.ID << "," << c.case_number << "," << c.date.toString()
		<< "," << c.iucr << "," << c.primary_type << ","
		<< c.description << "," << c.location_description
		<< "," << c.arrest << "," << c.domestic << ","
		<< c.latitude << "," << c.longitude;

	return os;

}
