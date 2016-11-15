#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "crimen.h"
#include "conjunto.h"

using namespace std;

conjunto::conjunto(){}

conjunto::conjunto(const conjunto & d){

	for(int i = 0 ; i < d.size() ; i++)

		vc[i] = d.getElement(i);

}

conjunto::iterator conjunto::find(const long int & id){

	vector<crimen>::iterator itc = vc.begin();

	if(vc.size())

		while((*itc).getID() <= id){

			if((*itc).getID() == id){

				conjunto::iterator it(itc);
				return it; // Elemento encontrado.

			}
			
			itc++;
			 
		}

	itc = vc.end();
	conjunto::iterator it(itc);
	return it; // Elemento no encontrado.

}

conjunto::entrada conjunto::getElement(int & index) const{

	if(index >= 0 && index < vc.size())

		return vc[index];

	else{

		conjunto::entrada vacio;
		return vacio;

	}

}

conjunto conjunto::findIUCR(const string & iucr) const{

	conjunto resultado;

	if(vc.size())

		for(int i = 0 ; i < size() ; i++)

			if(vc[i].getIUCR() == iucr)

				resultado.insert(vc[i]);

	return resultado;

}

conjunto conjunto::findDESCR(const string & descr) const{

	conjunto resultado;

	if(vc.size())

		for(int i = 0 ; i < size() ; i++)

			if(vc[i].getDescription() == descr)

				resultado.insert(vc[i]);

	return resultado;

}

bool conjunto::insert(const conjunto::entrada & e){

	if(e.getID() > 0){

		if(size()){ // Si no está vacío.

			vector<conjunto::entrada>::iterator it = upper_bound(vc.begin(), vc.end(), e);

			if(it == vc.begin() || (*(it - 1)).getID() < e.getID()){

				vc.insert(it,e);
				return true; // Se puede insertar.

			}

			return false; // No se inserta porque ya existe.

		}

		else // Si está vacío.

			vc.push_back(e);

	}

	return false; // No se inserta porque viola la invariante de
				  // representación (ID > 0).

}

bool conjunto::erase(const long int & id){

	vector<conjunto::entrada>::iterator it;

	for(it = vc.begin() ; it != vc.end() ; it++)

		if((*it).getID() == id){

			vc.erase(it);
			return true;

		}

	return false;

}

bool conjunto::erase(const conjunto::entrada & e){

	return (conjunto::erase(e.getID()));

}

conjunto & conjunto::operator=(const conjunto & org){

	if(this != &org){

		for(int i = 0 ; i < org.size() ; i++)

			vc[i] = org.getElement(i);

	}

	return *this;

}

conjunto::size_type conjunto::size() const{

	return vc.size();

}

bool conjunto::empty() const{

	return vc.empty();

}

bool conjunto::cheq_rep() const{

	if(size() != vc.size() || vc[0].getID() <= 0)

		return false; // Si los tamaños difieren
					  // o el primer elemento incumple ID > 0.

	else

		for(int i = 1 ; i < vc.size() ; i++)

			if((vc[i-1].getID() >= vc[i].getID()) || (vc[i].getID() <= 0))

				return false; // Si se viola el orden creciente o ID es <= 0.

	return true; // Se cumple la invariante de la representación.
	
}

ostream & operator << (ostream & sal, const conjunto & D){

	for(int i = 0 ; i < D.vc.size() ; i++)

		sal << D.vc[i] << endl;

	return sal;

}

// ================================= ITERADORES ========================================/ 


////////////////////////////----ITERATOR----///////////////////////////

conjunto::iterator conjunto::begin(){

	conjunto::iterator sal;
	sal.itv = vc.begin();

	return sal;

}

conjunto::iterator conjunto::end(){

	conjunto::iterator sal;
	sal.itv = vc.end();

	return sal;

}

conjunto::iterator::iterator(){}

conjunto::iterator::iterator(const conjunto::iterator & i){

	itv = i.itv;

}

conjunto::iterator::iterator(const std::vector<conjunto::entrada>::iterator & it){

	itv = it;

}

conjunto::entrada & conjunto::iterator::operator*(){

	return (*itv);

}

conjunto::iterator & conjunto::iterator::operator=(const conjunto::iterator & it){

	itv = it.itv;
	
	return (*this);

}

conjunto::iterator conjunto::iterator::operator++( int ){

	conjunto::iterator sal = *this;
    ++(*this);

    return sal;

}

conjunto::iterator & conjunto::iterator::operator++(){

	itv++;

	return (*this);

}

conjunto::iterator conjunto::iterator::operator--(int){

	conjunto::iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::iterator & conjunto::iterator::operator--(){

	itv--;

	return (*this);

}

bool conjunto::iterator::operator==(const conjunto::iterator & it){

	return (itv == it.itv);

}

bool conjunto::iterator::operator!=(const conjunto::iterator & it){

	return !(*this == it);

}

////////////////////////////----CONST_ITERATOR----///////////////////////////

conjunto::const_iterator conjunto::cbegin() const{

	conjunto::const_iterator sal;
	sal.c_itv = vc.cbegin();

	return sal;

}

conjunto::const_iterator conjunto::cend() const{

	conjunto::const_iterator sal;
	sal.c_itv = vc.cend();

	return sal;

}

conjunto::const_iterator::const_iterator(){}

conjunto::const_iterator::const_iterator(const conjunto::const_iterator & it){

	c_itv = it.c_itv;

}

conjunto::const_iterator::const_iterator(const std::vector<conjunto::entrada>::const_iterator & it){

	c_itv = it;

}

conjunto::const_iterator::const_iterator(const iterator & it){

	c_itv = it.itv;

}

const conjunto::entrada & conjunto::const_iterator::operator*() const{

	return (*c_itv);

}

conjunto::const_iterator & conjunto::const_iterator::operator=(const conjunto::const_iterator & it){

	c_itv = it.c_itv;
	
	return (*this);

}

conjunto::const_iterator conjunto::const_iterator::operator++( int ){

	conjunto::const_iterator sal = *this;
    ++(*this);

    return sal;

}

conjunto::const_iterator & conjunto::const_iterator::operator++(){

	c_itv++;

	return (*this);

}

conjunto::const_iterator conjunto::const_iterator::operator--(int){

	conjunto::const_iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::const_iterator & conjunto::const_iterator::operator--(){

	c_itv--;

	return (*this);

}

bool conjunto::const_iterator::operator==(const const_iterator & it){

	return (c_itv == it.c_itv);

}

bool conjunto::const_iterator::operator!=(const const_iterator & it){

	return !(*this == it);

}

////////////////////////////----DESCRIPTION_ITERATOR----///////////////////////////

conjunto::description_iterator conjunto::dbegin(const string & descr){

	conjunto::description_iterator di;

	di.ptr = this;
	di.descr = descr;
	di.itv = vc.begin();

	if((*di.itv).getDescription().find(descr) != string::npos)

		return di;

	else

		return ++di;

}

conjunto::description_iterator conjunto::dend(){

	conjunto::description_iterator di;

	di.ptr = this;
	di.itv = vc.end();
	
	return di;

}

conjunto::description_iterator::description_iterator(){

	ptr = 0;

}

conjunto::description_iterator::description_iterator(const conjunto::description_iterator & it){

	ptr = it.ptr;
	itv = it.itv;
	descr = it.descr;

}

conjunto::entrada & conjunto::description_iterator::operator*(){

	return (*itv);

}

conjunto::description_iterator & conjunto::description_iterator::operator=(const conjunto::description_iterator & it){

	if(this != &it){

		itv = it.itv;
		descr = it.descr;
		ptr = it.ptr;
		
	}
	
	return (*this);
	
}

conjunto::description_iterator conjunto::description_iterator::operator++( int ){

	conjunto::description_iterator sal = *this;
    ++(*this);

    return sal;
    
}

conjunto::description_iterator & conjunto::description_iterator::operator++(){

	++itv;

	while((itv != (*ptr).vc.end()) && (*itv).getDescription().find(descr) == string::npos)

		++itv;

	return (*this);

}

conjunto::description_iterator conjunto::description_iterator::operator--(int){

	conjunto::description_iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::description_iterator & conjunto::description_iterator::operator--(){

	--itv;

	while((itv != (*ptr).vc.begin()) && (*itv).getDescription().find(descr) == string::npos)
	
		itv--;

	return (*this);

}

bool conjunto::description_iterator::operator==(const conjunto::description_iterator & it){

	return (itv == it.itv);

}

bool conjunto::description_iterator::operator!=(const conjunto::description_iterator & it){

	return !(*this == it);

}

////////////////////////////----CONST_DESCRIPTION_ITERATOR----///////////////////////////

conjunto::const_description_iterator conjunto::cdbegin(const string & descr) const{

	conjunto::const_description_iterator cdi;

	cdi.ptr = this;
	cdi.descr = descr;
	cdi.c_itv = vc.cbegin();

	if((*cdi.c_itv).getDescription().find(descr) != string::npos)

		return cdi;

	else

		return ++cdi;

}

conjunto::const_description_iterator conjunto::cdend() const{

	conjunto::const_description_iterator cdi;

	cdi.ptr = this;
	cdi.c_itv = vc.cend();
	
	return cdi;

}

conjunto::const_description_iterator::const_description_iterator(){

	ptr = 0;

}

conjunto::const_description_iterator::const_description_iterator(const conjunto::const_description_iterator & it){

	ptr = it.ptr;
	c_itv = it.c_itv;
	descr = it.descr;

}

const conjunto::entrada & conjunto::const_description_iterator::operator*() const{

	return (*c_itv);

}

conjunto::const_description_iterator & conjunto::const_description_iterator::operator=(const conjunto::const_description_iterator & it){

	descr = it.descr;
	c_itv = it.c_itv;
	ptr = it.ptr;
	
	return (*this);

}

conjunto::const_description_iterator conjunto::const_description_iterator::operator++( int ){

	conjunto::const_description_iterator sal = *this;
    ++(*this);

    return sal;
    
}

conjunto::const_description_iterator & conjunto::const_description_iterator::operator++(){

	++c_itv;

	while((c_itv != (*ptr).vc.cend()) && (*c_itv).getDescription().find(descr) == string::npos)

		++c_itv;

	return (*this);
	
}

conjunto::const_description_iterator conjunto::const_description_iterator::operator--(int){

	conjunto::const_description_iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::const_description_iterator & conjunto::const_description_iterator::operator--(){

	--c_itv;

	while((c_itv != (*ptr).vc.cbegin()) && (*c_itv).getDescription().find(descr) == string::npos)
	
		c_itv--;

	return (*this);

}

bool conjunto::const_description_iterator::operator==(const conjunto::const_description_iterator & it){

	return c_itv == it.c_itv;

}

bool conjunto::const_description_iterator::operator!=(const conjunto::const_description_iterator & it){

	return !(*this == it);

}

////////////////////////////----ARREST_ITERATOR----///////////////////////////

conjunto::arrest_iterator conjunto::abegin(){

	conjunto::arrest_iterator ai;
	ai.ptr = this;
	ai.itv = vc.begin();
	
	if((*ai.itv).getArrest())

		return ai;

	else

		return ++ai;

}

conjunto::arrest_iterator conjunto::aend(){

	conjunto::arrest_iterator ai;
	ai.ptr = this;
	ai.itv = vc.end();
	
	return ai;

}

conjunto::arrest_iterator::arrest_iterator(){

	ptr = 0;

}

conjunto::arrest_iterator::arrest_iterator(const conjunto::arrest_iterator & it){

	ptr = it.ptr;
	itv = it.itv;

}

conjunto::entrada & conjunto::arrest_iterator::operator*(){

	return (*itv);

}

conjunto::arrest_iterator & conjunto::arrest_iterator::operator=(const conjunto::arrest_iterator & it){

	ptr = it.ptr;
	itv = it.itv;
	
	return (*this);

}

conjunto::arrest_iterator conjunto::arrest_iterator::operator++( int ){

	conjunto::arrest_iterator sal = *this;
    ++(*this);

    return sal;
    
}

conjunto::arrest_iterator & conjunto::arrest_iterator::operator++(){

	++itv;

	while((itv != (*ptr).vc.end()) && !(*itv).getArrest())
	
		++itv;

	return (*this);
	
}

conjunto::arrest_iterator conjunto::arrest_iterator::operator--(int){

	conjunto::arrest_iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::arrest_iterator & conjunto::arrest_iterator::operator--(){

	--itv;

	while(itv != (*ptr).vc.begin() && !(*itv).getArrest())
	
		--itv;

	return (*this);

}

bool conjunto::arrest_iterator::operator==(const conjunto::arrest_iterator & it){

	return (itv == it.itv);

}

bool conjunto::arrest_iterator::operator!=(const conjunto::arrest_iterator & it){

	return !(*this == it);

}

////////////////////////////----CONST_ARREST_ITERATOR----///////////////////////////

conjunto::const_arrest_iterator conjunto::cabegin() const{

	conjunto::const_arrest_iterator cai;
	cai.ptr = this;
	cai.c_itv = vc.cbegin();
	
	return ++cai;

}

conjunto::const_arrest_iterator conjunto::caend() const{

	conjunto::const_arrest_iterator cai;
	cai.ptr = this;
	cai.c_itv = vc.cend();
	
	return cai;

}

conjunto::const_arrest_iterator::const_arrest_iterator(){

	ptr = 0;

}

conjunto::const_arrest_iterator::const_arrest_iterator(const conjunto::const_arrest_iterator & it){

	ptr = it.ptr;
	c_itv = it.c_itv;

}

conjunto::const_arrest_iterator::const_arrest_iterator(const arrest_iterator & it){

	ptr = it.ptr;
	c_itv = it.itv;

}

const conjunto::entrada & conjunto::const_arrest_iterator::operator*() const{

	return (*c_itv);

}

conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator=(const conjunto::const_arrest_iterator & it){

	ptr = it.ptr;
	c_itv = it.c_itv;

	return (*this);

}

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator++( int ){

	conjunto::const_arrest_iterator sal = *this;
    ++(*this);

    return sal;
    
}

conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator++(){

	++c_itv;

	while((c_itv != (*ptr).vc.cend()) && !(*c_itv).getArrest())
	
		++c_itv;

	return (*this);
	
}

conjunto::const_arrest_iterator conjunto::const_arrest_iterator::operator--(int){

	conjunto::const_arrest_iterator sal = *this;
    --(*this);

    return sal;

}

conjunto::const_arrest_iterator & conjunto::const_arrest_iterator::operator--(){

	--c_itv;

	while(c_itv != (*ptr).vc.cbegin() && !(*c_itv).getArrest())
	
		--c_itv;

	return (*this);

}

bool conjunto::const_arrest_iterator::operator==(const conjunto::const_arrest_iterator & it){

	return (c_itv == it.c_itv);

}

bool conjunto::const_arrest_iterator::operator!=(const conjunto::const_arrest_iterator & it){

	return !(*this == it);

}