#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "crimen.h"
#include "conjunto.h"

using namespace std;

template <class Cmp>
conjunto<Cmp>::conjunto(){}

template <class Cmp>
conjunto<Cmp>::conjunto(typename conjunto<Cmp>::iterator ini, typename conjunto<Cmp>::iterator fin){

	while(ini != fin){

		insert(*ini);
		++ini;

	}
}

template <class Cmp>
conjunto<Cmp>::conjunto(const conjunto<Cmp> & d){

	for(int i = 0 ; i < d.size() ; i++)

		vc[i] = d.getElement(i);

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::find(const crimen & c){

	int sup = vc.size()-1;
	int medio, inf = 0;
	bool encontrado = false;

	vector<conjunto::entrada>::iterator itc = vc.begin();

	while(sup >= inf && !encontrado){

		medio = (inf+sup) / 2;

		if(!comp(vc[medio], c) && !comp(c, vc[medio])){ // comparamos igualdad entre crimen

			itc = vc.begin() + medio;
			encontrado = true;

		}

		else if(comp(vc[medio],c)) // comparamos menor entre crimen

			inf = medio + 1;

		else

			sup = medio - 1;

	}

	conjunto<Cmp>::iterator it(itc);

	return it;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::find(const crimen & c) const{

	int sup = vc.size()-1;
	int medio, inf = 0;
	bool encontrado = false;

	vector<conjunto::entrada>::const_iterator itc = vc.cbegin();

	while(sup >= inf && !encontrado){

		medio = (inf+sup) / 2;

		if(!comp(vc[medio], c) && !comp(c, vc[medio])){ // comparamos igualdad entre crimen

			itc = vc.cbegin() + medio;
			encontrado = true;

		}

		else if(comp(vc[medio],c)) // comparamos menor entre crimen

			inf = medio + 1;

		else

			sup = medio - 1;

	}

	conjunto<Cmp>::const_iterator it(itc);

	return it;

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::find(const long int & id){

	typename conjunto<Cmp>::iterator itc;

	for(itc = begin() ; itc != end() ; ++itc)

		if((*itc).getID() == id)

			return itc;

	return itc;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::find(const long int & id) const{

	typename conjunto<Cmp>::const_iterator itc;

	for(itc = cbegin() ; itc != cend() ; ++itc)

		if((*itc).getID() == id)

			return itc;

	return itc;

}

template <class Cmp>
typename conjunto<Cmp>::entrada conjunto<Cmp>::getElement(int & index) const{

	if(index >= 0 && index < vc.size())

		return vc[index];

	else{

		conjunto<Cmp>::entrada vacio;
		return vacio;

	}
}

template <class Cmp>
conjunto<Cmp> conjunto<Cmp>::findIUCR(const string & iucr) const{

	conjunto<Cmp> resultado;

	if(vc.size())

		for(int i = 0 ; i < size() ; i++)

			if(vc[i].getIUCR() == iucr)

				resultado.insert(vc[i]);

	return resultado;

}

template <class Cmp>
conjunto<Cmp> conjunto<Cmp>::findDESCR(const string & descr) const{

	conjunto resultado;

	if(vc.size())

		for(int i = 0 ; i < size() ; i++)

			if(vc[i].getDescription() == descr)

				resultado.insert(vc[i]);

	return resultado;

}

template <class Cmp>
bool conjunto<Cmp>::insert(const conjunto<Cmp>::entrada & e){


	if(e.getID() > 0){

		if(size()){ // Si no está vacío.

			vector<conjunto::entrada>::iterator it = std::upper_bound(vc.begin(), vc.end(), e, comp);

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

template <class Cmp>
bool conjunto<Cmp>::erase(const long int & id){

	vector<conjunto::entrada>::iterator it;

	for(it = vc.begin() ; it != vc.end() ; it++)

		if((*it).getID() == id){

			vc.erase(it);
			return true;

		}

	return false;

}

template <class Cmp>
bool conjunto<Cmp>::erase(const conjunto<Cmp>::entrada & e){

	return (conjunto<Cmp>::erase(e.getID()));

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::lower_bound(const conjunto<Cmp>::entrada & x){

	conjunto<Cmp>::iterator it(std::lower_bound(vc.begin(), vc.end(), x, comp));

	return it;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::lower_bound(const conjunto<Cmp>::entrada & x) const{

	conjunto<Cmp>::const_iterator it(std::lower_bound(vc.cbegin(), vc.cend(), x, comp));

	return it;

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::upper_bound(const conjunto<Cmp>::entrada & x){

	conjunto<Cmp>::iterator it(std::upper_bound(vc.begin(), vc.end(), x, comp));

	return it;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::upper_bound(const conjunto<Cmp>::entrada & x) const{

	conjunto<Cmp>::const_iterator it(std::upper_bound(vc.cbegin(), vc.cend(), x, comp));

	return it;

}

template <class Cmp>
conjunto<Cmp> & conjunto<Cmp>::operator=(const conjunto<Cmp> & org){

	if(this != &org){

		for(int i = 0 ; i < org.size() ; i++)

			vc[i] = org.getElement(i);

	}

	return *this;

}

template <class Cmp>
typename conjunto<Cmp>::size_type conjunto<Cmp>::size() const{

	return vc.size();

}

template <class Cmp>
bool conjunto<Cmp>::empty() const{

	return vc.empty();

}

template <class Cmp>
bool conjunto<Cmp>::cheq_rep() const{

	if(size() != vc.size() || vc[0].getID() <= 0)

		return false; // Si los tamaños difieren
					  // o el primer elemento incumple ID > 0.

	else

		for(int i = 1 ; i < vc.size() ; i++)

			if((vc[i-1].getID() >= vc[i].getID()) || (vc[i].getID() <= 0))

				return false; // Si se viola el orden creciente o ID es <= 0.

	return true; // Se cumple la invariante de la representación.
	
}

template <class Cmp>
ostream & operator << (ostream & sal, const conjunto<Cmp> & D){

	for(auto it = D.cbegin() ; it != D.cend() ; ++it)

		sal << *it << endl;

	return sal;

}

// ================================= ITERADORES ========================================/ 


////////////////////////////----ITERATOR----///////////////////////////

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::begin(){

	conjunto<Cmp>::iterator sal;
	sal.itv = vc.begin();

	return sal;

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::end(){

	conjunto<Cmp>::iterator sal;
	sal.itv = vc.end();

	return sal;

}

template <class Cmp>
conjunto<Cmp>::iterator::iterator(){}

template <class Cmp>
conjunto<Cmp>::iterator::iterator(const conjunto<Cmp>::iterator & i){

	itv = i.itv;

}

template <class Cmp>
conjunto<Cmp>::iterator::iterator(const std::vector<conjunto<Cmp>::entrada>::iterator & it){

	itv = it;

}

template <class Cmp>
typename conjunto<Cmp>::entrada & conjunto<Cmp>::iterator::operator*(){

	return (*itv);

}

template <class Cmp>
typename conjunto<Cmp>::iterator & conjunto<Cmp>::iterator::operator=(const conjunto<Cmp>::iterator & it){

	itv = it.itv;
	
	return (*this);

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::iterator::operator++( int ){

	conjunto<Cmp>::iterator sal = *this;
    ++(*this);

    return sal;

}

template <class Cmp>
typename conjunto<Cmp>::iterator & conjunto<Cmp>::iterator::operator++(){

	itv++;

	return (*this);

}

template <class Cmp>
typename conjunto<Cmp>::iterator conjunto<Cmp>::iterator::operator--(int){

	conjunto<Cmp>::iterator sal = *this;
    --(*this);

    return sal;

}

template <class Cmp>
typename conjunto<Cmp>::iterator & conjunto<Cmp>::iterator::operator--(){

	itv--;

	return (*this);

}

template <class Cmp>
bool conjunto<Cmp>::iterator::operator==(const conjunto<Cmp>::iterator & it){

	return (itv == it.itv);

}

template <class Cmp>
bool conjunto<Cmp>::iterator::operator!=(const conjunto<Cmp>::iterator & it){

	return !(*this == it);

}

////////////////////////////----CONST_ITERATOR----///////////////////////////

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::cbegin() const{

	conjunto<Cmp>::const_iterator sal;
	sal.c_itv = vc.cbegin();

	return sal;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::cend() const{

	conjunto<Cmp>::const_iterator sal;
	sal.c_itv = vc.cend();

	return sal;

}

template <class Cmp>
conjunto<Cmp>::const_iterator::const_iterator(){}

template <class Cmp>
conjunto<Cmp>::const_iterator::const_iterator(const conjunto<Cmp>::const_iterator & it){

	c_itv = it.c_itv;

}

template <class Cmp>
conjunto<Cmp>::const_iterator::const_iterator(const std::vector<conjunto<Cmp>::entrada>::const_iterator & it){

	c_itv = it;

}

template <class Cmp>
conjunto<Cmp>::const_iterator::const_iterator(const iterator & it){

	c_itv = it.itv;

}

template <class Cmp>
const typename conjunto<Cmp>::entrada & conjunto<Cmp>::const_iterator::operator*() const{

	return (*c_itv);

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator & conjunto<Cmp>::const_iterator::operator=(const conjunto<Cmp>::const_iterator & it){

	c_itv = it.c_itv;
	
	return (*this);

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::const_iterator::operator++( int ){

	conjunto<Cmp>::const_iterator sal = *this;
    ++(*this);

    return sal;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator & conjunto<Cmp>::const_iterator::operator++(){

	c_itv++;

	return (*this);

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator conjunto<Cmp>::const_iterator::operator--(int){

	conjunto<Cmp>::const_iterator sal = *this;
    --(*this);

    return sal;

}

template <class Cmp>
typename conjunto<Cmp>::const_iterator & conjunto<Cmp>::const_iterator::operator--(){

	c_itv--;

	return (*this);

}

template <class Cmp>
bool conjunto<Cmp>::const_iterator::operator==(const conjunto<Cmp>::const_iterator & it){

	return (c_itv == it.c_itv);

}

template <class Cmp>
bool conjunto<Cmp>::const_iterator::operator!=(const conjunto<Cmp>::const_iterator & it){

	return !(*this == it);

}