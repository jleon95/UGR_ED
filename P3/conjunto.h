/* 
 * conjunto.h
*/

#ifndef __CONJUNTO_H
#define __CONJUNTO_H
#include <string>
#include <vector>
#include <iostream> 
#include "crimen.h"

//! Clase conjunto
/*! Métodos--> conjunto:: conjunto(), insert(), find(),  findIUCR(), findDESCR(), erase(), size(), empty()

 * Tipos--> conjunto::entrada, conjunto::size_type

 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

* Asociado al conjunto, tendremos el tipo  \code conjunto::entrada \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso delitos (crimenes). Para esta entrada el requisito es que tenga definidos el operador< y operator=

* Además encontraremos el tipo \code conjunto::size_type \endcode que permite hacer referencia al número de elementos en el conjunto.

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática. 
 
 Ejemplo de su uso:
\code
...
conjunto DatosChicago, agresion;
crimen cr;

conjunto.insert(cr);
...
agresion = conjunto.findDESCR("BATTERY");

if (!agresion.empty()){
 cout <<"Tenemos "<< agresion.size() << " agresiones" << endl;
 cout << agresion << endl;
} else "No hay agresiones en el conjunto" << endl;
...
\endcode
 */





class conjunto
{  
public:
        /** @brief entrada Permite hacer referencia a los elementos almacenados en cada una de las posiciones del conjunto.
         */
	typedef crimen entrada;
	/** @brief size_type Número de elementos en el conjunto.
         */
	typedef unsigned int size_type;
	/** @brief Constructor primitivo. 
	
	*/
	conjunto();

	class iterator;  
   	class const_iterator;
   	class arrest_iterator; // Iterador sobre los delitos que implicaron un arresto (Arrest==true)
   	class const_arrest_iterator;
   	class description_iterator;  // Iterador sobre los delitos que concuerdan con la descripcion
   	class const_description_iterator;
	
	/** @brief Constructor de copia.
	@param[in] d conjunto a copiar
	*/
	conjunto(const conjunto & d);

	/** @brief Devuelve un elemento en una posición concreta.
	@param index posición del elemento
	@return elemento en la posición indicada o elemento por defecto 
	*/
	conjunto::entrada getElement(int & index) const;
		
	/** @brief Busca un crimen en el conjunto.
	@param id identificador del crimen a buscar
	@return Si existe una entrada en el conjunto devuelve un par con una copia de la entrada en el conjunto y con el segundo valor a true. Si  no se encuentra devuelve la entrada con la definicion por defecto y false 
	@post no modifica el conjunto.
	\verbatim Uso
       

	if (C.find(12345).second ==true) cout << "Esta" ;
	else cout << "No esta";
	\endverbatim
	*/
	conjunto::iterator find( const long int & id);

	/** @brief Busca los crímenes con el mismo código IUCR
	@param icur identificador del crimen  buscar
	@return Devuelve un  conjunto con todos los crimenes con el codigo IUCR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findIUCR("0460");
	\endverbatim
	*/
	conjunto findIUCR( const string & iucr) const;

/** @brief Busca los crímenes que contienen una determinada descripción 
	@param descr string que representa la descripcion del delito buscar
	@return Devuelve un  conjunto con todos los crimenes  que contengan descr en su descripcionR. Si no existe ninguno devuelve el conjunto vacio.
	@post no modifica el conjunto.
	\verbatim Uso
        vector<crimen> C, A;
        ....
        A = C.findDESCR("BATTERY");
	\endverbatim
	*/
	conjunto findDESCR( const string & descr) const;

/** @brief Inserta una entrada en el conjunto.
@param e entrada a insertar
@return true si la entrada se ha podido insertar con éxito. False en caso contrario
@post 	 Si e no esta en el conjunto, el size() sera incrementado en 1.
*/
	bool insert( const conjunto::entrada & e);

	
	
/** @brief Borra el delito dado un identificador.

Busca la entrada con id en el conjunto  y si la encuentra la borra.

@param[in] id a borrar
@return true si la entrada se ha podido borrar con éxito. False en caso contrario
@post Si esta en el conjunto su tamaño se decrementa en 1.
*/

	bool erase(const long int & id);


/** @brief Borra un crimen con identificador dado por e.getID() en el conjunto.


Busca la entrada con id en el conjunto (o e.getID() en el segundo caso) y si la encuentra la borra

@param[in] entrada con e.getID() que queremos borrar, el resto de los valores no son tenidos en cuenta
@return true si la entrada se ha podido borrar con éxito. False en caso contrario
@post Si esta en el conjunto su tamaño se decrementa en 1.
*/

	bool erase(const conjunto::entrada & e);
         

/** @brief Operador de asignación.
@param[in] org conjunto  a copiar
Crea un conjunto duplicado exacto de org.
*/
	conjunto & operator=( const conjunto & org);

	/** @brief Número de entradas en el conjunto.
@post  No se modifica el conjunto.
*/

	size_type size() const;


/** @brief Chequea si el conjunto está vacío.
   @return true si size()==0, false en caso contrario
*/
	bool empty() const;

	
	// ================================= ITERADORES ========================================/ 


////////////////////////////----ITERATOR----///////////////////////////

/**@brief devuelve iterador al inicio del conjunto
*/	 
	iterator begin();

/**@brief devuelve iterador al final (posición siguiente al último del conjunto
*/
	iterator end();

/** @brief class iterator
 * forward iterador sobre el conjunto, LECTURA
 *  iterator() ,operator*(), operator++, operator++(int) operator=, operator==, operator!=
 * */

    class iterator{

    public:

/** @brief Constructor primitivo. 
	
*/		
		iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		iterator(const iterator & it);

/** @brief Constructor a partir de un iterador de vector de entradas.
	@param[in] it iterador a asignar
*/
		iterator(const std::vector<entrada>::iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		conjunto::entrada & operator*();

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		iterator & operator=(const iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const iterator & it);

	private:

		friend class conjunto;
		std::vector<entrada>::iterator itv;

	};

////////////////////////////----CONST_ITERATOR----///////////////////////////

/** @brief  
     @return Devuelve el const_iterator a la primera posición del conjunto.
@post no modifica el conjunto
*/ 
	const_iterator cbegin() const;

/** @brief iterador al final
     @return Devuelve el iterador constante a la  posición final del conjunto.
@post no modifica el conjunto
*/
	const_iterator cend() const;

/** @brief class const_iterator
 * forward iterador constante sobre el conjunto, Lectura 
 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
 * */
	class const_iterator{

	public:

/** @brief Constructor primitivo. 
	
*/
		const_iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		const_iterator(const const_iterator & it);

/** @brief Constructor a partir de un const_iterador de vector de entradas.
	@param[in] it iterador a asignar
*/
		const_iterator(const std::vector<entrada>::const_iterator & it);

/** @brief Convierte iterator en const_iterator
*/
		const_iterator(const iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		const conjunto::entrada & operator*() const;

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		const_iterator & operator=(const const_iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		const_iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		const_iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		const_iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		const_iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const const_iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const const_iterator & it);

	private:
	 
		std::vector<entrada>::const_iterator c_itv;
		friend class conjunto;

	};

////////////////////////////----DESCRIPTION_ITERATOR----///////////////////////////

/**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
@param[in] descr descripcion de buscamos
@return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
*/
	description_iterator dbegin(const string & descr);

/**   @brief devolver fin del conjunto
@return un iterador que apunta a la posicion final
*/
	description_iterator dend();

/** @brief class description_iterator
 * forward iterador constante sobre el diccionario, Lectura 
 *  const_iterator ,operator*, operator++, operator++(int) operator=, operator==, operator!=
     * esta clase itera sobre todos los elementos que emparejan con una descripcion
 * */
	class description_iterator{

	public:

/** @brief Constructor primitivo. 
	
*/
		description_iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		description_iterator(const description_iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		conjunto::entrada & operator*();

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		description_iterator & operator=(const description_iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		description_iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		description_iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		description_iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		description_iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const description_iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const description_iterator & it);

	private:

		conjunto * ptr;
		string descr;  // la descripcion se asigna en con el metodo dbegin
		std::vector<entrada>::iterator itv;
		friend class conjunto;
	  
	};
	
/**   @brief devolver primera posicion del elemento que empareja con la descripcion descr
@param[in] descr descripcion de buscamos

@return un iterador que apunta a la primera posicion, el emparejamiento se hace teniendo en cuenta que descr debe ser una subcadena de la descripción del delito.
@post no modifica el conjunto
*/
	const_description_iterator cdbegin(const string & descr) const;

/**   @brief devolver fin del conjunto
@return un iterador que apunta a la posicion final
@post no modifica el conjunto
*/
	const_description_iterator cdend() const;
	
	class const_description_iterator{

	public:

/** @brief Constructor primitivo. 
	
*/
		const_description_iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		const_description_iterator(const const_description_iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		const conjunto::entrada & operator*() const;

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		const_description_iterator & operator=(const const_description_iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		const_description_iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		const_description_iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		const_description_iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		const_description_iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const const_description_iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const const_description_iterator & it);

	private:
	 
	 	const conjunto * ptr;
		string descr;
		std::vector<entrada>::const_iterator c_itv;
		friend class conjunto;

	};

/**   @brief Devolver primera posición del elemento que tiene arresto.
@return un iterador que apunta a la primera posición teniendo en cuenta que el campo arresto debe estar a true
*/
	arrest_iterator abegin();

/**   @brief Devolver fin del conjunto.
@return un iterador que apunta a la posición final
*/
	arrest_iterator aend();
	
	class arrest_iterator{

	public:

/** @brief Constructor primitivo. 
	
*/
		arrest_iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		arrest_iterator(const arrest_iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		conjunto::entrada & operator*();

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		arrest_iterator & operator=(const arrest_iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		arrest_iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		arrest_iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		arrest_iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		arrest_iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const arrest_iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const arrest_iterator & it);



	private:

		conjunto * ptr;
		std::vector<entrada>::iterator itv;
		friend class conjunto;
	  
	};
	
/**   @brief Devolver primera posición del elemento que tiene arresto.
@return un iterador que apunta a la primera posición teniendo en cuenta que el campo arresto debe estar a true.
@post no modifica el conjunto
*/
	const_arrest_iterator cabegin() const;

/**   @brief Devolver fin del conjunto.
@return un iterador que apunta a la posición final
@post no modifica el conjunto
*/
	const_arrest_iterator caend() const;
	
	class const_arrest_iterator{

	public:

/** @brief Constructor primitivo. 
	
*/
		const_arrest_iterator();

/** @brief Constructor de copia.
	@param[in] it iterador a copiar
*/
		const_arrest_iterator(const const_arrest_iterator & it);

/** @brief Convierte arrest_iterator en const_arrest_iterator
*/
		const_arrest_iterator(const arrest_iterator & it);

/** @brief Operador de acceso al elemento apuntado por el iterador.
*/
		const conjunto::entrada & operator*() const;

/** @brief Operador de asignación.
@param[in] org iterador a copiar
*/
		const_arrest_iterator & operator=(const const_arrest_iterator & it);

/** @brief Operador de incremento postfijo.
@param vacío para distinguirlo del incremento prefijo
*/
		const_arrest_iterator operator++( int );

/** @brief Operador de incremento prefijo.
*/
		const_arrest_iterator & operator++();

/** @brief Operador de decremento postfijo.
@param vacío para distinguirlo del decremento prefijo
*/
		const_arrest_iterator operator--(int);

/** @brief Operador de decremento prefijo.
*/
		const_arrest_iterator & operator--();

/** @brief Operador de igualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator==(const const_arrest_iterator & it);

/** @brief Operador de desigualdad.
@param it iterador a comparar.
@return true o false según cumpla la comparación lógica.
*/
		bool operator!=(const const_arrest_iterator & it);

	private:
	 
	 	const conjunto * ptr;
		std::vector<entrada>::const_iterator c_itv;
		friend class conjunto;

	};
	   
	 
private:

	std::vector<crimen> vc; // vector ORDENADO por crimen.id que almacena los elementos del conjunto
 
/** \invariant
 
 IR: rep ==> bool
 
\li Para todo i, 0 <= i < vc.size() se cumple
	vc[i].ID > 0;
\li Para todo i, 0 <= i <= D.dic.size()-1 se cumple
	vc[i].ID< vc[i+1].ID

*/

	
/** @brief Chequea el Invariante de la representacion 
@return true si el invariante es correcto, falso en caso contrario
*/
	bool cheq_rep( ) const;

//  declaracion del operator<< como metodo amigo
	friend ostream & operator << ( ostream & sal, const conjunto & D);

 // Clases amigas
	friend class iterator;
	friend class const_iterator;
	friend class description_iterator;
	friend class const_description_iterator;
	friend class arrest_iterator;
	friend class const_arrest_iterator;

};


/** @brief imprime todas las entradas del conjunto 
@post  No se modifica el conjunto.
*/
ostream & operator << ( ostream & sal, const conjunto & D);

#include "conjunto.hxx"

#endif