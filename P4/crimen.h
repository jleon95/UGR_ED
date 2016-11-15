/* 
 * crimen.h
*/
#ifndef __CRIMEN_H
#define __CRIMEN_H

#include <string>
#include <iostream> 

#include "fecha.h"
//! Clase crimen, asociada a la definición de un crimen 
/*! crimen::crimen,  .....
 * Descripción contiene toda la información asociada a un crimen.
*/


class crimen {

 public:

/** @brief Constructor por defecto. 
*/
	crimen();
/** @brief Constructor de copia. 
*/
	crimen(const crimen& x);

/** @brief Modificación del dato miembro ID.
@param  id nuevo ID
*/
	void setID(long int & id);

/** @brief Modificación del dato miembro case_number.
@param s nuevo case_number
*/
	void setCaseNumber(const string &  s);

/** @brief Modificación del dato miembro fecha.
@param d nueva fecha
*/
	void setDate(const fecha & d);

/** @brief Modificación del dato miembro iucr.
@param s nuevo iucr
*/
	void setIUCR(const string & s);

/** @brief Modificación del dato miembro primary_type.
@param s nuevo primary_type
*/
	void setPrimaryType(const string & s);

/** @brief Modificación del dato miembro description.
@param s nuevo description
*/
	void setDescription(const string & s);

/** @brief Modificación del dato miembro location_description.
@param s nuevo location_description
*/
	void setLocationDescription(const string & s);

/** @brief Modificación del dato miembro arrest.
@param a nuevo arrest
*/
	void setArrest(bool & a);

/** @brief Modificación del dato miembro domestic.
@param d nuevo domestic
*/
	void setDomestic(bool & d); 

/** @brief Modificación del dato miembro latitude.
@param lat nuevo latitude
*/
	void setLatitude(double & lat);

/** @brief Modificación del dato miembro longitude.
@param nuevo longitude
*/
	void setLongitude(double & lon);

/** @brief Acceso al dato miembro ID.
@return ID
*/
	long int getID() const;

/** @brief Acceso al dato miembro case_number.
@return case_number
*/
	string getCaseNumber() const;

/** @brief Acceso al dato miembro date.
@return date
*/
	fecha getDate() const;

/** @brief Acceso al dato miembro iucr.
@return iucr
*/
	string getIUCR() const;

/** @brief Acceso al dato miembro primary_type.
@return primary_type
*/
	string getPrimaryType() const;

/** @brief Acceso al dato miembro description.
@return description
*/
	string getDescription() const;

/** @brief Acceso al dato miembro location_description.
@return location_description
*/
	string getLocationDescription() const;

/** @brief Acceso al dato miembro arrest.
@return arrest
*/
	bool getArrest() const;

/** @brief Acceso al dato miembro domestic.
@return domestic
*/
	bool getDomestic() const;

/** @brief Acceso al dato miembro latitude.
@return latitude
*/
	double getLatitude() const;

/** @brief Acceso al dato miembro longitude.
@return longitude
*/
	double getLongitude() const;

/** @brief Operador de asignación.
@param[in] c crimen a copiar.
 Crea una copia exacta de c.
*/
	crimen & operator=(const crimen & c);

/** @brief Operador de igualdad. Se asume que cada ID es única.
@param x crimen a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator==(const crimen & x) const;

/** @brief Operador menor.
@param x crimen a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator<(const crimen & x) const;

 private:

/** \invariant
 
 IR: rep ==> bool
 
\li ID > 0
*/

/** @brief Chequea el Invariante de la representacion 
@return true si el invariante es correcto, falso en caso contrario
*/
	bool cheq_rep();

	friend ostream& operator<< ( ostream& os, const crimen& c);

	//Atributos 
	long int ID;
	string case_number;
	fecha date;
	string iucr;
	string primary_type;
	string description;
	string location_description;
	bool arrest;
	bool domestic;
	double latitude;
	double longitude; 

};

/** @brief Imprime el contenido del objeto crimen.
*/
ostream& operator<< ( ostream& os, const crimen& c);


//! Clase LessFecha que representa el functor less<fecha>.
class LessFecha{

public:

/** @brief Operador paréntesis.
@param a primer crimen a comparar.
@param b segundo crimen a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator()(const crimen & a, const crimen & b);

};

//! Clase GreaterFecha que representa el functor greater<fecha>.
class GreaterFecha{

public:

/** @brief Operador paréntesis.
@param a primer crimen a comparar.
@param b segundo crimen a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator()(const crimen & a, const crimen & b);

};

//! Clase LessIUCR que representa el functor less<IUCR>.
class LessIUCR{

public:

/** @brief Operador paréntesis.
@param a primer crimen a comparar.
@param b segundo crimen a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator()(const crimen & a, const crimen & b);

};

#include "crimen.hxx"
#endif
