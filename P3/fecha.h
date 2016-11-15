/*
 * fecha.h
*/
#ifndef __FECHA_H
#define __FECHA_H

#include <string>
#include <iostream>

using namespace std;

//! Clase fecha, asociada a la definición de una fecha.
/*! fecha::fecha,  .....
 * Descripción contiene toda la información asociada a una fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
*/

class fecha {

public:

/** @brief Constructor por defecto.
*/
	fecha (); //Constructor de fecha por defecto

/** @brief Constructor de copia.
@param f La fecha origen.
*/
	fecha(const fecha & f);

/** @brief Constructor a partir de un string que contiene otra fecha.
@param s Un string con los datos de otra fecha.
*/
	fecha (const string & s); // s es un string con el formato mm/dd/aaaa  hh:mm:ss AM/PM

/** @brief Operador de asignación con otra fecha.
@param f Otra fecha.
*/
	fecha & operator=(const fecha & f);

/** @brief Operador de asignación con un string en formato adecuado.
@param s Un string.
*/
	fecha & operator=(const string & s); // s es un string con el formato mm/dd/aaaa hh:mm:ss AM/PM
	
/** @brief Conversión a string de los datos de fecha.
@return El string con los datos.
*/
	string toString() const; //convierte la fecha a un string

	// Acceso a los datos miembro.
/** @brief Acceso al dato miembro year.
@return year
*/
	int getYear() const;

/** @brief Acceso al dato miembro mon.
@return mon
*/
	int getMonth() const;

/** @brief Acceso al dato miembro mday.
@return mday
*/
	int getDay() const;

/** @brief Acceso al dato miembro hour.
@return hour
*/
	int getHour() const;

/** @brief Acceso al dato miembro min.
@return min
*/
	int getMinute() const;

/** @brief Acceso al dato miembro sec.
@return sec
*/
	int getSecond() const;

	// Operadores relacionales

/** @brief Operador de igualdad.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator==(const fecha & f) const;

/** @brief Operador menor.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator<(const fecha & f) const;

/** @brief Operador mayor.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator>(const fecha & f) const;

/** @brief Operador menor o igual.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator<=(const fecha & f) const;

/** @brief Operador mayor o igual.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator>=(const fecha & f) const;

/** @brief Operador de desigualdad.
@param f fecha a comparar.
@return true o false según cumpla la comparación lógica.
*/
	bool operator!=(const fecha & f) const;

private:

	int  sec;   // seconds of minutes from 0 to 59
	int  min;   // minutes of hour from 0 to 59
	int  hour;  // hours of day from 0 to 24
	int  mday;  // day of month from 1 to 31
	int  mon;   // month of year from 0 to 11
	int  year;  // year since 2000

/** \invariant
 
 IR: rep ==> bool
 
\li sec >= 0 && sec < 60
\li min >= 0 && min < 60
\li hour >= 0 && hour < 24
\li mday > 0 && mday <= 31
\li mon > 0 && mon <= 12
\li year > 0

*/

/** @brief Chequea el Invariante de la representación 
@return true si el invariante es correcto, falso en caso contrario
*/
	bool cheq_rep();

	friend  ostream& operator<< ( ostream& os, const fecha & f);

};

/* @brief imprime fecha con el formato  mm/dd/aaaa hh:mm:ss AM/PM
*/
	ostream& operator<< ( ostream& os, const fecha & f); 

#include "fecha.hxx" // Incluimos la implementacion.


#endif
