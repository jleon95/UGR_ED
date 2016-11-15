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

pair<conjunto::entrada,bool>  conjunto::find(const long int & id) const{

	pair<conjunto::entrada,bool> elemento;

	if(vc.size())

		for(int i = 0 ; vc[i].getID() <= id ; i++)

			if(vc[i].getID() == id){

				elemento.first = vc[i];
				elemento.second = true;
				return elemento; // Elemento encontrado.

			}

	elemento.second = false;
	return elemento; // Elemento no encontrado.

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

			vector<conjunto::entrada>::iterator it = upper_bound(vc.begin(),
													vc.end(), e);

			if((*(it - 1)).getID() < e.getID()){

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